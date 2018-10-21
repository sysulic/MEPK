#include "parse.h"

using namespace std;

extern std::string domainName;
extern vector<std::string> atoms;
extern map<string, vector<string> > objects;
extern vector<string> agents;
extern map<int, string> findAtomsByIndex;
extern map<string, int> findAtomsByName;
extern vector<SensingAction> sActions;
extern vector<OnticAction> oActions;
extern int atomNum;
extern KLDNF init;
extern KLDNF posGoal;
extern KLDNF goal;
extern PropDNF constraint;

int yyparse();

void Parse::exec(const char* path, bool showCompileResult) {
	FILE* df = fopen(path, "r");
	if(df==NULL) {
		printf("cannot open %s\n", path);
		return;
	}
	extern FILE* yyin;
	yyin = df;
	yyparse();
	fclose(df);

	if(!showCompileResult) return;

	// pre-processing
	// goal = posGoal;
	// goal = posGoal.negation(constraint);

	//for(size_t i = 0;i < sActions.size();i++) {
	//	sActions[i].preCon = sActions[i].preCon.negation(constraint);
	//}

	//for(size_t i = 0;i < oActions.size();i++) {
	//	oActions[i].preCon = oActions[i].preCon.negation(constraint);
	//	for(size_t j = 0;j < oActions[i].eff.size();j++) {
	//		oActions[i].eff[j].condition = oActions[i].eff[j].condition.negation(constraint);
	//	}
	//}

	// output the compile result
	ofstream os("compile.output");
	os << "================================= " << 
		domainName << " =================================" << endl;
	for(map<string, vector<string> >::iterator ite = objects.begin();
	 ite != objects.end();ite++) {
		os << ite->first << " :";
		for(size_t i = 0;i < ite->second.size();i++) {
			os << "  " << ite->second[i];
		}
		os << endl;
	}
	os << "agent : ";
	for(size_t i = 0;i < agents.size();i++) {
		os << agents[i] << " ";
	}
	os << endl;
	os << "================================= " << "atoms"  << " =================================" << endl;
	for(map<int, string>::iterator ite = findAtomsByIndex.begin();
		ite != findAtomsByIndex.end();ite++) {
		os << ite->first << "    " << ite->second
			<< "    " << findAtomsByName[ite->second] << endl;
	}
	os << "================================= " << "init:"  << " =================================" << endl;
	init.show(os);
	os << endl << "================================= " << "constraint: "  << " =================================" << endl;
	constraint.show(os);
	os << endl << "================================= " << "goal: "  << " =================================" << endl;
	goal.show(os);
	os << endl << "================================= " << "posGoal: "  << " =================================" << endl;
	posGoal.show(os);
	os << endl;

	os << endl << endl;
	PropDNF preConstraint;
	preConstraint.dnf.push_back(PropTerm(atomNum));
	os << "=================================sensing=================================\n";
	for(size_t i = 0;i < sActions.size();i++) {
		os << "Action Name : " << sActions[i].name << endl << "preCon : ";
		sActions[i].preCon.show(os);
		os << endl << "posRes : ";
		sActions[i].posRes.show(os);
		os << endl << "negRes : ";
		sActions[i].negRes.show(os);
		os << endl << endl;
	}
	os << "=================================ontic=================================\n";
	for(size_t i = 0;i < oActions.size();i++) {
		os << "Action Name : " << oActions[i].name << endl << "preCon : ";
		oActions[i].preCon.show(os);
		os << endl;
		os << "Result List : \n";
		for(size_t j = 0;j < oActions[i].eff.size();j++) {
			os << "   ";
			oActions[i].eff[j].condition.show(os);
			os << endl << "   ";
			oActions[i].eff[j].effect.show(os);
			os << endl << endl;
		}
	}
	os << "sensing action number : " << sActions.size() << endl;
	os << "ontic action number : " << oActions.size() << endl;
	os.close();
}