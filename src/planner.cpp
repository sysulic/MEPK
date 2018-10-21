#include "planner.h"

int tc = 0;

Planner::Planner(const char *domain) {
	printf("\n================================================================\n");
	printf("domain_file: %s\n", domain);

	preProcessTime = 0.0f;
	searchTime = 0.0f;
	heuristicTime = 0.0f;
	pIteTime = 0.0f;
	resDepth = 0;
	resNodeNum = 0;
	exploredNodeNum = 0;
	goalPos = -1;

	allNodes.clear();
	allEdges.clear();
	solEdge.clear();
	exploredNode.clear();

	clock_t startClock = clock();

	printf("\nPreprocessing Start!\n...\n");
	parser.exec(domain, false);
	in.exec();
	printf("\nProcessing Completed!\n");

	// print compile result
	//cout << "epis_actions.size() = " << in.mine_epis_actions.size() << endl;
	//cout << "ontic_actions.size() = " << in.mine_ontic_actions.size() << endl;
	//cout << endl << endl;
	//init.print();
	//cout << endl << endl;
	//goal.print();
	//cout << endl << endl;
	//in.mine_constraint.print();
	//cout << endl << endl;

	clock_t endClock = clock();
	preProcessTime = difftime(endClock, startClock) / 1000000.0;
}

Planner::~Planner() {

}

void Planner::exec() {
	printf("\nPlanning Start!\n...\n");
	if (in.mine_init.neg_entails(in.mine_goal, in.mine_constraint)) {
		printf("init neg_entails goal!\n");
       		return;
	}

	clock_t startClock = clock();

	LAONode initNode(in.mine_init, 0, false, false);
	allNodes.push_back(initNode);
	solEdge.insert(make_pair(0, -1));
	
	while(!isSolved(0)) {
		int index = getToExploredNode();
		//cout << index << endl;
		exploreNode(index);
		clock_t start = clock();
		policyIteration();
		clock_t end = clock();
		pIteTime += difftime(end, start) / 1000000.0f;
		//print(0);
		//if(tc++ > 1) break;
	}

	clock_t endClock = clock();
	searchTime = difftime(endClock, startClock) / 1000000.0;
	print(0);
	cout << "\n\n===========================Information===========================" << endl;
	printf("preTime = %.6f\n", preProcessTime);
	printf("totalTime = %.6f\n", preProcessTime+searchTime);
	printf("searchTime = %.6f\n", searchTime);
	printf("heuristicTime = %.2f\n", heuristicTime);
	printf("policyIterationTime = %.2f\n", pIteTime);
	cout << "resDepth = " << resDepth << endl;
	cout << "resNodeNum = " << resNodeNum << endl;
	cout << "exploredNodeNum = " << exploredNodeNum << endl << endl;
	printf("Planning Completed!\n");

	/*
	ofstream ros("result.output");
	ros << endl << "Initial:" << endl;
	show(ros);
	ros.close();
	*/
}

bool Planner::isSolved(int index) {
	if(solEdge.find(index) == solEdge.end()) return false;
	if(solEdge[index] == -1) {
		return allNodes[index].isSolved;
	}
	bool ans = true;
	for(size_t i = 0;i < allEdges[index][solEdge[index]].childNode.size();i++) {
		ans &= isSolved(allEdges[index][solEdge[index]].childNode[i]);
	}
	return ans;
}

int Planner::insertNode(ACDF& kb) {
	int nodeSize = allNodes.size(), i = 0;
	bool isGoal = kb.neg_entails(in.mine_goal, in.mine_constraint);
	if(isGoal) {
		if(goalPos == -1) {
			goalPos = nodeSize;
			allNodes.push_back(LAONode(kb, 0.0f, true, false));
		}
		return goalPos;
	}
	for(;i < nodeSize;i++) {
		if(i == goalPos) continue;
		if(kb.equals(allNodes[i].kb, in.mine_constraint)) {
			return i;
		}
	}
	allNodes.push_back(LAONode(kb, 
		heuristicHelper.getHeuristicValue(kb, in.mine_pos_goal), false, false));
	return nodeSize;
}

bool Planner::hasExplored(ACDF& kb) {
	int nodeSize = allNodes.size(), i = 0;
	for(;i < nodeSize;i++) {
		if(kb.equals(allNodes[i].kb, in.mine_constraint)) {
			break;
		}
	}
	return allEdges.find(i) != allEdges.end();
}

bool Planner::isInSolGraph(const int index) {
	return solEdge.find(index) != solEdge.end() && index != goalPos;
}

void Planner::labelGraph() {

}

void Planner::policyIteration() {
	extractSolution();
	while(true) {
		map<int, int> oriSolEdge(solEdge);
		updateStateCost();
		updatePolicy();
		if(isSolved(0) || !checkSolChange(oriSolEdge)) break;
	}
}

void Planner::extractSolution() {
	solEdge.clear();
	list<int> mq;
	mq.push_back(0);
	while(!mq.empty()) {
		int index = mq.front();
		mq.pop_front();
		if(solEdge.find(index) != solEdge.end()) continue;
		if(allNodes[index].isSolved 
			|| allEdges.find(index) == allEdges.end()) {
			solEdge.insert(make_pair(index, -1));
			continue;
		}
		vector<char> episVist = checkEpisAlongSol(index);
		double minActionCost = (double)INT_MAX;
		int minIndex = -1;
		for(size_t i = 0;i < allEdges[index].size();i++) {
			bool ignored = false;
			if(allEdges[index][i].childNode.size() == 2 &&
				episVist[allEdges[index][i].actionIndex] == '1') continue;
			for(size_t j = 0;j < allEdges[index][i].childNode.size();j++) {
				if(allEdges[index][i].childNode[j] == index ||
					isInSolGraph(allEdges[index][i].childNode[j])) {
					ignored = true;
					break;
				}
			}
			if(ignored) continue;
			double tempHeu = ((allEdges[index][i].et == ONTICEDGE) ? 
				onticCost+allNodes[allEdges[index][i].childNode[0]].heuValue : 
				episCost+0.5*allNodes[allEdges[index][i].childNode[0]].heuValue
				+0.5*allNodes[allEdges[index][i].childNode[1]].heuValue);
			if(tempHeu< minActionCost) {
				minActionCost = tempHeu;
				minIndex = i;
			}
		}
		if(minIndex == -1) {
			solEdge.insert(make_pair(index, -1));
			allNodes[index].heuValue = maxHeuristicValue;
		}
		else {
			solEdge[index] = minIndex;
			for(size_t j = 0;j < allEdges[index][solEdge[index]].childNode.size();j++) {
				mq.push_back(allEdges[index][solEdge[index]].childNode[j]);
			}
		}
	}
}

void Planner::updateStateCost() {
	map<int, double> lastHeuValue = getStateCost();
	while(true) {
		double curError = 0.0f;
		map<int, double> curHeuValue;
		for(map<int, int>::const_iterator ite = solEdge.begin();
			ite != solEdge.end();ite++) {
			int index = ite->first;
			if(ite->second == -1) {
				curHeuValue[index] = lastHeuValue[index];
				continue;
			}
			curHeuValue[index] = ((allEdges[index][solEdge[index]].et == ONTICEDGE) ? 
					onticCost + lastHeuValue[allEdges[index][solEdge[index]].childNode[0]] : 
					episCost + 0.5*lastHeuValue[allEdges[index][solEdge[index]].childNode[0]]
					+ 0.5*lastHeuValue[allEdges[index][solEdge[index]].childNode[1]]);
			curError = max(curError, 
				abs(curHeuValue[index] - lastHeuValue[index]));
		}
		lastHeuValue = curHeuValue;
		if(curError <= errorBound) break;
	}
	for(auto ite = lastHeuValue.begin();ite != lastHeuValue.end();ite++) {
		//allNodes[ite->first].heuValue = min(allNodes[ite->first].heuValue, 
		//								ite->second );
		allNodes[ite->first].heuValue = ite->second;
	}
}

void Planner::updatePolicy(int index) {
	assert(!solEdge.empty());
	if(solEdge[index] == -1) return ;
	for(size_t i = 0;i < allEdges[index][solEdge[index]].childNode.size();i++) {
		updatePolicy(allEdges[index][solEdge[index]].childNode[i]);
	}
	for(size_t i = 0;i < allEdges[index].size();i++) {
		allNodes[index].heuValue = min(allNodes[index].heuValue, 
			((allEdges[index][i].et == ONTICEDGE) ? 
			onticCost+allNodes[allEdges[index][i].childNode[0]].heuValue : 
			episCost+0.5*allNodes[allEdges[index][i].childNode[0]].heuValue
			+0.5*allNodes[allEdges[index][i].childNode[1]].heuValue));
	}
	// remove old edges and add new edges
	if(index == 0) extractSolution();
}

int Planner::getToExploredNode() {
	assert(!solEdge.empty());
	for(auto ite = solEdge.begin();ite != solEdge.end();ite++) {
		if(!allNodes[ite->first].isSolved &&
			ite->second == -1) return ite->first;
	}
	assert(false);
}

void Planner::exploreNode(int index) {
	ACDF curKB = allNodes[index].kb;
	if(allNodes[index].isSolved) return ;
	if(find(exploredNode.begin(), exploredNode.end(), index)
		!= exploredNode.end()) return ;
	if(allEdges.find(index) != allEdges.end()) return ;
	exploredNodeNum++;
	exploredNode.insert(index);
	int onticSize = in.mine_ontic_actions.size(), sensSize = in.mine_epis_actions.size();
	allEdges[index].clear();
	//cout << "======================================" << endl;
	for(int i = 0;i < onticSize;i++) {
		if(curKB.neg_entails(in.mine_ontic_actions[i].pre_con, in.mine_constraint)) {
			ACDF resKB = curKB;
			vector<ACDF> satEff;
			for(auto ite = in.mine_ontic_actions[i].con_eff.begin();ite != in.mine_ontic_actions[i].con_eff.end();ite++) {
				if(curKB.neg_entails(ite->condition, in.mine_constraint)) {
					satEff.push_back(ite->effect);
				}
			}
			for(auto ite = satEff.begin();ite != satEff.end();ite++) {
				resKB = resKB.update(*ite, in.mine_constraint).minimal(in.mine_constraint);
			}
			allEdges[index].push_back(
				LAOEdge(ONTICEDGE, i, vector<int>(1, insertNode(resKB))));
		}
	}

	for(int i = 0;i < sensSize;i++) {
		if(curKB.neg_entails(in.mine_epis_actions[i].pre_con, in.mine_constraint)) {
			ACDF posKB = curKB.revision(in.mine_epis_actions[i].pos_res, in.mine_constraint).minimal(in.mine_constraint);
			ACDF negKB = curKB.revision(in.mine_epis_actions[i].neg_res, in.mine_constraint).minimal(in.mine_constraint);
			vector<int> temp;
			temp.push_back(insertNode(posKB));
			temp.push_back(insertNode(negKB));
			allEdges[index].push_back(LAOEdge(EPISEDGE, i, temp));
			/*cout << in.mine_epis_actions[i].name << endl;
			curKB.print();
			cout << endl << endl;
			posKB.print();
			cout << endl << endl;
			negKB.print();
			cout << endl << endl << endl;*/
		}
	}
	//cout << "======================================" << endl;
	return ;
}

bool Planner::checkSolChange(const map<int, int>& ori) {
	for(map<int, int>::const_iterator ite = ori.begin();ite != ori.end();ite++) {
		if(solEdge.find(ite->first) == solEdge.end() ||
			solEdge[ite->first] != ite->second) {
			return true;
		}
	}
	return false;
}

void Planner::print(int index, int ident, int depth) {
	if(ident == 0) {
		cout << "===========================Plan Tree===========================" << endl;
	}
	resNodeNum++;
	resDepth = max(resDepth, depth);
	string ide = "";
	for(int i = 0;i < ident;i++) ide+=' ';
	if(solEdge[index] == -1) {
		cout << ide << "TERMINATE\n";
	}
	else if(allEdges[index][solEdge[index]].et == ONTICEDGE) {
		cout << ide << in.mine_ontic_actions[allEdges[index][solEdge[index]].actionIndex].name << endl;
		print(allEdges[index][solEdge[index]].childNode[0], ident+2, depth+1);
	}
	else {
		cout << ide << in.mine_epis_actions[allEdges[index][solEdge[index]].actionIndex].name;
		cout << " +:" << endl;
		print(allEdges[index][solEdge[index]].childNode[0], ident+2, depth+1);
		cout << ide << in.mine_epis_actions[allEdges[index][solEdge[index]].actionIndex].name;
		cout << " -:" << endl;
		print(allEdges[index][solEdge[index]].childNode[1], ident+2, depth+1);
	}
}

vector<char> Planner::checkEpisAlongSol(int index) {
	vector<char> ans(in.mine_epis_actions.size(), '0');
	list<int> mq;
	mq.push_back(index);
	while(!mq.empty()) {
		int lastIndex = mq.front();
		mq.pop_front();
		for(auto ite = solEdge.begin();ite != solEdge.end();ite++) {
			if(ite->second == -1) continue;
			for(size_t j = 0;j < allEdges[ite->first][ite->second].childNode.size();j++) {
				if(lastIndex == allEdges[ite->first][ite->second].childNode[j]) {
					mq.push_back(ite->first);
					if(allEdges[ite->first][ite->second].childNode.size() == 2) {
						ans[allEdges[ite->first][ite->second].actionIndex] = '1';
					}
				}
			}
		}
	}
	return ans;
}

map<int, double> Planner::getStateCost() {
	list<int> mq;
	mq.push_back(0);
	map<int, double> ans;
	while(!mq.empty()) {
		int index = mq.front();
		mq.pop_front();
		if(solEdge[index] == -1) {
			ans[index] = allNodes[index].heuValue;
		}
		else {
			ans[index] = ((allEdges[index][solEdge[index]].et == ONTICEDGE) ? 
			onticCost+allNodes[allEdges[index][solEdge[index]].childNode[0]].heuValue : 
			episCost+0.5*allNodes[allEdges[index][solEdge[index]].childNode[0]].heuValue
			+0.5*allNodes[allEdges[index][solEdge[index]].childNode[1]].heuValue);
			for(size_t i = 0; i < allEdges[index][solEdge[index]].childNode.size();i++) {
				mq.push_back(allEdges[index][solEdge[index]].childNode[i]);
			}
		}
	}
	return ans;
}

void Planner::show(ofstream& ros, int index, int indent) {
	allNodes[index].kb.show(ros, 0);
	ros << endl << endl;
	if(solEdge[index] == -1) return ;
	else if(allEdges[index][solEdge[index]].et == ONTICEDGE) {
		for(int j = 0;j < indent;j++) ros << " ";
		ros << "==> " << in.mine_ontic_actions[allEdges[index][solEdge[index]].actionIndex].name << " :" << endl;
		for(int j = 0;j < indent;j++) ros << " ";
		show(ros, allEdges[index][solEdge[index]].childNode[0], indent+3);
	}
	else {
		
		for(int j = 0;j < indent;j++) ros << " ";
		ros << "==> " << in.mine_epis_actions[allEdges[index][solEdge[index]].actionIndex].name << " +:" << endl;
		for(int j = 0;j < indent;j++) ros << " ";
		show(ros, allEdges[index][solEdge[index]].childNode[0], indent+3);
		for(int j = 0;j < indent;j++) ros << " ";
		ros << "==> " << in.mine_epis_actions[allEdges[index][solEdge[index]].actionIndex].name << " -:" << endl;
		for(int j = 0;j < indent;j++) ros << " ";
		show(ros, allEdges[index][solEdge[index]].childNode[1], indent+3);
	}
	return ;
}

