%{
#include "define.h"

int yylex(void);
int yyerror(char* s);

using namespace std;

extern std::string domainName;
extern vector<std::string> atoms;
extern map<string, vector<string> > objects;
extern vector<string> agents;
extern map<int, string> findAtomsByIndex;
extern map<string, int> findAtomsByName;
extern map<string, int> findSensingActionByName;
extern map<string, int> findOnticActionByName;
extern vector<SensingAction> sActions;
extern vector<OnticAction> oActions;
extern int atomNum;
extern KLDNF init;
extern KLDNF posGoal;
extern KLDNF goal;
extern PropDNF constraint;

void atomGround(vector<string>& ga, int pos,  string cur, map<string, vector<char> >& visited) {
	if(pos == (int)ga.size()) {
		cur = "(" + ga[0] + cur + ")";
		int index = findAtomsByName.size();
		findAtomsByName[cur] = index;
		findAtomsByIndex[index] = cur;
		atomNum++;
		return ;
	}
	string cType = ga[pos];
	for(size_t i = 0;i < visited[cType].size();i++) {
		if(visited[cType][i] == '0') {
			visited[cType][i] = '1';
			string nc = cur + " " + ((cType=="agent") ? agents[i] : objects[cType][i]);
			atomGround(ga, pos+1, nc, visited);
			visited[cType][i] = '0';
		}
	}
}

vector<map<string, string>> actionVar;
vector<string> actionVarSeq;

void actionVarGround(map<string, string>& table, map<string, string> cur, map<string, string>::iterator ite, map<string, vector<char>> visited) {
	if(ite == table.end()) {
		actionVar.push_back(cur);
		return ;
	}
	string varType = ite->second;
	if(varType == "agent") {
		for(size_t i = 0;i < agents.size();i++) {
			if(visited["agent"][i] == '0') {
				visited["agent"][i] = '1';
				map<string, string> temp(cur);
				temp[ite->first] = agents[i];
				map<string, string>::iterator tempIte = ite;
				actionVarGround(table, temp, ++tempIte, visited);
				visited["agent"][i] = '0';
			}
		}
	}
	else {
		for(size_t i = 0;i < objects[varType].size();i++) {
			if(visited[varType][i] == '0') {
				visited[varType][i] = '1';
				map<string, string> temp(cur);
				temp[ite->first] = objects[varType][i];
				map<string, string>::iterator tempIte = ite;
				actionVarGround(table, temp, ++tempIte, visited);
				visited[varType][i] = '0';
			}
		}
	}
}
%}

%union{
	bool *defaultType;
	std::string *str;
	std::map<std::string, std::vector<std::string> > *stringToStringVector;
	std::vector<std::string> *stringVector;
	std::map<int, std::string> *intToString;
	std::map<std::string, int> *stringToInt;
	std::vector<std::vector<std::string> > *stringVectorVector;
	KLDNF *kldnf;
	std::vector<KLDNF> *kldnfVector;
	std::vector<std::vector<KLDNF> > *kldnfVectorVector;
	std::vector<std::vector<std::vector<KLDNF> > > *kldnfVectorVectorVector;
	PropDNF *pdnf;
	std::vector<PropDNF> *pdnfVector;
	std::map<std::string, std::string> *stringToString;
}

%token <str> NAME

%token <str> K
%token <str> DK
%token AND
%token OR
%token NOT
%token IMPLY
%token ONEOF

%token <str> TRUETERM
%token <str> FALSETERM

%token LEFT_PAREN
%token RIGHT_PAREN
%token LEFT_BRACE
%token RIGHT_BRACE
%token LEFT_BRACKET
%token RIGHT_BRACKET
%token COMMA
%token COLON
%token CONNECTOR

%token DEFINE
%token LDOMAIN
%token TYPES
%token PREDICATES
%token PRECONDITION
%token ACTION
%token CATEGORY
%token PARAMETERS
%token <str> OBSERVE_POS
%token <str> OBSERVE_NEG
%token <str> EFFECT
%token PROBLEM
%token OBJECTS
%token AGENTS
%token INIT
%token CONSTRAINT
%token GOAL

// declare type
%type <str> DomainName
%type <str> TypeName
%type <defaultType> ObjectPart
%type <stringToStringVector> ObjectList
%type <stringToStringVector> DetailObjectList
%type <defaultType> AgentPart
%type <stringVector> AgentList
%type <defaultType> PredicatePart
%type <stringVector> GeneralAtom
%type <stringVectorVector> GeneralAtomList
%type <stringVector> VarList
%type <defaultType> InitPart
%type <kldnf> Formula
%type <kldnfVector> FormulaList
%type <kldnf> FormulaAtom
%type <kldnfVector> NegFormula
%type <kldnfVectorVector> NegFormulaList
%type <kldnfVector> NegFormulaAtom
%type <str> NameList
%type <defaultType> ConstraintPart
%type <pdnf> ConFormula
%type <pdnfVector> ConFormulaList
%type <pdnf> ConFormulaAtom
%type <defaultType> GoalPart
%type <defaultType> ActionPart
%type <defaultType> SensingAction
%type <defaultType> OnticAction
%type <kldnfVectorVectorVector> OnticResList
%type <kldnfVectorVector> OnticRes
%type <kldnfVectorVector> SingleOnticResList
%type <kldnfVector> SingleOnticRes
%type <defaultType> ActionVar
%type <stringToString> ActionVarList
%type <kldnfVector> GeneralFormula
%type <kldnfVectorVector> GeneralFormulaList
%type <kldnfVector> GeneralFormulaAtom
%type <stringVector> GeneralNameList
%type <kldnfVector> NegGeneralFormula
%type <kldnfVectorVector> NegGeneralFormulaList
%type <kldnfVector> NegGeneralFormulaAtom

%%

domain
	:	LEFT_PAREN
			DEFINE DomainName
			ObjectPart
			AgentPart
			PredicatePart
			ActionPart
			InitPart
			ConstraintPart
			GoalPart
		RIGHT_PAREN
	{
		domainName = *$3;
	};
DomainName
	:	LEFT_PAREN LDOMAIN NAME RIGHT_PAREN
	{
		$$ = $3;
	};
ObjectPart
	:	LEFT_PAREN COLON OBJECTS ObjectList RIGHT_PAREN
	{
		objects = *$4;
	}
	|	LEFT_PAREN COLON OBJECTS RIGHT_PAREN
	{

	};
ObjectList
	:	DetailObjectList
	{
		$$ = $1;
	}
	|	ObjectList DetailObjectList
	{
		$$ = $1;
		(*$$)[(*$2).begin()->first] = (*$2).begin()->second;
	};
DetailObjectList
	:	NAME TypeName
	{
		$$ = new (map<string, vector<string> >);
		$$->insert(make_pair(*$2, vector<string>(1, *$1)));
	}
	|	NAME DetailObjectList
	{
		$$ = $2;
		(*$$)[(*$$).begin()->first].push_back(*$1);
	};
TypeName
	: CONNECTOR NAME
	{
		$$ = $2;
	};
AgentPart
	: LEFT_PAREN COLON AGENTS AgentList RIGHT_PAREN
	{
		agents = *$4;
	};
AgentList
	: NAME
	{
		$$ = new vector<string>;
		(*$$).push_back(*$1);
	}
	| AgentList NAME
	{
		$$ = $1;
		(*$$).push_back(*$2);
	};
PredicatePart
	: LEFT_PAREN COLON PREDICATES  GeneralAtomList RIGHT_PAREN
	{
		atomNum = 0;
		map<string, vector<char> > visited;
		for(map<string, vector<string> >::iterator ite = objects.begin(); ite != objects.end();ite++) {
			visited.insert(make_pair(ite->first, vector<char>(ite->second.size(), '0')));
		}
		visited.insert(make_pair("agent", vector<char>(agents.size(), '0')));
		vector<vector<string> > tgal(*$4);
		for(size_t i = 0;i < tgal.size();i++) {
			atomGround(tgal[i], 1, "", visited);
		}
	};
GeneralAtomList
	: GeneralAtom
	{
		$$ = new vector<vector<string> >;
		(*$$).push_back(*$1);
	}
	| GeneralAtomList GeneralAtom
	{
		$$ = $1;
		(*$$).push_back(*$2);
	};
GeneralAtom
	: LEFT_PAREN NAME RIGHT_PAREN
	{
		$$ = new vector<string>;
		(*$$).push_back(*$2);
	}
	| LEFT_PAREN NAME VarList RIGHT_PAREN
	{
		$$ = $3;
		(*$$).insert((*$$).begin(), *$2);
	};
VarList
	: NAME CONNECTOR NAME
	{
		$$ = new vector<string>;
		(*$$).push_back(*$3);
	}
	| VarList NAME CONNECTOR NAME
	{
		$$ = $1;
		(*$$).push_back(*$4);
	};
InitPart
	: LEFT_PAREN COLON INIT Formula RIGHT_PAREN
	{
		init = *$4;
	};
Formula
	: FormulaAtom
	{
		$$ = new KLDNF;
		*$$ = *$1;
	}
	| LEFT_PAREN K Formula RIGHT_PAREN
	{
		string agentName = $2->substr(2, $2->length()-2);
		$$ = new KLDNF;
		KLTerm klt;
		klt.KPart[agentName] = *$3;
		$$->dnf.push_back(klt);
	}
	| LEFT_PAREN DK Formula RIGHT_PAREN
	{
		string agentName = $2->substr(3, $2->length()-3);
		$$ = new KLDNF;
		KLTerm klt;
		klt.LPart[agentName].push_back(*$3);
		$$->dnf.push_back(klt);
	}
	| LEFT_PAREN NOT Formula RIGHT_PAREN
	{
		PropDNF preConstraint;
		preConstraint.dnf.push_back(PropTerm(atomNum));
		$$ = new KLDNF;
		*$$ = $3->negation(preConstraint);
	}
	| LEFT_PAREN AND FormulaList RIGHT_PAREN
	{
		$$ = new KLDNF;
		for(size_t i = 0;i < $3->size();i++) {
			*$$ = $$->conjunction((*$3)[i]);
		}
	}
	| LEFT_PAREN OR FormulaList RIGHT_PAREN
	{
		$$ = new KLDNF;
		for(size_t i = 0;i < $3->size();i++) {
			*$$ = $$->disjunction((*$3)[i]);
		}
	};
FormulaList
	: Formula Formula
	{
		$$ = new vector<KLDNF>;
		$$->push_back(*$1);
		$$->push_back(*$2);
	}
	| FormulaList Formula
	{
		$$ = $1;
		$$->push_back(*$2);
	};
FormulaAtom
	: LEFT_PAREN NameList RIGHT_PAREN
	{
		$$ = new KLDNF;
		PropTerm pt(atomNum);
		KLTerm klt;
		string atomName = "(" + *$2 + ")";
		if(atomName != "(True)") {
			pt.literal[findAtomsByName[atomName]] = TRUE;
		}
		klt.PPart.dnf.push_back(pt);
		$$->dnf.push_back(klt);
	};
NameList
	: NAME
	{
		$$ = new std::string;
		$$ = $1;
	}
	| NameList NAME
	{
		*$$ = *$$ + " " + *$2;
	};
ConstraintPart
	: LEFT_PAREN COLON CONSTRAINT ConFormula RIGHT_PAREN
	{
		constraint = *$4;
	};
ConFormula
	: ConFormulaAtom
	{
		$$ = new PropDNF;
		$$ = $1;
	}
	| LEFT_PAREN NOT ConFormula RIGHT_PAREN
	{
		$$ = new PropDNF;
		*$$ = $3->negation();
	}
	| LEFT_PAREN AND ConFormulaList RIGHT_PAREN
	{
		$$ = new PropDNF;
		for(size_t i = 0; i < $3->size();i++) {
			*$$ = $$->conjunction((*$3)[i]);
		}
	} 
	| LEFT_PAREN OR ConFormulaList RIGHT_PAREN
	{
		$$ = new PropDNF;
		for(size_t i = 0; i < $3->size();i++) {
			*$$ = $$->disjunction((*$3)[i]);
		}
	};
ConFormulaList
	: ConFormula ConFormula
	{
		$$ = new vector<PropDNF>;
		$$->push_back(*$1);
		$$->push_back(*$2);
	}
	| ConFormulaList ConFormula
	{
		$$ = $1;
		$$->push_back(*$2);
	};
ConFormulaAtom
	: LEFT_PAREN NameList RIGHT_PAREN
	{
		$$ = new PropDNF;
		PropTerm pt(atomNum);
		string atomName = "(" + *$2 + ")";
		if(atomName != "(True)") {
			pt.literal[findAtomsByName[atomName]] = TRUE;
		}
		$$->dnf.push_back(pt);
	};
GoalPart
	: LEFT_PAREN COLON GOAL NegFormula RIGHT_PAREN
	{
		goal = (*$4)[0];
		posGoal = (*$4)[1];
	};
NegFormula
	: NegFormulaAtom
	{
		$$ = new vector<KLDNF>;
		*$$ = *$1;
	}
	| LEFT_PAREN K NegFormula RIGHT_PAREN
	{
		string agentName = $2->substr(2, $2->length()-2);
		$$ = new vector<KLDNF>(2);
		KLTerm klt1, klt2;
		klt1.LPart[agentName].push_back((*$3)[0]);
		klt2.KPart[agentName] = (*$3)[1];
		(*$$)[0].dnf.push_back(klt1);
		(*$$)[1].dnf.push_back(klt2);
	}
	| LEFT_PAREN DK NegFormula RIGHT_PAREN
	{
		string agentName = $2->substr(3, $2->length()-3);
		$$ = new vector<KLDNF>(2);
		KLTerm klt1, klt2;
		klt2.LPart[agentName].push_back((*$3)[1]);
		klt1.KPart[agentName] = (*$3)[0];
		(*$$)[0].dnf.push_back(klt1);
		(*$$)[1].dnf.push_back(klt2);
	}
	| LEFT_PAREN NOT NegFormula RIGHT_PAREN
	{
		PropDNF preConstraint;
		preConstraint.dnf.push_back(PropTerm(atomNum));
		$$ = new vector<KLDNF>(2);
		(*$$)[0] = (*$3)[1];
		(*$$)[1] = (*$3)[0];
	}
	| LEFT_PAREN AND NegFormulaList RIGHT_PAREN
	{
		$$ = new vector<KLDNF>(2);
		for(size_t i = 0;i < (*$3)[0].size();i++) {
			(*$$)[0] = (*$$)[0].disjunction((*$3)[0][i]);
			(*$$)[1] = (*$$)[1].conjunction((*$3)[1][i]);
		}
	}
	| LEFT_PAREN OR NegFormulaList RIGHT_PAREN
	{
		$$ = new vector<KLDNF>(2);
		for(size_t i = 0;i < (*$3)[0].size();i++) {
			(*$$)[0] = (*$$)[0].conjunction((*$3)[0][i]);
			(*$$)[1] = (*$$)[1].disjunction((*$3)[1][i]);
		}
	};
NegFormulaList
	: NegFormula NegFormula
	{
		$$ = new vector<vector<KLDNF>>(2);
		(*$$)[0].push_back((*$1)[0]);
		(*$$)[0].push_back((*$2)[0]);
		(*$$)[1].push_back((*$1)[1]);
		(*$$)[1].push_back((*$2)[1]);
	}
	| NegFormulaList NegFormula
	{
		$$ = $1;
		(*$$)[0].push_back((*$2)[0]);
		(*$$)[1].push_back((*$2)[1]);
	};
NegFormulaAtom
	: LEFT_PAREN NameList RIGHT_PAREN
	{
		$$ = new vector<KLDNF>;
		KLDNF kld1, kld2;
		PropTerm pt1(atomNum), pt2(atomNum);
		KLTerm klt1, klt2;
		string atomName = "(" + *$2 + ")";
		if(atomName == "(True)") {
			pt1.literal[0] = UNSAT;
		}
		else {
			pt1.literal[findAtomsByName[atomName]] = FALSE;
			pt2.literal[findAtomsByName[atomName]] = TRUE;
		}
		klt1.PPart.dnf.push_back(pt1);
		klt2.PPart.dnf.push_back(pt2);
		kld1.dnf.push_back(klt1);
		kld2.dnf.push_back(klt2);
		$$->push_back(kld1);
		$$->push_back(kld2);
	};
ActionPart
	: SensingAction
	{

	}
	| OnticAction
	{

	}
	| ActionPart OnticAction
	{

	}
	| ActionPart SensingAction
	{

	};
SensingAction
	: LEFT_PAREN COLON ACTION NAME
	  COLON CATEGORY LEFT_PAREN NAME RIGHT_PAREN
	  ActionVar
	  COLON PRECONDITION NegGeneralFormula 
	  COLON OBSERVE_POS GeneralFormula
	  COLON OBSERVE_NEG GeneralFormula
	  RIGHT_PAREN
	{
		string actionNamePre = *$4;
		string actionType = *$8;
		for(size_t i = 0;i < actionVar.size();i++) {
			string actionName = actionNamePre + "(";
			for(size_t j = 0;j < actionVarSeq.size();j++) {
				actionName += (((j == 0) ? "" : ", ") + actionVar[i][actionVarSeq[j]]);
			}
			actionName += ")";
			SensingAction sa;
			sa.name = actionName;
			if (actionType == "ontic") { sa.category = ONTIC; }
			else if (actionType == "observation") { sa.category = OBSERVATION; }
			else if (actionType == "communication") { sa.category = COMMUNICATION; }
			else if (actionType == "sensing") { sa.category = SENSING; }
			else { cout << "something wrong in category in parse.y" << endl; }
			sa.preCon = (*$13)[i];
			sa.posRes = (*$16)[i];
			sa.negRes = (*$19)[i];
			sActions.push_back(sa);
		}
	}
	| LEFT_PAREN COLON ACTION NAME
	  COLON CATEGORY LEFT_PAREN NAME RIGHT_PAREN
	  COLON PARAMETERS LEFT_PAREN RIGHT_PAREN
	  COLON PRECONDITION NegFormula 
	  COLON OBSERVE_POS Formula
	  COLON OBSERVE_NEG Formula
	  RIGHT_PAREN
	{
		string actionName = *$4;
		string actionType = *$8;
		SensingAction sa;
		sa.name = actionName;
		if (actionType == "ontic") { sa.category = ONTIC; }
		else if (actionType == "observation") { sa.category = OBSERVATION; }
		else if (actionType == "communication") { sa.category = COMMUNICATION; }
		else if (actionType == "sensing") { sa.category = SENSING; }
		else { cout << "something wrong in category in parse.y" << endl; }
		sa.preCon = (*$16)[0];
		sa.posRes = (*$19);
		sa.negRes = (*$22);
		sActions.push_back(sa);
	};
ActionVar
	: COLON PARAMETERS LEFT_PAREN ActionVarList RIGHT_PAREN
	{	
		actionVar.clear();
		actionVarSeq.clear();
		if($4->empty()) {
			actionVar.push_back(map<string, string>());
		}
		else {
			for(map<string, string>::iterator ite = $4->begin();
				ite != $4->end();ite++) {
				actionVarSeq.push_back(ite->first);
			}
			map<string, vector<char> > visited;
			for(map<string, vector<string> >::iterator ite = objects.begin();
				ite != objects.end();ite++) {
				visited.insert(make_pair(ite->first, vector<char>(ite->second.size(), '0')));
			}
			visited.insert(make_pair("agent", vector<char>(agents.size(), '0')));
			actionVarGround(*$4, map<string, string>(), $4->begin(), visited);
		}
	};
ActionVarList
	: NAME CONNECTOR NAME
	{
		$$ = new map<string, string>;
		(*$$)[*$1] = *$3;
	}
	| ActionVarList NAME CONNECTOR NAME
	{
		$$ = $1;
		(*$$)[*$2] = *$4;
	};
GeneralFormula
	: GeneralFormulaAtom
	{
		$$ = new vector<KLDNF>;
		*$$ = *$1;
	}
	| LEFT_PAREN K GeneralFormula RIGHT_PAREN
	{
		$$ = new vector<KLDNF>;
		string generalAgentName = $2->substr(2, $2->length()-2);
		for(size_t i = 0;i < $3->size();i++) {
			string agentName = ((actionVar.empty() || actionVar[i].find(generalAgentName)
				== actionVar[i].end()) ? generalAgentName : actionVar[i][generalAgentName]);
			KLDNF kld;
			KLTerm klt;
			klt.KPart[agentName] = (*$3)[i];
			kld.dnf.push_back(klt);
			$$->push_back(kld);
		}
	}
	| LEFT_PAREN DK GeneralFormula RIGHT_PAREN
	{
		$$ = new vector<KLDNF>;
		string generalAgentName = $2->substr(3, $2->length()-3);
		for(size_t i = 0;i < $3->size();i++) {
			string agentName = ((actionVar.empty() || actionVar[i].find(generalAgentName)
				== actionVar[i].end()) ? generalAgentName : actionVar[i][generalAgentName]);
			KLDNF kld;
			KLTerm klt;
			klt.LPart[agentName].push_back((*$3)[i]);
			kld.dnf.push_back(klt);
			$$->push_back(kld);
		}
	}
	| LEFT_PAREN NOT GeneralFormula RIGHT_PAREN
	{
		$$ = new vector<KLDNF>;
		PropDNF preConstraint;
		preConstraint.dnf.push_back(PropTerm(atomNum));
		for(size_t i = 0;i < $3->size();i++) {
			$$->push_back((*$3)[i].negation(preConstraint));
		}
	}
	| LEFT_PAREN AND GeneralFormulaList RIGHT_PAREN
	{
		$$ = new vector<KLDNF>;
		size_t row = $3->size(), col = (*$3)[0].size();
		for(size_t j = 0;j < col;j++) {
			KLDNF kld;
			for(size_t i = 0;i < row;i++) {
				kld = kld.conjunction((*$3)[i][j]);
			}
			$$->push_back(kld);
		}
	}
	| LEFT_PAREN OR GeneralFormulaList RIGHT_PAREN
	{
		$$ = new vector<KLDNF>;
		size_t row = $3->size(), col = (*$3)[0].size();
		for(size_t j = 0;j < col;j++) {
			KLDNF kld;
			for(size_t i = 0;i < row;i++) {
				kld = kld.disjunction((*$3)[i][j]);
			}
			$$->push_back(kld);
		}
	};
GeneralFormulaList
	: GeneralFormula GeneralFormula
	{
		$$ = new vector<vector<KLDNF> >;
		$$->push_back(*$1);
		$$->push_back(*$2);
	}
	| GeneralFormulaList GeneralFormula
	{
		$$ = $1;
		$$->push_back(*$2);
	};
GeneralFormulaAtom
	: LEFT_PAREN GeneralNameList RIGHT_PAREN
	{
		$$ = new vector<KLDNF>;
		for(size_t i = 0;i < $2->size();i++) {
			PropTerm pt(atomNum);
			KLDNF kld;
			KLTerm klt;
			string atomName = "(" + (*$2)[i] + ")";
			if(atomName != "(True)") {
				pt.literal[findAtomsByName[atomName]] = TRUE;
			}
			klt.PPart.dnf.push_back(pt);
			kld.dnf.push_back(klt);
			$$->push_back(kld);
		}
	};
GeneralNameList
	: NAME
	{
		$$ = new vector<string>;
		for(size_t i = 0;i < actionVar.size();i++) {
			$$->push_back((actionVar[i].find(*$1) == actionVar[i].end()) ?
				*$1 : actionVar[i][*$1]);
		}
	}
	| GeneralNameList NAME
	{
		$$ = $1;
		for(size_t i = 0;i < actionVar.size();i++) {
			(*$$)[i] += (" " + ((actionVar[i].find(*$2) == actionVar[i].end()) ?
				*$2 : actionVar[i][*$2]));
		}
	};
OnticAction
	: LEFT_PAREN COLON ACTION NAME
	  COLON CATEGORY LEFT_PAREN NAME RIGHT_PAREN
	  ActionVar
	  COLON PRECONDITION NegGeneralFormula
	  COLON EFFECT LEFT_PAREN OnticResList RIGHT_PAREN
	  RIGHT_PAREN
	{
		string actionNamePre = *$4;
		string actionType = *$8;
		for(size_t i = 0;i < actionVar.size();i++) {
			string actionName = actionNamePre + "(";
			for(size_t j = 0;j < actionVarSeq.size();j++) {
				actionName += (((j == 0) ? "" : ", ") + actionVar[i][actionVarSeq[j]]);
			}
			actionName += ")";
			OnticAction oa;
			oa.name = actionName;

			if (actionType == "ontic") { oa.category = ONTIC; }
			else if (actionType == "observation") { oa.category = OBSERVATION; }
			else if (actionType == "communication") { oa.category = COMMUNICATION; }
			else if (actionType == "sensing") { oa.category = SENSING; }
			else { cout << "something wrong in category in parse.y" << endl; }

			oa.preCon = (*$13)[i];
			for(size_t j = 0;j < $17->size();j++) {
				ConditionalEffect ce;
				ce.condition = (*$17)[j][i][0];
				ce.effect = (*$17)[j][i][1];
				oa.eff.push_back(ce);
			}
			oActions.push_back(oa);
		}
	}
	| LEFT_PAREN COLON ACTION NAME
	  COLON CATEGORY LEFT_PAREN NAME RIGHT_PAREN
	  COLON PARAMETERS LEFT_PAREN RIGHT_PAREN
	  COLON PRECONDITION NegFormula
	  COLON EFFECT LEFT_PAREN SingleOnticResList RIGHT_PAREN
	  RIGHT_PAREN
	{
		string actionName = *$4;
		string actionType = *$8;
		OnticAction oa;
		oa.name = actionName;
		if (actionType == "ontic") { oa.category = ONTIC; }
		else if (actionType == "observation") { oa.category = OBSERVATION; }
		else if (actionType == "communication") { oa.category = COMMUNICATION; }
		else if (actionType == "sensing") { oa.category = SENSING; }
		else { cout << "something wrong in category in parse.y" << endl; }
		oa.preCon = (*$16)[0];
		for(size_t i = 0;i < (*$20).size();i++) {
			ConditionalEffect ce;
			ce.condition = (*$20)[i][0];
			ce.effect = (*$20)[i][1];
			oa.eff.push_back(ce);
		}
		oActions.push_back(oa);
	};
OnticResList
	: OnticRes
	{
		$$ = new vector<vector<vector<KLDNF>>>;
		$$->push_back(*$1);
	}
	| OnticResList OnticRes
	{
		$$ = $1;
		$$->push_back(*$2);
	};
OnticRes
	: LEFT_BRACKET
	  LEFT_BRACE NegGeneralFormula RIGHT_BRACE
	  LEFT_BRACE GeneralFormula RIGHT_BRACE
	  RIGHT_BRACKET
	{
		$$ = new vector<vector<KLDNF>>;
		for(size_t i = 0;i < actionVar.size();i++) {
			vector<KLDNF> temp;
			temp.push_back((*$3)[i]);
			temp.push_back((*$6)[i]);
			$$->push_back(temp);
		}
	};
SingleOnticResList
	: SingleOnticRes
	{
		$$ = new vector<vector<KLDNF>>;
		$$->push_back(*$1);
	}
	| SingleOnticResList SingleOnticRes
	{
		$$ = $1;
		$$->push_back(*$2);
	};
SingleOnticRes
	: LEFT_BRACKET
	  LEFT_BRACE NegFormula RIGHT_BRACE
	  LEFT_BRACE Formula RIGHT_BRACE
	  RIGHT_BRACKET
	{
		$$ = new vector<KLDNF>;
		$$->push_back((*$3)[0]);
		$$->push_back(*$6);
	};
NegGeneralFormula
	: NegGeneralFormulaAtom
	{
		$$ = new vector<KLDNF>;
		*$$ = *$1;
	}
	| LEFT_PAREN K NegGeneralFormula RIGHT_PAREN
	{
		$$ = new vector<KLDNF>;
		string generalAgentName = $2->substr(2, $2->length()-2);
		for(size_t i = 0;i < $3->size();i++) {
			string agentName = ((actionVar[i].find(generalAgentName)
				== actionVar[i].end()) ? generalAgentName : actionVar[i][generalAgentName]);
			KLDNF kld;
			KLTerm klt;
			klt.LPart[agentName].push_back((*$3)[i]);
			kld.dnf.push_back(klt);
			$$->push_back(kld);
		}
	}
	| LEFT_PAREN DK NegGeneralFormula RIGHT_PAREN
	{
		$$ = new vector<KLDNF>;
		string generalAgentName = $2->substr(3, $2->length()-3);
		for(size_t i = 0;i < $3->size();i++) {
			string agentName = ((actionVar[i].find(generalAgentName)
				== actionVar[i].end()) ? generalAgentName : actionVar[i][generalAgentName]);
			KLDNF kld;
			KLTerm klt;
			klt.KPart[agentName] = (*$3)[i];
			kld.dnf.push_back(klt);
			$$->push_back(kld);
		}
	}
	| LEFT_PAREN NOT NegGeneralFormula RIGHT_PAREN
	{
		$$ = new vector<KLDNF>;
		PropDNF preConstraint;
		preConstraint.dnf.push_back(PropTerm(atomNum));
		for(size_t i = 0;i < $3->size();i++) {
			$$->push_back((*$3)[i].negation(preConstraint));
		}
	}
	| LEFT_PAREN AND NegGeneralFormulaList RIGHT_PAREN
	{
		$$ = new vector<KLDNF>;
		size_t row = $3->size(), col = (*$3)[0].size();
		for(size_t j = 0;j < col;j++) {
			KLDNF kld;
			for(size_t i = 0;i < row;i++) {
				kld = kld.disjunction((*$3)[i][j]);
			}
			$$->push_back(kld);
		}
	}
	| LEFT_PAREN OR NegGeneralFormulaList RIGHT_PAREN
	{
		$$ = new vector<KLDNF>;
		size_t row = $3->size(), col = (*$3)[0].size();
		for(size_t j = 0;j < col;j++) {
			KLDNF kld;
			for(size_t i = 0;i < row;i++) {
				kld = kld.conjunction((*$3)[i][j]);
			}
			$$->push_back(kld);
		}
	};
NegGeneralFormulaList
	: NegGeneralFormula NegGeneralFormula
	{
		$$ = new vector<vector<KLDNF> >;
		$$->push_back(*$1);
		$$->push_back(*$2);
	}
	| NegGeneralFormulaList NegGeneralFormula
	{
		$$ = $1;
		$$->push_back(*$2);
	};
NegGeneralFormulaAtom
	: LEFT_PAREN GeneralNameList RIGHT_PAREN
	{
		$$ = new vector<KLDNF>;
		for(size_t i = 0;i < $2->size();i++) {
			PropTerm pt(atomNum);
			KLDNF kld;
			KLTerm klt;
			string atomName = "(" + (*$2)[i] + ")";
			if(atomName != "(True)") {
				pt.literal[findAtomsByName[atomName]] = FALSE;
			}
			else {
				pt.literal[0] = UNSAT;
			}
			klt.PPart.dnf.push_back(pt);
			kld.dnf.push_back(klt);
			$$->push_back(kld);
		}
	};
%%

int yyerror(char* s) {
	return 0;
}

int yyerror(std::string s) {
	return 0;
}