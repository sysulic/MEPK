/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 7 "parse.y"

#include "reader.h"

int yyerror(char *s);
int yylex(void);

extern Reader reader;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 200 "parse.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 213 "parse.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   208

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNRULES -- Number of states.  */
#define YYNSTATES  192

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    15,    20,    26,    31,    34,
      36,    38,    44,    49,    52,    54,    59,    61,    64,    66,
      70,    73,    75,    78,    80,    82,    84,   115,   141,   143,
     145,   147,   148,   150,   152,   154,   159,   163,   168,   173,
     176,   179,   182,   185,   188,   190,   192,   194,   197,   199,
     201,   203,   208,   212,   219,   221,   223,   234,   239,   245,
     251,   256,   262,   265,   267,   271,   274,   276,   278,   286,
     294
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      40,     0,    -1,    41,    -1,    72,    -1,    13,    22,    42,
      43,    46,    53,    14,    -1,    13,    23,     3,    14,    -1,
      13,    20,    24,    44,    14,    -1,    13,    20,    24,    14,
      -1,    44,    45,    -1,    45,    -1,     3,    -1,    13,    20,
      25,    47,    14,    -1,    13,    20,    25,    14,    -1,    47,
      48,    -1,    48,    -1,    13,    49,    50,    14,    -1,     3,
      -1,    50,    51,    -1,    51,    -1,    52,    21,    45,    -1,
      52,     3,    -1,     3,    -1,    53,    54,    -1,    54,    -1,
      55,    -1,    56,    -1,    13,    20,    27,    57,    20,    28,
      13,    58,    14,    20,    29,    13,    59,    14,    20,    26,
      13,    60,    14,    20,    30,    13,    66,    14,    20,    31,
      13,    67,    14,    14,    -1,    13,    20,    27,    57,    20,
      28,    13,    58,    14,    20,    29,    13,    59,    14,    20,
      26,    13,    60,    14,    20,    32,    13,    68,    14,    14,
      -1,     3,    -1,     3,    -1,    50,    -1,    -1,    61,    -1,
      63,    -1,    64,    -1,    62,    13,    61,    14,    -1,    13,
      61,    14,    -1,     4,    13,    61,    14,    -1,     5,    13,
      61,    14,    -1,     6,    62,    -1,     7,    62,    -1,     8,
      62,    -1,     9,    62,    -1,    10,    62,    -1,    65,    -1,
      11,    -1,    12,    -1,    49,    52,    -1,     3,    -1,    61,
      -1,    61,    -1,    68,    17,    69,    18,    -1,    17,    69,
      18,    -1,    15,    70,    16,    15,    71,    16,    -1,    61,
      -1,    61,    -1,    13,    22,    73,    74,    75,    76,    81,
      82,    83,    14,    -1,    13,    33,     3,    14,    -1,    13,
      20,    23,     3,    14,    -1,    13,    20,    34,    77,    14,
      -1,    13,    20,    34,    14,    -1,    13,    20,    35,    79,
      14,    -1,    77,    78,    -1,    78,    -1,    79,    21,    45,
      -1,    79,    80,    -1,    80,    -1,     3,    -1,    13,    20,
      36,    13,    61,    14,    14,    -1,    13,    20,    37,    13,
      64,    14,    14,    -1,    13,    20,    38,    13,    61,    14,
      14,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   128,   128,   128,   133,   147,   155,   159,   165,   170,
     177,   185,   189,   195,   200,   207,   215,   221,   226,   233,
     241,   246,   254,   255,   258,   259,   262,   282,   300,   304,
     315,   316,   320,   324,   325,   328,   337,   343,   347,   353,
     354,   355,   356,   357,   358,   361,   362,   363,   374,   378,
     382,   386,   391,   398,   406,   409,   414,   434,   440,   444,
     448,   454,   460,   465,   472,   480,   485,   492,   496,   504,
     512
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME", "K", "DK", "AND", "OR", "NOT",
  "IMPLY", "ONEOF", "TRUE", "FALSE", "LEFT_PAREN", "RIGHT_PAREN",
  "LEFT_BRACE", "RIGHT_BRACE", "LEFT_BRACKET", "RIGHT_BRACKET", "COMMA",
  "COLON", "CONNECTOR", "DEFINE", "DOMAIN", "TYPES", "PREDICATES",
  "PRECONDITION", "ACTION", "CATEGORY", "PARAMETERS", "OBSERVE_POS",
  "OBSERVE_NEG", "EFFECT", "PROBLEM", "OBJECTS", "AGENTS", "INIT",
  "CONSTRAINT", "GOAL", "$accept", "epddlDoc", "domain", "domainName",
  "typesDef", "primTypes", "primType", "predicatesDef",
  "atomicFormulaSkeletons", "atomicFormulaSkeleton", "predicate",
  "typedVariableList", "singleTypeVarList", "variables", "actionsDef",
  "action", "epistemicAction", "onticAction", "actionSymbol", "category",
  "parameters", "precondition", "formula", "formulas", "episFormula",
  "objFormula", "atomicProp", "observe_pos", "observe_neg", "effects",
  "effect", "aft_condition", "con_effect", "problem", "problemDecl",
  "problemDomain", "objectsDecl", "agentsDecl", "objectTypes",
  "singleType", "objects", "object", "init", "constraint", "goal", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    40,    41,    42,    43,    43,    44,    44,
      45,    46,    46,    47,    47,    48,    49,    50,    50,    51,
      52,    52,    53,    53,    54,    54,    55,    56,    57,    58,
      59,    59,    60,    61,    61,    62,    62,    63,    63,    64,
      64,    64,    64,    64,    64,    65,    65,    65,    65,    66,
      67,    68,    68,    69,    70,    71,    72,    73,    74,    75,
      75,    76,    77,    77,    78,    79,    79,    80,    81,    82,
      83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     7,     4,     5,     4,     2,     1,
       1,     5,     4,     2,     1,     4,     1,     2,     1,     3,
       2,     1,     2,     1,     1,     1,    30,    25,     1,     1,
       1,     0,     1,     1,     1,     4,     3,     4,     4,     2,
       2,     2,     2,     2,     1,     1,     1,     2,     1,     1,
       1,     4,     3,     6,     1,     1,    10,     4,     5,     5,
       4,     5,     2,     1,     3,     2,     1,     1,     7,     7,
       7
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     3,     0,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,    57,     0,     0,     0,     0,
      23,    24,    25,     0,     0,     0,     0,    10,     7,     0,
       9,     0,     0,     4,    22,     0,     0,     0,     0,     0,
       6,     8,     0,    12,     0,    14,     0,    58,    67,    60,
       0,    63,     0,    66,     0,     0,     0,     0,    16,     0,
      11,    13,    28,     0,    59,    62,     0,    65,     0,     0,
       0,     0,     0,    21,     0,    18,     0,     0,    64,    61,
       0,     0,     0,    56,    15,    17,    20,     0,     0,    48,
       0,     0,     0,     0,     0,     0,     0,    45,    46,     0,
       0,    33,    34,    44,     0,     0,    19,     0,     0,     0,
       0,    39,    40,    41,    42,    43,    47,     0,     0,     0,
      29,     0,     0,     0,     0,     0,    68,     0,     0,     0,
      37,    38,    36,     0,    69,     0,     0,    35,    70,     0,
      31,    30,     0,     0,     0,     0,     0,     0,    32,     0,
       0,     0,     0,     0,     0,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    54,     0,    52,    27,     0,
       0,     0,    51,     0,     0,    50,     0,    55,     0,     0,
      53,    26
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     8,    13,    39,    40,    20,    54,    55,
     109,    84,    85,    86,    29,    30,    31,    32,    73,   131,
     152,   157,   110,   121,   111,   112,   113,   166,   186,   168,
     171,   176,   188,     4,     9,    15,    23,    36,    60,    61,
      62,    63,    49,    67,    82
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -116
static const yytype_int16 yypact[] =
{
      -4,    -9,    17,  -116,  -116,    27,  -116,     6,    34,    38,
      55,    59,    10,    50,    44,    52,    66,    68,    42,    61,
      70,    62,    64,    73,  -116,  -116,     5,    63,    69,    40,
    -116,  -116,  -116,    84,    56,    71,    79,  -116,  -116,     7,
    -116,    43,    72,  -116,  -116,    80,     8,    58,    75,    83,
    -116,  -116,    94,  -116,    47,  -116,    95,  -116,  -116,  -116,
       9,  -116,     3,  -116,    97,    65,    82,    90,  -116,   101,
    -116,  -116,  -116,    85,  -116,  -116,   103,  -116,    12,    96,
      74,    87,    98,  -116,    13,  -116,     4,    86,  -116,  -116,
      67,   100,    77,  -116,  -116,  -116,  -116,   103,   104,   105,
     106,   107,   108,   108,   108,   108,   108,  -116,  -116,   101,
     102,  -116,  -116,  -116,    25,   109,  -116,   115,    67,    67,
      67,   110,   110,   110,   110,   110,   121,   111,   112,    67,
    -116,   113,   114,   116,   117,    67,  -116,   118,   119,   120,
    -116,  -116,  -116,   122,  -116,   123,    81,  -116,  -116,   125,
     101,   101,   127,   124,   126,   129,    67,   131,  -116,   128,
      20,   130,   133,    67,   132,  -116,   136,   138,    32,   134,
      67,   137,   142,   138,   135,  -116,   141,  -116,  -116,   140,
     146,   145,  -116,    67,    67,  -116,   147,  -116,   148,   149,
    -116,  -116
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -116,  -116,  -116,  -116,  -116,  -116,   -38,  -116,  -116,    93,
      99,   -21,   -84,    26,  -116,   139,  -116,  -116,  -116,  -116,
    -116,  -116,  -115,   -61,  -116,    48,  -116,  -116,  -116,  -116,
     -39,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,   143,
     144,   -60,  -116,  -116,  -116
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -17
static const yytype_int16 yytable[] =
{
      95,    51,    77,   132,   133,   134,    58,    96,    37,     1,
      37,    58,    58,     5,   138,    58,    83,     6,    77,    38,
     143,    50,    59,    74,    76,    97,    89,    94,    99,    10,
      18,   102,   103,   104,   105,   106,   107,   108,    88,    11,
       7,   158,   122,   123,   124,   125,   172,    12,   165,   173,
     161,    14,   162,    28,    43,   175,    52,    53,    16,   116,
      52,    70,    17,    19,    21,    22,    26,    95,   185,   187,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
      24,    27,    25,    28,    34,    33,    35,    45,    41,    42,
      46,    47,    48,    64,    57,    65,    66,    68,    72,    56,
      58,    79,    80,    81,    83,    87,    37,    92,   -16,    90,
     149,    91,    93,   114,    98,   115,   127,   117,   130,   118,
     119,   120,   129,   135,    96,   136,   137,   139,   140,   151,
     141,   142,   144,   145,   179,   126,   147,   148,   150,     0,
     146,   153,   156,   163,   154,   159,   164,    71,   160,   167,
     169,    69,   155,   170,   174,   177,   178,   181,   182,   183,
     184,   189,   128,   191,   190,     0,   180,     0,    44,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    75,     0,     0,     0,     0,    78
};

static const yytype_int16 yycheck[] =
{
      84,    39,    62,   118,   119,   120,     3,     3,     3,    13,
       3,     3,     3,    22,   129,     3,     3,     0,    78,    14,
     135,    14,    14,    14,    21,    21,    14,    14,     3,    23,
      20,     6,     7,     8,     9,    10,    11,    12,    76,    33,
      13,   156,   103,   104,   105,   106,    14,    13,   163,    17,
      30,    13,    32,    13,    14,   170,    13,    14,     3,    97,
      13,    14,     3,    13,    20,    13,    24,   151,   183,   184,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      14,    20,    14,    13,    20,    23,    13,     3,    25,    20,
      34,    20,    13,    35,    14,    20,    13,     3,     3,    27,
       3,    36,    20,    13,     3,    20,     3,    20,     3,    13,
      29,    37,    14,    13,    28,    38,    14,    13,     3,    13,
      13,    13,    13,    13,     3,    14,    14,    14,    14,   150,
      14,    14,    14,    14,   173,   109,    14,    14,    13,    -1,
      20,    14,    13,    13,    20,    14,    13,    54,    20,    17,
      14,    52,    26,    15,    20,    18,    14,    16,    18,    13,
      15,    14,   114,    14,    16,    -1,    31,    -1,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    64
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    40,    41,    72,    22,     0,    13,    42,    73,
      23,    33,    13,    43,    13,    74,     3,     3,    20,    13,
      46,    20,    13,    75,    14,    14,    24,    20,    13,    53,
      54,    55,    56,    23,    20,    13,    76,     3,    14,    44,
      45,    25,    20,    14,    54,     3,    34,    20,    13,    81,
      14,    45,    13,    14,    47,    48,    27,    14,     3,    14,
      77,    78,    79,    80,    35,    20,    13,    82,     3,    49,
      14,    48,     3,    57,    14,    78,    21,    80,    79,    36,
      20,    13,    83,     3,    50,    51,    52,    20,    45,    14,
      13,    37,    20,    14,    14,    51,     3,    21,    28,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    49,
      61,    63,    64,    65,    13,    38,    45,    13,    13,    13,
      13,    62,    62,    62,    62,    62,    52,    14,    64,    13,
       3,    58,    61,    61,    61,    13,    14,    14,    61,    14,
      14,    14,    14,    61,    14,    14,    20,    14,    14,    29,
      13,    50,    59,    14,    20,    26,    13,    60,    61,    14,
      20,    30,    32,    13,    13,    61,    66,    17,    68,    14,
      15,    69,    14,    17,    20,    61,    70,    18,    14,    69,
      31,    16,    18,    13,    15,    61,    67,    61,    71,    14,
      16,    14
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 139 "parse.y"
    {
		reader.domainName = *(yyvsp[(3) - (7)].str);
		reader.types = *(yyvsp[(4) - (7)].str_set);
		reader.predicates = *(yyvsp[(5) - (7)].pre_set);
		// cout << "domain done" << endl;
	;}
    break;

  case 5:
#line 148 "parse.y"
    {
		(yyval.str) = (yyvsp[(3) - (4)].str);
	;}
    break;

  case 6:
#line 156 "parse.y"
    {
		(yyval.str_set) = (yyvsp[(4) - (5)].str_set);
	;}
    break;

  case 7:
#line 160 "parse.y"
    {
		(yyval.str_set) = new StringSet;
	;}
    break;

  case 8:
#line 166 "parse.y"
    {
		(yyval.str_set) = (yyvsp[(1) - (2)].str_set);
		(yyval.str_set)->insert(*(yyvsp[(2) - (2)].str));
	;}
    break;

  case 9:
#line 171 "parse.y"
    {
		(yyval.str_set) = new StringSet;
		(yyval.str_set)->insert(*(yyvsp[(1) - (1)].str));
	;}
    break;

  case 10:
#line 178 "parse.y"
    {
		(yyval.str) =  new string(*(yyvsp[(1) - (1)].str));
	;}
    break;

  case 11:
#line 186 "parse.y"
    {
		(yyval.pre_set) = (yyvsp[(4) - (5)].pre_set);
	;}
    break;

  case 12:
#line 190 "parse.y"
    {
		(yyval.pre_set) = new PredicateSet;
	;}
    break;

  case 13:
#line 196 "parse.y"
    {
		(yyval.pre_set) = (yyvsp[(1) - (2)].pre_set);
		(yyval.pre_set)->insert(*(yyvsp[(2) - (2)].multitype_pair));
	;}
    break;

  case 14:
#line 201 "parse.y"
    {
		(yyval.pre_set) = new PredicateSet;
		(yyval.pre_set)->insert(*(yyvsp[(1) - (1)].multitype_pair));
	;}
    break;

  case 15:
#line 208 "parse.y"
    {
		(yyval.multitype_pair) = new MultiTypePair;
		(yyval.multitype_pair)->first = *(yyvsp[(2) - (4)].str);
		(yyval.multitype_pair)->second = *(yyvsp[(3) - (4)].multitype_list);
	;}
    break;

  case 16:
#line 216 "parse.y"
    { 
		(yyval.str) = (yyvsp[(1) - (1)].str);
	;}
    break;

  case 17:
#line 222 "parse.y"
    {
		(yyval.multitype_list) = (yyvsp[(1) - (2)].multitype_list);
		(yyval.multitype_list)->push_back(*(yyvsp[(2) - (2)].singletype_pair));
	;}
    break;

  case 18:
#line 227 "parse.y"
    {
		(yyval.multitype_list) = new MultiTypeList;
		(yyval.multitype_list)->push_back(*(yyvsp[(1) - (1)].singletype_pair));
	;}
    break;

  case 19:
#line 234 "parse.y"
    {
		(yyval.singletype_pair) = new SingleTypePair;
		(yyval.singletype_pair)->first = *(yyvsp[(3) - (3)].str);
		(yyval.singletype_pair)->second = *(yyvsp[(1) - (3)].str_list);
	;}
    break;

  case 20:
#line 242 "parse.y"
    {
		(yyval.str_list) = (yyvsp[(1) - (2)].str_list);
		(yyval.str_list)->push_back(*(yyvsp[(2) - (2)].str));
	;}
    break;

  case 21:
#line 247 "parse.y"
    {
		(yyval.str_list) = new StringList;
		(yyval.str_list)->push_back(*(yyvsp[(1) - (1)].str));
	;}
    break;

  case 24:
#line 258 "parse.y"
    { reader.epistemicActions.insert(reader.epistemicActions.begin(), *(yyvsp[(1) - (1)].epistemic_action)); ;}
    break;

  case 25:
#line 259 "parse.y"
    { reader.onticActions.insert(reader.onticActions.begin(), *(yyvsp[(1) - (1)].ontic_action)); ;}
    break;

  case 26:
#line 270 "parse.y"
    {
		(yyval.epistemic_action) = new PreEpistemicAction;
		(yyval.epistemic_action)->name = *(yyvsp[(4) - (30)].str);
		(yyval.epistemic_action)->category = *(yyvsp[(8) - (30)].act_type);
		(yyval.epistemic_action)->paras = *(yyvsp[(13) - (30)].multitype_list);
		(yyval.epistemic_action)->preCondition = *(yyvsp[(18) - (30)].tree);
		(yyval.epistemic_action)->observe_pos = *(yyvsp[(23) - (30)].tree);
		(yyval.epistemic_action)->observe_neg = *(yyvsp[(28) - (30)].tree);
		// cout << "epistemicActions done" << endl;
	;}
    break;

  case 27:
#line 289 "parse.y"
    {
		(yyval.ontic_action) = new PreOnticAction;
		(yyval.ontic_action)->name = *(yyvsp[(4) - (25)].str);
		(yyval.ontic_action)->category = *(yyvsp[(8) - (25)].act_type);
		(yyval.ontic_action)->paras = *(yyvsp[(13) - (25)].multitype_list);
		(yyval.ontic_action)->preCondition = *(yyvsp[(18) - (25)].tree);
		(yyval.ontic_action)->effects = *(yyvsp[(23) - (25)].eff_set);	
		// cout << "onticAction done" << endl;
	;}
    break;

  case 28:
#line 300 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 29:
#line 305 "parse.y"
    {
		if (*(yyvsp[(1) - (1)].str) == "ontic") { *(yyval.act_type) = ONTIC; }
		else if (*(yyvsp[(1) - (1)].str) == "observation") { *(yyval.act_type) = OBSERVATION; }
		else if (*(yyvsp[(1) - (1)].str) == "communication") { *(yyval.act_type) = COMMUNICATION; }
		else if (*(yyvsp[(1) - (1)].str) == "sensing") { *(yyval.act_type) = SENSING; }
		else { cout << "something wrong in category in parse.y" << endl; }
	;}
    break;

  case 30:
#line 315 "parse.y"
    { (yyval.multitype_list) = (yyvsp[(1) - (1)].multitype_list); ;}
    break;

  case 31:
#line 316 "parse.y"
    { (yyval.multitype_list) = new MultiTypeList; ;}
    break;

  case 32:
#line 320 "parse.y"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); ;}
    break;

  case 33:
#line 324 "parse.y"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); ;}
    break;

  case 34:
#line 325 "parse.y"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); ;}
    break;

  case 35:
#line 329 "parse.y"
    {
		if ((yyvsp[(1) - (4)].tree)->right == NULL) {
			(yyval.tree) = (yyvsp[(1) - (4)].tree);
		} else {
			(yyval.tree) = new Formula("same", (yyvsp[(1) - (4)].tree), NULL);
		}
		(yyval.tree)->right = (yyvsp[(3) - (4)].tree);
	;}
    break;

  case 36:
#line 338 "parse.y"
    {
		(yyval.tree) = new Formula("same", (yyvsp[(2) - (3)].tree), NULL);
	;}
    break;

  case 37:
#line 344 "parse.y"
    {
		(yyval.tree) = new Formula(*(yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].tree), NULL);
	;}
    break;

  case 38:
#line 348 "parse.y"
    {
		(yyval.tree) = new Formula(*(yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].tree), NULL);
	;}
    break;

  case 39:
#line 353 "parse.y"
    { (yyval.tree) = new Formula("&", (yyvsp[(2) - (2)].tree)->left, (yyvsp[(2) - (2)].tree)->right); ;}
    break;

  case 40:
#line 354 "parse.y"
    { (yyval.tree) = new Formula("|", (yyvsp[(2) - (2)].tree)->left, (yyvsp[(2) - (2)].tree)->right); ;}
    break;

  case 41:
#line 355 "parse.y"
    { (yyval.tree) = new Formula("!", (yyvsp[(2) - (2)].tree)->left, (yyvsp[(2) - (2)].tree)->right); ;}
    break;

  case 42:
#line 356 "parse.y"
    { (yyval.tree) = new Formula("->", (yyvsp[(2) - (2)].tree)->left, (yyvsp[(2) - (2)].tree)->right); ;}
    break;

  case 43:
#line 357 "parse.y"
    { (yyval.tree) = new Formula("oneof", (yyvsp[(2) - (2)].tree)->left, (yyvsp[(2) - (2)].tree)->right); ;}
    break;

  case 44:
#line 358 "parse.y"
    { (yyval.tree) = new Formula(*(yyvsp[(1) - (1)].str)); ;}
    break;

  case 45:
#line 361 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 46:
#line 362 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 47:
#line 364 "parse.y"
    {
		(yyval.str) = new string(*(yyvsp[(1) - (2)].str));
		bool variable_exist = false;
		for (StringList::iterator ssi = (*(yyvsp[(2) - (2)].str_list)).begin(); ssi != (*(yyvsp[(2) - (2)].str_list)).end(); ssi++)
		{
			if ((*ssi)[0] == '?') variable_exist = true;
			*(yyval.str) += " " + *ssi;
		}
		if (!variable_exist) reader.atomicPropSet.insert(*(yyval.str));
	;}
    break;

  case 48:
#line 374 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); reader.atomicPropSet.insert(*(yyvsp[(1) - (1)].str)); ;}
    break;

  case 49:
#line 378 "parse.y"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); ;}
    break;

  case 50:
#line 382 "parse.y"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); ;}
    break;

  case 51:
#line 387 "parse.y"
    {
		(yyval.eff_set) = (yyvsp[(1) - (4)].eff_set);
		(yyval.eff_set)->insert((yyval.eff_set)->begin(), *(yyvsp[(3) - (4)].eff));
	;}
    break;

  case 52:
#line 392 "parse.y"
    {
		(yyval.eff_set) = new EffectList;
		(yyval.eff_set)->insert((yyval.eff_set)->begin(), *(yyvsp[(2) - (3)].eff));
	;}
    break;

  case 53:
#line 399 "parse.y"
    {
		(yyval.eff) = new Effect;
		(yyval.eff)->aft_condition = *(yyvsp[(2) - (6)].tree);
		(yyval.eff)->con_effect = *(yyvsp[(5) - (6)].tree);
	;}
    break;

  case 54:
#line 406 "parse.y"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); ;}
    break;

  case 55:
#line 409 "parse.y"
    { (yyval.tree) = (yyvsp[(1) - (1)].tree); ;}
    break;

  case 56:
#line 423 "parse.y"
    {
		reader.problemName = *(yyvsp[(3) - (10)].str);
		reader.objects = *(yyvsp[(5) - (10)].multitype_list);
		reader.agents = *(yyvsp[(6) - (10)].str_list);
		reader.init = *(yyvsp[(7) - (10)].tree);
		reader.constraint = *(yyvsp[(8) - (10)].tree);
		reader.goal = *(yyvsp[(9) - (10)].tree);
		// cout << "problem done" << endl;
	;}
    break;

  case 57:
#line 435 "parse.y"
    {
		(yyval.str) = (yyvsp[(3) - (4)].str);
	;}
    break;

  case 59:
#line 445 "parse.y"
    {
		(yyval.multitype_list) = (yyvsp[(4) - (5)].multitype_list);
	;}
    break;

  case 60:
#line 449 "parse.y"
    {
		(yyval.multitype_list) = new MultiTypeList;
	;}
    break;

  case 61:
#line 455 "parse.y"
    {
 		(yyval.str_list) = (yyvsp[(4) - (5)].str_list);
 	;}
    break;

  case 62:
#line 461 "parse.y"
    {
		(yyval.multitype_list) = (yyvsp[(1) - (2)].multitype_list);
		(yyval.multitype_list)->push_back(*(yyvsp[(2) - (2)].singletype_pair));
	;}
    break;

  case 63:
#line 466 "parse.y"
    {
		(yyval.multitype_list) = new MultiTypeList;
		(yyval.multitype_list)->push_back(*(yyvsp[(1) - (1)].singletype_pair));
	;}
    break;

  case 64:
#line 473 "parse.y"
    {
		(yyval.singletype_pair) = new SingleTypePair;
		(yyval.singletype_pair)->first = *(yyvsp[(3) - (3)].str);
		(yyval.singletype_pair)->second = *(yyvsp[(1) - (3)].str_list);
	;}
    break;

  case 65:
#line 481 "parse.y"
    {
		(yyval.str_list) = (yyvsp[(1) - (2)].str_list);
		(yyval.str_list)->push_back(*(yyvsp[(2) - (2)].str));
	;}
    break;

  case 66:
#line 486 "parse.y"
    {
		(yyval.str_list) = new StringList;
		(yyval.str_list)->push_back(*(yyvsp[(1) - (1)].str));
	;}
    break;

  case 67:
#line 492 "parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 68:
#line 497 "parse.y"
    {
		(yyval.tree) = (yyvsp[(5) - (7)].tree);
		// cout << "init done" << endl;
	;}
    break;

  case 69:
#line 505 "parse.y"
    {
		(yyval.tree) = (yyvsp[(5) - (7)].tree);
		// cout << "constraint done" << endl;
	;}
    break;

  case 70:
#line 513 "parse.y"
    {
		(yyval.tree) = (yyvsp[(5) - (7)].tree);
		// cout << "goal done" << endl;
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 2043 "parse.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 519 "parse.y"


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

