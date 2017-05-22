#include "reader.h"
// #include "Formula.h"

int yyparse();

void Reader::exec(const char* dFile, const char* pFile) {

	FILE* fp_d=fopen(dFile, "r");
	FILE* fp_p=fopen(pFile, "r");
	if(fp_d==NULL) {
		printf("cannot open %s\n", dFile);
		return;
	}
	if(fp_p==NULL) {
		printf("cannot open %s\n", pFile);
		return;
	}
	// puts("----- begin parsing -----");
	extern FILE* yyin;  // yyin和yyout都是FILE*类型
	yyin = fp_d;  // yacc会从yyin读取输入，yyin默认是标准输入，这里改为磁盘文件。yacc默认向yyout输出，可修改yyout改变输出目的
	yyparse();
	yyin = fp_p;
	yyparse();
	// puts("----- end parsing -----");
	fclose(fp_d);
	fclose(fp_p);

	string beginFile = "../outpute/";
	beginFile += this->domainName; beginFile += "_begin";
	string endFile = "../outpute/";
	endFile += this->domainName; endFile += "_reader";
	ofstream out_begin(beginFile.c_str());  // 打开要写入的文本文件
	ofstream out_end(endFile.c_str());  // 打开要写入的文本文件
	// if(!out_begin.is_open()) {
	// 	cout << "cannot open " << beginFile << endl;
	// 	return;
	// }
	// if(!out_end.is_open()) {
	// 	cout << "cannot open " << endFile << endl;
	// 	return;
	// }
	printInit(out_begin, out_end);
	printConstraint(out_begin, out_end);
	printGoal(out_begin, out_end);
	printEpistemicActions(out_begin, true);
	// printEpistemicActions(out_end, false);
	printOnticActions(out_begin, true);
	// printOnticActions(out_end, false);  // conversion after first printActions()
	out_begin.close();
	out_end.close();

}

void Reader::printInit(ofstream & out_begin, ofstream & out_end) {

	// print init
	// out_begin << "----------------init Tree-------------------" << endl;
	// init.show(out_begin, 0);
	// out_begin << "----------------  done  -------------------\n" << endl;

	// print init DNFed
	// out_end << "----------------init CDF Tree-------------------" << endl;
	init.convertToCDFTree();
	// init.show(out_end, 0);
	// out_end << "----------------  done  -------------------\n" << endl;
}

void Reader::printConstraint(ofstream & out_begin, ofstream & out_end) {

	// print constraint
	// out_begin << "----------------init Tree-------------------" << endl;
	// constraint.show(out_begin, 0);
	// out_begin << "----------------  done  -------------------\n" << endl;

	// print constraint DNFed
	// out_end << "----------constraint DNF Tree--------------" << endl;
	constraint.convertToCDFTree();
	// constraint.show(out_end, 0);
	// out_end << "----------------  done  -------------------\n" << endl;
}

void Reader::printGoal(ofstream & out_begin, ofstream & out_end) {

	// print goal
	// out_begin << "----------------goal Tree-------------------" << endl;
	// goal.show(out_begin, 0);
	// out_begin << "----------------  done  -------------------\n" << endl;
	
	// print goal DNFed
	// out_end << "----------goal's complement CDF Tree-------------" << endl;
	goal.set_complement();  // we'll use ¬goal in our reasoning algo
	goal.convertToCDFTree();
	// goal.show(out_end, 0);
	// out_end << "----------------  done  -------------------\n" << endl;
}

void Reader::printEpistemicActions(ofstream & out_file, bool edit) {

	// out_file << "-------------- epistemic actions ----------------\n";
  	for(PreEpistemicActionList::iterator it_action = epistemicActions.begin();
  		it_action != epistemicActions.end(); ++it_action) {

		// if (it_action != epistemicActions.begin())
			// out_file << "******************************************\n";
		// out_file << ":action " << it_action->name << " --------------\n";
		// out_file << ":category " << it_action->category << " ------------\n";

		// out_file << "\n:parameters ----------------\n";
		// for (MultiTypeList::iterator it_para = it_action->paras.begin();
		// 	it_para != it_action->paras.end(); ++it_para) {
		// 	out_file << it_para->first << ":";
		// 	for (StringList::const_iterator it_vrb = (*it_para).second.begin();
		// 		it_vrb != it_para->second.end(); ++it_vrb) {
		// 		out_file << " " << *it_vrb;
		// 	}
		// 	out_file << "   ";
		// }

		// out_file << "\n:precondition --------------" << endl;
		// it_action->preCondition.show(out_file, 0);
		// if (edit) {
			it_action->preCondition.set_complement();
			it_action->preCondition.convertToCDFTree();
		// }

		// out_file << "\n:observe_pos -------------------" << endl;
		// it_action->observe_pos.show(out_file, 0);
		// if (edit)
			it_action->observe_pos.convertToCDFTree();

		// out_file << "\n:observe_neg ---------------" << endl;
		// it_action->observe_neg.show(out_file, 0);
		// if (edit)
			it_action->observe_neg.convertToCDFTree();
  	}
	// out_file << "----------------  done  -------------------\n\n";

}

void Reader::printOnticActions(ofstream & out_file, bool edit) {
	// out_file << "-------------- ontic actions ----------------\n";
  	for(PreOnticActionList::iterator it_action = onticActions.begin();
  		it_action != onticActions.end(); ++it_action) {

		// if (it_action != onticActions.begin())
		// 	out_file << "******************************************\n";
		// out_file << ":action " << (*it_action).name << " --------------\n";
		// out_file << ":category " << it_action->category << " ------------\n";

		// out_file << "\n:parameters ----------------\n";
		// for (MultiTypeList::iterator it_para = (*it_action).paras.begin();
		// 	it_para != (*it_action).paras.end(); ++it_para) {
		// 	out_file << (*it_para).first << ":";
		// 	for (StringList::const_iterator it_vrb = (*it_para).second.begin();
		// 		it_vrb != (*it_para).second.end(); ++it_vrb) {
		// 		out_file << " " << *it_vrb;
		// 	}
		// 	out_file << "   ";
		// }

		// out_file << "\n:precondition --------------" << endl;
		// (*it_action).preCondition.show(out_file, 0);
		// if (edit) {
			(*it_action).preCondition.set_complement();
			(*it_action).preCondition.convertToCDFTree();
		// }
		// out_file << "\n:effect --------------------\n";
		size_t counter = 1;
		for (EffectList::iterator it_ef = (*it_action).effects.begin();
			it_ef != (*it_action).effects.end(); ++it_ef, ++counter) {
			// out_file << "\n--- effect --- No." << counter << " :\n";
			// (*it_ef).aft_condition.show(out_file, 0);
			// if (edit) {
				(*it_ef).aft_condition.set_complement();
				(*it_ef).aft_condition.convertToCDFTree();
			// }
			// out_file << "-----\n";
			// (*it_ef).con_effect.show(out_file, 0);
			// if (edit)
				(*it_ef).con_effect.convertToCDFTree();
		}

  	}
	// out_file << "----------------  done  -------------------\n\n";

}
