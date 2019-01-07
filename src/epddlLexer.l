%{
#include "define.h"
#include "epddlParser.h"

using namespace std;

int yyerror(char* s);
%}

name			[a-zA-Z0-9\?][a-zA-Z_0-9\-]*
k				K_[a-zA-Z0-9\?]+
dk				DK_[a-zA-Z0-9]+

%%
"and"				{ return AND; }
"or"				{ return OR; }
"not"				{ return NOT; }
"imply"				{ return IMPLY; }
"oneof"				{ return ONEOF; }

"("					{ return LEFT_PAREN; }
")"					{ return RIGHT_PAREN; }
"{"					{ return LEFT_BRACE; }
"}"					{ return RIGHT_BRACE; }
"<"					{ return LEFT_BRACKET; }
">"					{ return RIGHT_BRACKET; }
","					{ return COMMA; }
":"					{ return COLON; }
"-"					{ return CONNECTOR; }

"define"			{ return DEFINE; }
"domain"			{ return LDOMAIN; }
"types"				{ return TYPES; }
"predicates"		{ return PREDICATES; }
"precondition"		{ return PRECONDITION; }
"action" 			{ return ACTION; }
"category"			{ return CATEGORY; }
"parameters"		{ return PARAMETERS; }
"observe_pos"		{ return OBSERVE_POS; }
"observe_neg"		{ return OBSERVE_NEG; }
"effect"			{ return EFFECT; }
"problem"			{ yylineno = 1; return PROBLEM; }
"objects"			{ return OBJECTS; }
"agents"			{ return AGENTS; }
"init"				{ return INIT; }
"constraint"		{ return CONSTRAINT; }
"goal"				{ return GOAL; }



{k}					{ yylval.str = new string(yytext); return K; }
{dk}				{ yylval.str = new string(yytext); return DK; }
{name}				{ yylval.str = new string(yytext); return NAME; }
\n 					{ yylineno++; }

[ \t\r\n]      ;

%%

int yywrap(void) {
	return 1;
}