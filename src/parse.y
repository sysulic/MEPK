 /*
 * File: parse.l
 * Description: A parser for a sepecific file type epddl.
 *
 * Created by Biqing Fang on 10/25/2015.
 */
%{
#include "reader.h"

int yyerror(char *s);
int yylex(void);

extern Reader reader;

%}

%union{
  string* str;
  ACTION_TYPE* act_type;
  StringSet* str_set;
  StringList* str_list;
  SingleTypePair* singletype_pair;
  MultiTypeList* multitype_list;
  MultiTypePair* multitype_pair;
  PredicateSet* pre_set;
  Effect* eff;
  EffectList* eff_set;
  PreEpistemicAction* epistemic_action;
  PreOnticAction* ontic_action;
  PreEpistemicActionList* epistemic_list;
  PreOnticActionList* ontic_list;
  Formula* tree;
}

%start epddlDoc

%token <str> NAME

%token <str> K
%token <str> DK
%token AND
%token OR
%token NOT
%token IMPLY
%token ONEOF

%token <str> TRUE
%token <str> FALSE

// marks
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
%token DOMAIN
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

%type <str> domainName

%type <str_set> typesDef
%type <str_set> primTypes
%type <str> primType

%type <pre_set> predicatesDef
%type <pre_set> atomicFormulaSkeletons
%type <multitype_pair> atomicFormulaSkeleton
%type <str> predicate
%type <multitype_list> typedVariableList
%type <singletype_pair> singleTypeVarList
%type <str_list> variables

%type <tree> aft_condition
%type <tree> con_effect
%type <eff> effect
%type <eff_set> effects
%type <str> actionSymbol
%type <act_type> category
%type <multitype_list> parameters
%type <tree> observe_pos
%type <tree> observe_neg
%type <epistemic_action> epistemicAction
%type <ontic_action> onticAction

%type <tree> precondition
%type <tree> formula
%type <tree> episFormula
%type <tree> objFormula
%type <tree> formulas

%type <str> problemDecl
%type <str> atomicProp

%type <multitype_list> objectsDecl
%type <str_list> agentsDecl
%type <multitype_list> objectTypes
%type <singletype_pair> singleType
%type <str_list> objects
%type <str> object

%type <tree> init
%type <tree> constraint
%type <tree> goal
%%

/******************* Start of grammar *************************/

epddlDoc : domain | problem;

/************* DOMAINS ****************************/

domain
	:	LEFT_PAREN
			DEFINE domainName
			typesDef
			predicatesDef
			actionsDef
		RIGHT_PAREN
	{
		reader.domainName = *$3;
		reader.types = *$4;
		reader.predicates = *$5;
		// cout << "domain done" << endl;
	}
	;
domainName
	:	LEFT_PAREN DOMAIN NAME RIGHT_PAREN
	{
		$$ = $3;
	}
	;

/******** typesdef ********/
typesDef
	:	LEFT_PAREN COLON TYPES primTypes RIGHT_PAREN
	{
		$$ = $4;
	}
	|	LEFT_PAREN COLON TYPES RIGHT_PAREN
	{
		$$ = new StringSet;
	}
	;
primTypes
	:	primTypes primType
	{
		$$ = $1;
		$$->insert(*$2);
	}
	|	primType
	{
		$$ = new StringSet;
		$$->insert(*$1);
	}
	;
primType
	:	NAME
	{
		$$ =  new string(*$1);
	}
	;

/***** predicatesdef *****/
predicatesDef
	:	LEFT_PAREN COLON PREDICATES atomicFormulaSkeletons RIGHT_PAREN
	{
		$$ = $4;
	}
	|	LEFT_PAREN COLON PREDICATES RIGHT_PAREN
	{
		$$ = new PredicateSet;
	}
	;
atomicFormulaSkeletons
	:	atomicFormulaSkeletons atomicFormulaSkeleton
	{
		$$ = $1;
		$$->insert(*$2);
	}
	|	atomicFormulaSkeleton
	{
		$$ = new PredicateSet;
		$$->insert(*$1);
	}
	;
atomicFormulaSkeleton
	:	LEFT_PAREN predicate typedVariableList RIGHT_PAREN
	{
		$$ = new MultiTypePair;
		$$->first = *$2;
		$$->second = *$3;
	}
	;
predicate
	:	NAME
	{ 
		$$ = $1;
	}
	;
typedVariableList
	:	typedVariableList singleTypeVarList
	{
		$$ = $1;
		$$->push_back(*$2);
	}
	|	singleTypeVarList
	{
		$$ = new MultiTypeList;
		$$->push_back(*$1);
	}
	;
singleTypeVarList
	:	variables CONNECTOR primType
	{
		$$ = new SingleTypePair;
		$$->first = *$3;
		$$->second = *$1;
	}
	;
variables
	:	variables NAME
	{
		$$ = $1;
		$$->push_back(*$2);
	}
	|	NAME
	{
		$$ = new StringList;
		$$->push_back(*$1);
	}
	;
/****** actionsdef ******/
actionsDef
	:	actionsDef action
	|	action
	;
action
	:	epistemicAction { reader.epistemicActions.insert(reader.epistemicActions.begin(), *$1); }
	|	onticAction { reader.onticActions.insert(reader.onticActions.begin(), *$1); }
	;
epistemicAction
	:	LEFT_PAREN
			COLON ACTION actionSymbol
			COLON CATEGORY LEFT_PAREN category RIGHT_PAREN
			COLON PARAMETERS LEFT_PAREN parameters RIGHT_PAREN
			COLON PRECONDITION LEFT_PAREN precondition RIGHT_PAREN
			COLON OBSERVE_POS LEFT_PAREN observe_pos RIGHT_PAREN
			COLON OBSERVE_NEG LEFT_PAREN observe_neg RIGHT_PAREN
		RIGHT_PAREN
	{
		$$ = new PreEpistemicAction;
		$$->name = *$4;
		$$->category = *$8;
		$$->paras = *$13;
		$$->preCondition = *$18;
		$$->observe_pos = *$23;
		$$->observe_neg = *$28;
		// cout << "epistemicActions done" << endl;
	}
	;
onticAction
	:	LEFT_PAREN
			COLON ACTION actionSymbol
			COLON CATEGORY LEFT_PAREN category RIGHT_PAREN
			COLON PARAMETERS LEFT_PAREN parameters RIGHT_PAREN
			COLON PRECONDITION LEFT_PAREN precondition RIGHT_PAREN
			COLON EFFECT LEFT_PAREN effects RIGHT_PAREN
		RIGHT_PAREN
	{
		$$ = new PreOnticAction;
		$$->name = *$4;
		$$->category = *$8;
		$$->paras = *$13;
		$$->preCondition = *$18;
		$$->effects = *$23;	
		// cout << "onticAction done" << endl;
	}
	;
actionSymbol
	:	NAME { $$ = $1; }
	;
/** category **/
category
	:	NAME
	{
		if (*$1 == "ontic") { *$$ = ONTIC; }
		else if (*$1 == "observation") { *$$ = OBSERVATION; }
		else if (*$1 == "communication") { *$$ = COMMUNICATION; }
		else if (*$1 == "sensing") { *$$ = SENSING; }
		else { cout << "something wrong in category in parse.y" << endl; }
	}
	;
/** parameters **/
parameters
	:	typedVariableList { $$ = $1; }
	|	{ $$ = new MultiTypeList; }
	;
/** precondition **/
precondition
	:	formula 	{ $$ = $1; }
	;
// definition of any kinds of formulas which include 'K' or not
formula
	:	episFormula 		{ $$ = $1; }
	|	objFormula 			{ $$ = $1; }
	;
formulas
	:	formulas LEFT_PAREN formula RIGHT_PAREN
	{
		if ($1->right == NULL) {
			$$ = $1;
		} else {
			$$ = new Formula("same", $1, NULL);
		}
		$$->right = $3;
	}
	|	LEFT_PAREN formula RIGHT_PAREN
	{
		$$ = new Formula("same", $2, NULL);
	}
	;
episFormula
	:	K LEFT_PAREN formula RIGHT_PAREN
	{
		$$ = new Formula(*$1, $3, NULL);
	}
	|	DK LEFT_PAREN formula RIGHT_PAREN
	{
		$$ = new Formula(*$1, $3, NULL);
	}
	;
objFormula
	:	AND formulas		{ $$ = new Formula("&", $2->left, $2->right); }
	|	OR formulas			{ $$ = new Formula("|", $2->left, $2->right); }
	|	NOT formulas		{ $$ = new Formula("!", $2->left, $2->right); }
	|	IMPLY formulas		{ $$ = new Formula("->", $2->left, $2->right); }
	|	ONEOF formulas		{ $$ = new Formula("oneof", $2->left, $2->right); }
	|	atomicProp			{ $$ = new Formula(*$1); }
	;
atomicProp
	:   TRUE	{ $$ = $1; }
	|	FALSE	{ $$ = $1; }
    |	predicate variables
	{
		$$ = new string(*$1);
		bool variable_exist = false;
		for (StringList::iterator ssi = (*$2).begin(); ssi != (*$2).end(); ssi++)
		{
			if ((*ssi)[0] == '?') variable_exist = true;
			*$$ += " " + *ssi;
		}
		if (!variable_exist) reader.atomicPropSet.insert(*$$);
	}
	|	NAME { $$ = $1; reader.atomicPropSet.insert(*$1); }
	;
/** observe_pos **/
observe_pos
	:	formula { $$ = $1; }
	;
/** observe_neg **/
observe_neg
	:	formula { $$ = $1; }
	;
/** effect **/
effects
	:	effects LEFT_BRACKET effect RIGHT_BRACKET
	{
		$$ = $1;
		$$->insert($$->begin(), *$3);
	}
	|	LEFT_BRACKET effect RIGHT_BRACKET
	{
		$$ = new EffectList;
		$$->insert($$->begin(), *$2);
	}
	;
effect
	:	LEFT_BRACE aft_condition RIGHT_BRACE LEFT_BRACE con_effect RIGHT_BRACE
	{
		$$ = new Effect;
		$$->aft_condition = *$2;
		$$->con_effect = *$5;
	}
	;
aft_condition
	:	formula { $$ = $1; }
	;
con_effect
	:	formula { $$ = $1; }
	;
/************* PROBLEMS ***************************/

problem
	:	LEFT_PAREN
			DEFINE problemDecl
			problemDomain
			objectsDecl
			agentsDecl
			init
			constraint
			goal
		RIGHT_PAREN
	{
		reader.problemName = *$3;
		reader.objects = *$5;
		reader.agents = *$6;
		reader.init = *$7;
		reader.constraint = *$8;
		reader.goal = *$9;
		// cout << "problem done" << endl;
	}
	;
problemDecl
	:	LEFT_PAREN PROBLEM NAME RIGHT_PAREN
	{
		$$ = $3;
	}
	;
problemDomain
	:	LEFT_PAREN COLON DOMAIN NAME RIGHT_PAREN
	;
/** objectdecl **/
objectsDecl
	:	LEFT_PAREN COLON OBJECTS objectTypes RIGHT_PAREN
	{
		$$ = $4;
	}
	|	LEFT_PAREN COLON OBJECTS RIGHT_PAREN
	{
		$$ = new MultiTypeList;
	}
	;
agentsDecl
	:	LEFT_PAREN COLON AGENTS objects RIGHT_PAREN
 	{
 		$$ = $4;
 	}
	;
objectTypes
	:	objectTypes singleType
	{
		$$ = $1;
		$$->push_back(*$2);
	}
	|	singleType
	{
		$$ = new MultiTypeList;
		$$->push_back(*$1);
	}
	;
singleType
	:	objects CONNECTOR primType
	{
		$$ = new SingleTypePair;
		$$->first = *$3;
		$$->second = *$1;
	}
	;
objects
	:	objects object
	{
		$$ = $1;
		$$->push_back(*$2);
	}
	|	object
	{
		$$ = new StringList;
		$$->push_back(*$1);
	}
	;
object
	:	NAME { $$ = $1; }
	;
/** init **/
init
	:	LEFT_PAREN COLON INIT LEFT_PAREN formula RIGHT_PAREN RIGHT_PAREN
	{
		$$ = $5;
		// cout << "init done" << endl;
	}
	;
/** constraint **/
constraint
	:	LEFT_PAREN COLON CONSTRAINT LEFT_PAREN objFormula RIGHT_PAREN RIGHT_PAREN
	{
		$$ = $5;
		// cout << "constraint done" << endl;
	}
	;
/** goal **/
goal
	:	LEFT_PAREN COLON GOAL LEFT_PAREN formula RIGHT_PAREN RIGHT_PAREN
	{
		$$ = $5;
		// cout << "goal done" << endl;
	}
	;

%%

int yyerror(string s)
{
  extern int yylineno;	// defined and maintained in lex.c
  extern char *yytext;	// defined and maintained in lex.c
  
  cerr << "ERROR: " << s << " at symbol \"" << yytext;
  cerr << "\" on line " << yylineno << endl;
  exit(1);
  return 0;
}

int yyerror(char *s)  // 当yacc遇到语法错误时，会回调yyerror函数，并且把错误信息放在参数s中
{
	return yyerror(string(s));
}
