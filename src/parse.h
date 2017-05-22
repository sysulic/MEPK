/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NAME = 258,
     K = 259,
     DK = 260,
     AND = 261,
     OR = 262,
     NOT = 263,
     IMPLY = 264,
     ONEOF = 265,
     TRUE = 266,
     FALSE = 267,
     LEFT_PAREN = 268,
     RIGHT_PAREN = 269,
     LEFT_BRACE = 270,
     RIGHT_BRACE = 271,
     LEFT_BRACKET = 272,
     RIGHT_BRACKET = 273,
     COMMA = 274,
     COLON = 275,
     CONNECTOR = 276,
     DEFINE = 277,
     DOMAIN = 278,
     TYPES = 279,
     PREDICATES = 280,
     PRECONDITION = 281,
     ACTION = 282,
     CATEGORY = 283,
     PARAMETERS = 284,
     OBSERVE_POS = 285,
     OBSERVE_NEG = 286,
     EFFECT = 287,
     PROBLEM = 288,
     OBJECTS = 289,
     AGENTS = 290,
     INIT = 291,
     CONSTRAINT = 292,
     GOAL = 293
   };
#endif
/* Tokens.  */
#define NAME 258
#define K 259
#define DK 260
#define AND 261
#define OR 262
#define NOT 263
#define IMPLY 264
#define ONEOF 265
#define TRUE 266
#define FALSE 267
#define LEFT_PAREN 268
#define RIGHT_PAREN 269
#define LEFT_BRACE 270
#define RIGHT_BRACE 271
#define LEFT_BRACKET 272
#define RIGHT_BRACKET 273
#define COMMA 274
#define COLON 275
#define CONNECTOR 276
#define DEFINE 277
#define DOMAIN 278
#define TYPES 279
#define PREDICATES 280
#define PRECONDITION 281
#define ACTION 282
#define CATEGORY 283
#define PARAMETERS 284
#define OBSERVE_POS 285
#define OBSERVE_NEG 286
#define EFFECT 287
#define PROBLEM 288
#define OBJECTS 289
#define AGENTS 290
#define INIT 291
#define CONSTRAINT 292
#define GOAL 293




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 17 "parse.y"
{
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
/* Line 1529 of yacc.c.  */
#line 143 "parse.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

