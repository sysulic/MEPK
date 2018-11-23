/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "epddlParser.y" /* yacc.c:339  */

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

#line 146 "epddlParser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "epddlParser.h".  */
#ifndef YY_YY_EPDDLPARSER_H_INCLUDED
# define YY_YY_EPDDLPARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NAME = 258,
    K = 259,
    DK = 260,
    AND = 261,
    OR = 262,
    NOT = 263,
    IMPLY = 264,
    ONEOF = 265,
    TRUETERM = 266,
    FALSETERM = 267,
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
    LDOMAIN = 278,
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 81 "epddlParser.y" /* yacc.c:355  */

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

#line 242 "epddlParser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_EPDDLPARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 259 "epddlParser.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   244

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  255

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   184,   184,   198,   203,   207,   212,   216,   222,   227,
     233,   238,   243,   248,   254,   268,   273,   279,   284,   290,
     295,   301,   306,   311,   319,   327,   334,   341,   349,   355,
     361,   374,   379,   384,   389,   394,   399,   406,   414,   420,
     426,   437,   443,   448,   458,   468,   476,   484,   493,   501,
     508,   530,   534,   538,   542,   547,   576,   599,   621,   626,
     632,   637,   651,   665,   674,   686,   699,   705,   711,   728,
     736,   745,   779,   805,   810,   816,   830,   835,   841,   851,
     856,   870,   884,   893,   905,   918,   924,   930
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME", "K", "DK", "AND", "OR", "NOT",
  "IMPLY", "ONEOF", "TRUETERM", "FALSETERM", "LEFT_PAREN", "RIGHT_PAREN",
  "LEFT_BRACE", "RIGHT_BRACE", "LEFT_BRACKET", "RIGHT_BRACKET", "COMMA",
  "COLON", "CONNECTOR", "DEFINE", "LDOMAIN", "TYPES", "PREDICATES",
  "PRECONDITION", "ACTION", "CATEGORY", "PARAMETERS", "OBSERVE_POS",
  "OBSERVE_NEG", "EFFECT", "PROBLEM", "OBJECTS", "AGENTS", "INIT",
  "CONSTRAINT", "GOAL", "$accept", "domain", "DomainName", "ObjectPart",
  "ObjectList", "DetailObjectList", "TypeName", "AgentPart", "AgentList",
  "PredicatePart", "GeneralAtomList", "GeneralAtom", "VarList", "InitPart",
  "Formula", "FormulaList", "FormulaAtom", "NameList", "ConstraintPart",
  "ConFormula", "ConFormulaList", "ConFormulaAtom", "GoalPart",
  "NegFormula", "NegFormulaList", "NegFormulaAtom", "ActionPart",
  "SensingAction", "ActionVar", "ActionVarList", "GeneralFormula",
  "GeneralFormulaList", "GeneralFormulaAtom", "GeneralNameList",
  "OnticAction", "OnticResList", "OnticRes", "SingleOnticResList",
  "SingleOnticRes", "NegGeneralFormula", "NegGeneralFormulaList",
  "NegGeneralFormulaAtom", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
# endif

#define YYPACT_NINF -154

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-154)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -1,    18,    24,    34,  -154,    33,    39,    75,    99,    74,
     122,   104,   120,   124,  -154,     2,   108,   125,   126,     0,
    -154,     4,  -154,   138,   123,   127,   129,  -154,  -154,   141,
    -154,  -154,  -154,  -154,  -154,     8,   133,   128,   130,   136,
    -154,  -154,  -154,  -154,  -154,   149,    56,  -154,   150,   -21,
     134,   143,    27,  -154,  -154,   137,   146,   131,   140,   147,
     142,  -154,    29,   139,    77,   148,  -154,   151,   132,  -154,
     162,   145,  -154,   156,  -154,   146,   146,   146,   146,   146,
      43,  -154,   106,   157,  -154,   159,  -154,   170,   171,   161,
     163,   146,    97,   103,   164,  -154,  -154,   151,   151,   151,
      58,  -154,    88,   165,  -154,  -154,   166,  -154,  -154,  -154,
    -154,  -154,  -154,  -154,   151,   107,   109,   167,  -154,   159,
     159,   159,   159,   159,    59,  -154,   168,  -154,  -154,  -154,
    -154,  -154,   169,   172,   159,   111,   113,   173,  -154,   155,
     175,  -154,  -154,  -154,  -154,  -154,  -154,  -154,   176,   174,
      61,   177,   178,   181,    62,    94,   182,  -154,   188,   179,
     183,  -154,  -154,   177,   177,   177,   177,   177,    63,   -22,
    -154,   159,   189,   184,   192,   177,   115,   117,   193,  -154,
    -154,   180,   190,   191,  -154,  -154,  -154,  -154,  -154,  -154,
    -154,  -154,   100,   194,  -154,   195,     1,   180,   180,   180,
     180,   180,    65,   154,   198,    57,  -154,   146,   196,   201,
     202,   180,   119,   121,   203,  -154,   180,   177,   204,  -154,
     199,   205,  -154,  -154,  -154,  -154,  -154,  -154,  -154,   206,
     160,  -154,   197,   208,   101,  -154,  -154,   209,   146,   159,
     207,  -154,   180,   211,   210,  -154,   213,  -154,   212,   214,
     146,  -154,   215,   216,  -154
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,     0,     0,     0,     0,     0,
       5,     0,     6,     0,     0,     0,     0,    51,    52,     0,
       9,     8,     4,     7,    12,     0,     0,     0,     0,     0,
      54,    53,    10,    13,    11,     0,     0,    15,     0,     0,
       0,     0,     0,    14,    16,     0,     0,     0,     0,     0,
       0,    17,     0,     0,     0,     0,    22,     0,     0,     2,
       0,     0,    18,     0,    31,     0,     0,     0,     0,     0,
       0,    21,     0,     0,    34,     0,    19,     0,     0,     0,
       0,     0,     0,     0,     0,    32,    30,     0,     0,     0,
       0,    33,     0,     0,    42,    20,     0,    23,    24,    28,
      26,    29,    27,    25,     0,     0,     0,     0,    40,     0,
       0,     0,     0,     0,     0,    41,     0,    38,    36,    39,
      37,    35,     0,     0,     0,     0,     0,     0,    50,     0,
       0,    43,    44,    48,    46,    49,    47,    45,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    79,     0,     0,
       0,    57,    69,     0,     0,     0,     0,     0,     0,     0,
      58,     0,     0,     0,     0,     0,     0,     0,     0,    70,
      87,     0,     0,     0,    59,    80,    81,    85,    83,    86,
      84,    82,     0,     0,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    73,     0,     0,     0,
       0,     0,     0,     0,     0,    68,     0,     0,     0,    74,
       0,     0,    61,    62,    66,    64,    67,    65,    63,     0,
       0,    71,     0,     0,     0,    76,    55,     0,     0,     0,
       0,    77,     0,     0,     0,    72,     0,    56,     0,     0,
       0,    75,     0,     0,    78
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -154,  -154,  -154,  -154,  -154,    67,  -154,  -154,  -154,  -154,
    -154,   187,  -154,  -154,   -56,   118,  -154,   -73,  -154,   -65,
     110,  -154,  -154,   -81,   114,  -154,  -154,   217,  -154,  -154,
    -153,    -3,  -154,    38,   218,  -154,     5,  -154,     3,  -150,
      69,  -154
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,     9,    21,    22,    31,    13,    35,    18,
      46,    47,    62,    39,    91,    92,    66,    80,    51,   114,
     115,    84,    59,   134,   135,   104,    26,    27,   140,   154,
     211,   212,   194,   168,    28,   205,   206,   234,   235,   175,
     176,   157
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      65,   156,    83,    19,   103,    19,    48,    19,   181,   100,
     182,    43,     1,   173,   174,    56,    20,   178,    32,    89,
      90,    29,    44,    94,     4,   187,   189,   189,   193,   124,
      60,   207,    71,   208,   117,   109,   111,   111,   132,   133,
       3,    61,   137,    72,   209,   210,    95,     5,   214,   127,
     129,   129,     8,   143,   145,   145,     7,    96,   224,   226,
     226,    95,    95,   229,   152,   160,   179,   230,   179,    45,
      53,   218,   118,   138,   204,   153,   161,   180,    10,   215,
      74,    75,    76,    77,    78,    79,    30,    12,    33,   246,
     183,    74,   119,   120,   121,   122,   123,   162,   163,   164,
     165,   166,   167,   162,   197,   198,   199,   200,   201,    74,
      64,   110,    97,    98,    99,   240,    64,   112,   233,    11,
      82,   128,    82,   130,   102,   144,   102,   146,   155,   188,
     155,   190,   192,   225,   192,   227,    14,    17,    15,    25,
      16,    34,    38,    23,    42,    24,    45,    37,    36,    50,
      49,   220,    52,    55,    57,    48,    58,    63,   244,    64,
      68,    69,    81,    70,    82,    86,    87,    73,    67,    88,
      85,   101,   102,   105,   106,   107,   237,   108,   113,   125,
     126,   131,   243,   141,   148,   216,   142,   147,   139,   150,
     155,   170,   184,   192,   252,   149,    93,   213,   185,   158,
     151,   159,   169,   195,   172,   171,   186,   191,   116,   221,
     219,   196,   204,   217,   203,   222,   223,   228,   231,   232,
     236,   245,   233,   239,   242,   247,   248,   250,   238,   249,
     202,   253,   251,    54,   254,   177,   136,   241,     0,     0,
       0,     0,     0,    40,    41
};

static const yytype_int16 yycheck[] =
{
      56,   151,    67,     3,    85,     3,    27,     3,    30,    82,
      32,     3,    13,   163,   164,    36,    14,   167,    14,    75,
      76,    21,    14,    79,     0,   175,   176,   177,   181,   102,
       3,    30,     3,    32,    99,    91,    92,    93,   119,   120,
      22,    14,   123,    14,   197,   198,     3,    13,   201,   114,
     115,   116,    13,   134,   135,   136,    23,    14,   211,   212,
     213,     3,     3,   216,     3,     3,     3,   217,     3,    13,
      14,    14,    14,    14,    17,    14,    14,    14,     3,    14,
       3,     4,     5,     6,     7,     8,    19,    13,    21,   242,
     171,     3,     4,     5,     6,     7,     8,     3,     4,     5,
       6,     7,     8,     3,     4,     5,     6,     7,     8,     3,
      13,    14,     6,     7,     8,    14,    13,    14,    17,    20,
      13,    14,    13,    14,    13,    14,    13,    14,    13,    14,
      13,    14,    13,    14,    13,    14,    14,    13,    34,    13,
      20,     3,    13,    35,     3,    20,    13,    20,    25,    13,
      20,   207,     3,     3,    20,    27,    13,    20,   239,    13,
      20,    14,    14,    21,    13,     3,    21,    28,    37,    13,
      38,    14,    13,     3,     3,    14,    16,    14,    14,    14,
      14,    14,   238,    14,    29,    31,    14,    14,    20,    13,
      13,     3,     3,    13,   250,    20,    78,   200,    14,    21,
      26,    20,    20,    13,    21,    26,    14,    14,    98,    13,
     205,    20,    17,    15,    20,    14,    14,    14,    14,    20,
      14,    14,    17,    15,    15,    14,    16,    15,    31,    16,
     192,    16,    18,    46,    18,   166,   122,   234,    -1,    -1,
      -1,    -1,    -1,    26,    26
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    40,    22,     0,    13,    41,    23,    13,    42,
       3,    20,    13,    46,    14,    34,    20,    13,    48,     3,
      14,    43,    44,    35,    20,    13,    65,    66,    73,    21,
      44,    45,    14,    44,     3,    47,    25,    20,    13,    52,
      66,    73,     3,     3,    14,    13,    49,    50,    27,    20,
      13,    57,     3,    14,    50,     3,    36,    20,    13,    61,
       3,    14,    51,    20,    13,    53,    55,    37,    20,    14,
      21,     3,    14,    28,     3,     4,     5,     6,     7,     8,
      56,    14,    13,    58,    60,    38,     3,    21,    13,    53,
      53,    53,    54,    54,    53,     3,    14,     6,     7,     8,
      56,    14,    13,    62,    64,     3,     3,    14,    14,    53,
      14,    53,    14,    14,    58,    59,    59,    58,    14,     4,
       5,     6,     7,     8,    56,    14,    14,    58,    14,    58,
      14,    14,    62,    62,    62,    63,    63,    62,    14,    20,
      67,    14,    14,    62,    14,    62,    14,    14,    29,    20,
      13,    26,     3,    14,    68,    13,    78,    80,    21,    20,
       3,    14,     3,     4,     5,     6,     7,     8,    72,    20,
       3,    26,    21,    78,    78,    78,    79,    79,    78,     3,
      14,    30,    32,    62,     3,    14,    14,    78,    14,    78,
      14,    14,    13,    69,    71,    13,    20,     4,     5,     6,
       7,     8,    72,    20,    17,    74,    75,    30,    32,    69,
      69,    69,    70,    70,    69,    14,    31,    15,    14,    75,
      53,    13,    14,    14,    69,    14,    69,    14,    14,    69,
      78,    14,    20,    17,    76,    77,    14,    16,    31,    15,
      14,    77,    15,    53,    62,    14,    69,    14,    16,    16,
      15,    18,    53,    16,    18
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    41,    42,    42,    43,    43,    44,    44,
      45,    46,    47,    47,    48,    49,    49,    50,    50,    51,
      51,    52,    53,    53,    53,    53,    53,    53,    54,    54,
      55,    56,    56,    57,    58,    58,    58,    58,    59,    59,
      60,    61,    62,    62,    62,    62,    62,    62,    63,    63,
      64,    65,    65,    65,    65,    66,    66,    67,    68,    68,
      69,    69,    69,    69,    69,    69,    70,    70,    71,    72,
      72,    73,    73,    74,    74,    75,    76,    76,    77,    78,
      78,    78,    78,    78,    78,    79,    79,    80
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,    11,     4,     5,     4,     1,     2,     2,     2,
       2,     5,     1,     2,     5,     1,     2,     3,     4,     3,
       4,     5,     1,     4,     4,     4,     4,     4,     2,     2,
       3,     1,     2,     5,     1,     4,     4,     4,     2,     2,
       3,     5,     1,     4,     4,     4,     4,     4,     2,     2,
       3,     1,     1,     2,     2,    20,    23,     5,     3,     4,
       1,     4,     4,     4,     4,     4,     2,     2,     3,     1,
       2,    19,    22,     1,     2,     8,     1,     2,     8,     1,
       4,     4,     4,     4,     4,     2,     2,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 194 "epddlParser.y" /* yacc.c:1646  */
    {
		domainName = *(yyvsp[-8].str);
	}
#line 1503 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 199 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.str) = (yyvsp[-1].str);
	}
#line 1511 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 204 "epddlParser.y" /* yacc.c:1646  */
    {
		objects = *(yyvsp[-1].stringToStringVector);
	}
#line 1519 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 208 "epddlParser.y" /* yacc.c:1646  */
    {

	}
#line 1527 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 213 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.stringToStringVector) = (yyvsp[0].stringToStringVector);
	}
#line 1535 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 217 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.stringToStringVector) = (yyvsp[-1].stringToStringVector);
		(*(yyval.stringToStringVector))[(*(yyvsp[0].stringToStringVector)).begin()->first] = (*(yyvsp[0].stringToStringVector)).begin()->second;
	}
#line 1544 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 223 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.stringToStringVector) = new (map<string, vector<string> >);
		(yyval.stringToStringVector)->insert(make_pair(*(yyvsp[0].str), vector<string>(1, *(yyvsp[-1].str))));
	}
#line 1553 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 228 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.stringToStringVector) = (yyvsp[0].stringToStringVector);
		(*(yyval.stringToStringVector))[(*(yyval.stringToStringVector)).begin()->first].push_back(*(yyvsp[-1].str));
	}
#line 1562 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 234 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.str) = (yyvsp[0].str);
	}
#line 1570 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 239 "epddlParser.y" /* yacc.c:1646  */
    {
		agents = *(yyvsp[-1].stringVector);
	}
#line 1578 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 244 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.stringVector) = new vector<string>;
		(*(yyval.stringVector)).push_back(*(yyvsp[0].str));
	}
#line 1587 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 249 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.stringVector) = (yyvsp[-1].stringVector);
		(*(yyval.stringVector)).push_back(*(yyvsp[0].str));
	}
#line 1596 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 255 "epddlParser.y" /* yacc.c:1646  */
    {
		atomNum = 0;
		map<string, vector<char> > visited;
		for(map<string, vector<string> >::iterator ite = objects.begin(); ite != objects.end();ite++) {
			visited.insert(make_pair(ite->first, vector<char>(ite->second.size(), '0')));
		}
		visited.insert(make_pair("agent", vector<char>(agents.size(), '0')));
		vector<vector<string> > tgal(*(yyvsp[-1].stringVectorVector));
		for(size_t i = 0;i < tgal.size();i++) {
			atomGround(tgal[i], 1, "", visited);
		}
	}
#line 1613 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 269 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.stringVectorVector) = new vector<vector<string> >;
		(*(yyval.stringVectorVector)).push_back(*(yyvsp[0].stringVector));
	}
#line 1622 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 274 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.stringVectorVector) = (yyvsp[-1].stringVectorVector);
		(*(yyval.stringVectorVector)).push_back(*(yyvsp[0].stringVector));
	}
#line 1631 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 280 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.stringVector) = new vector<string>;
		(*(yyval.stringVector)).push_back(*(yyvsp[-1].str));
	}
#line 1640 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 285 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.stringVector) = (yyvsp[-1].stringVector);
		(*(yyval.stringVector)).insert((*(yyval.stringVector)).begin(), *(yyvsp[-2].str));
	}
#line 1649 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 291 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.stringVector) = new vector<string>;
		(*(yyval.stringVector)).push_back(*(yyvsp[0].str));
	}
#line 1658 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 296 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.stringVector) = (yyvsp[-3].stringVector);
		(*(yyval.stringVector)).push_back(*(yyvsp[0].str));
	}
#line 1667 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 302 "epddlParser.y" /* yacc.c:1646  */
    {
		init = *(yyvsp[-1].kldnf);
	}
#line 1675 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 307 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnf) = new KLDNF;
		*(yyval.kldnf) = *(yyvsp[0].kldnf);
	}
#line 1684 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 312 "epddlParser.y" /* yacc.c:1646  */
    {
		string agentName = (yyvsp[-2].str)->substr(2, (yyvsp[-2].str)->length()-2);
		(yyval.kldnf) = new KLDNF;
		KLTerm klt;
		klt.KPart[agentName] = *(yyvsp[-1].kldnf);
		(yyval.kldnf)->dnf.push_back(klt);
	}
#line 1696 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 320 "epddlParser.y" /* yacc.c:1646  */
    {
		string agentName = (yyvsp[-2].str)->substr(3, (yyvsp[-2].str)->length()-3);
		(yyval.kldnf) = new KLDNF;
		KLTerm klt;
		klt.LPart[agentName].push_back(*(yyvsp[-1].kldnf));
		(yyval.kldnf)->dnf.push_back(klt);
	}
#line 1708 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 328 "epddlParser.y" /* yacc.c:1646  */
    {
		PropDNF preConstraint;
		preConstraint.dnf.push_back(PropTerm(atomNum));
		(yyval.kldnf) = new KLDNF;
		*(yyval.kldnf) = (yyvsp[-1].kldnf)->negation(preConstraint);
	}
#line 1719 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 335 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnf) = new KLDNF;
		for(size_t i = 0;i < (yyvsp[-1].kldnfVector)->size();i++) {
			*(yyval.kldnf) = (yyval.kldnf)->conjunction((*(yyvsp[-1].kldnfVector))[i]);
		}
	}
#line 1730 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 342 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnf) = new KLDNF;
		for(size_t i = 0;i < (yyvsp[-1].kldnfVector)->size();i++) {
			*(yyval.kldnf) = (yyval.kldnf)->disjunction((*(yyvsp[-1].kldnfVector))[i]);
		}
	}
#line 1741 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 350 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		(yyval.kldnfVector)->push_back(*(yyvsp[-1].kldnf));
		(yyval.kldnfVector)->push_back(*(yyvsp[0].kldnf));
	}
#line 1751 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 356 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = (yyvsp[-1].kldnfVector);
		(yyval.kldnfVector)->push_back(*(yyvsp[0].kldnf));
	}
#line 1760 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 362 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnf) = new KLDNF;
		PropTerm pt(atomNum);
		KLTerm klt;
		string atomName = "(" + *(yyvsp[-1].str) + ")";
		if(atomName != "(True)") {
			pt.literal[findAtomsByName[atomName]] = TRUE;
		}
		klt.PPart.dnf.push_back(pt);
		(yyval.kldnf)->dnf.push_back(klt);
	}
#line 1776 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 375 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.str) = new std::string;
		(yyval.str) = (yyvsp[0].str);
	}
#line 1785 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 380 "epddlParser.y" /* yacc.c:1646  */
    {
		*(yyval.str) = *(yyval.str) + " " + *(yyvsp[0].str);
	}
#line 1793 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 385 "epddlParser.y" /* yacc.c:1646  */
    {
		constraint = *(yyvsp[-1].pdnf);
	}
#line 1801 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 390 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.pdnf) = new PropDNF;
		(yyval.pdnf) = (yyvsp[0].pdnf);
	}
#line 1810 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 395 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.pdnf) = new PropDNF;
		*(yyval.pdnf) = (yyvsp[-1].pdnf)->negation();
	}
#line 1819 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 400 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.pdnf) = new PropDNF;
		for(size_t i = 0; i < (yyvsp[-1].pdnfVector)->size();i++) {
			*(yyval.pdnf) = (yyval.pdnf)->conjunction((*(yyvsp[-1].pdnfVector))[i]);
		}
	}
#line 1830 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 407 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.pdnf) = new PropDNF;
		for(size_t i = 0; i < (yyvsp[-1].pdnfVector)->size();i++) {
			*(yyval.pdnf) = (yyval.pdnf)->disjunction((*(yyvsp[-1].pdnfVector))[i]);
		}
	}
#line 1841 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 415 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.pdnfVector) = new vector<PropDNF>;
		(yyval.pdnfVector)->push_back(*(yyvsp[-1].pdnf));
		(yyval.pdnfVector)->push_back(*(yyvsp[0].pdnf));
	}
#line 1851 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 421 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.pdnfVector) = (yyvsp[-1].pdnfVector);
		(yyval.pdnfVector)->push_back(*(yyvsp[0].pdnf));
	}
#line 1860 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 427 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.pdnf) = new PropDNF;
		PropTerm pt(atomNum);
		string atomName = "(" + *(yyvsp[-1].str) + ")";
		if(atomName != "(True)") {
			pt.literal[findAtomsByName[atomName]] = TRUE;
		}
		(yyval.pdnf)->dnf.push_back(pt);
	}
#line 1874 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 438 "epddlParser.y" /* yacc.c:1646  */
    {
		goal = (*(yyvsp[-1].kldnfVector))[0];
		posGoal = (*(yyvsp[-1].kldnfVector))[1];
	}
#line 1883 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 444 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		*(yyval.kldnfVector) = *(yyvsp[0].kldnfVector);
	}
#line 1892 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 449 "epddlParser.y" /* yacc.c:1646  */
    {
		string agentName = (yyvsp[-2].str)->substr(2, (yyvsp[-2].str)->length()-2);
		(yyval.kldnfVector) = new vector<KLDNF>(2);
		KLTerm klt1, klt2;
		klt1.LPart[agentName].push_back((*(yyvsp[-1].kldnfVector))[0]);
		klt2.KPart[agentName] = (*(yyvsp[-1].kldnfVector))[1];
		(*(yyval.kldnfVector))[0].dnf.push_back(klt1);
		(*(yyval.kldnfVector))[1].dnf.push_back(klt2);
	}
#line 1906 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 459 "epddlParser.y" /* yacc.c:1646  */
    {
		string agentName = (yyvsp[-2].str)->substr(3, (yyvsp[-2].str)->length()-3);
		(yyval.kldnfVector) = new vector<KLDNF>(2);
		KLTerm klt1, klt2;
		klt2.LPart[agentName].push_back((*(yyvsp[-1].kldnfVector))[1]);
		klt1.KPart[agentName] = (*(yyvsp[-1].kldnfVector))[0];
		(*(yyval.kldnfVector))[0].dnf.push_back(klt1);
		(*(yyval.kldnfVector))[1].dnf.push_back(klt2);
	}
#line 1920 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 469 "epddlParser.y" /* yacc.c:1646  */
    {
		PropDNF preConstraint;
		preConstraint.dnf.push_back(PropTerm(atomNum));
		(yyval.kldnfVector) = new vector<KLDNF>(2);
		(*(yyval.kldnfVector))[0] = (*(yyvsp[-1].kldnfVector))[1];
		(*(yyval.kldnfVector))[1] = (*(yyvsp[-1].kldnfVector))[0];
	}
#line 1932 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 477 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>(2);
		for(size_t i = 0;i < (*(yyvsp[-1].kldnfVectorVector))[0].size();i++) {
			(*(yyval.kldnfVector))[0] = (*(yyval.kldnfVector))[0].disjunction((*(yyvsp[-1].kldnfVectorVector))[0][i]);
			(*(yyval.kldnfVector))[1] = (*(yyval.kldnfVector))[1].conjunction((*(yyvsp[-1].kldnfVectorVector))[1][i]);
		}
	}
#line 1944 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 485 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>(2);
		for(size_t i = 0;i < (*(yyvsp[-1].kldnfVectorVector))[0].size();i++) {
			(*(yyval.kldnfVector))[0] = (*(yyval.kldnfVector))[0].conjunction((*(yyvsp[-1].kldnfVectorVector))[0][i]);
			(*(yyval.kldnfVector))[1] = (*(yyval.kldnfVector))[1].disjunction((*(yyvsp[-1].kldnfVectorVector))[1][i]);
		}
	}
#line 1956 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 494 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVectorVector) = new vector<vector<KLDNF>>(2);
		(*(yyval.kldnfVectorVector))[0].push_back((*(yyvsp[-1].kldnfVector))[0]);
		(*(yyval.kldnfVectorVector))[0].push_back((*(yyvsp[0].kldnfVector))[0]);
		(*(yyval.kldnfVectorVector))[1].push_back((*(yyvsp[-1].kldnfVector))[1]);
		(*(yyval.kldnfVectorVector))[1].push_back((*(yyvsp[0].kldnfVector))[1]);
	}
#line 1968 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 502 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVectorVector) = (yyvsp[-1].kldnfVectorVector);
		(*(yyval.kldnfVectorVector))[0].push_back((*(yyvsp[0].kldnfVector))[0]);
		(*(yyval.kldnfVectorVector))[1].push_back((*(yyvsp[0].kldnfVector))[1]);
	}
#line 1978 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 509 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		KLDNF kld1, kld2;
		PropTerm pt1(atomNum), pt2(atomNum);
		KLTerm klt1, klt2;
		string atomName = "(" + *(yyvsp[-1].str) + ")";
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
		(yyval.kldnfVector)->push_back(kld1);
		(yyval.kldnfVector)->push_back(kld2);
	}
#line 2003 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 531 "epddlParser.y" /* yacc.c:1646  */
    {

	}
#line 2011 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 535 "epddlParser.y" /* yacc.c:1646  */
    {

	}
#line 2019 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 539 "epddlParser.y" /* yacc.c:1646  */
    {

	}
#line 2027 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 543 "epddlParser.y" /* yacc.c:1646  */
    {

	}
#line 2035 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 554 "epddlParser.y" /* yacc.c:1646  */
    {
		string actionNamePre = *(yyvsp[-16].str);
		string actionType = *(yyvsp[-12].str);
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
			sa.preCon = (*(yyvsp[-7].kldnfVector))[i];
			sa.posRes = (*(yyvsp[-4].kldnfVector))[i];
			sa.negRes = (*(yyvsp[-1].kldnfVector))[i];
			sActions.push_back(sa);
		}
	}
#line 2062 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 583 "epddlParser.y" /* yacc.c:1646  */
    {
		string actionName = *(yyvsp[-19].str);
		string actionType = *(yyvsp[-15].str);
		SensingAction sa;
		sa.name = actionName;
		if (actionType == "ontic") { sa.category = ONTIC; }
		else if (actionType == "observation") { sa.category = OBSERVATION; }
		else if (actionType == "communication") { sa.category = COMMUNICATION; }
		else if (actionType == "sensing") { sa.category = SENSING; }
		else { cout << "something wrong in category in parse.y" << endl; }
		sa.preCon = (*(yyvsp[-7].kldnfVector))[0];
		sa.posRes = (*(yyvsp[-4].kldnf));
		sa.negRes = (*(yyvsp[-1].kldnf));
		sActions.push_back(sa);
	}
#line 2082 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 600 "epddlParser.y" /* yacc.c:1646  */
    {	
		actionVar.clear();
		actionVarSeq.clear();
		if((yyvsp[-1].stringToString)->empty()) {
			actionVar.push_back(map<string, string>());
		}
		else {
			for(map<string, string>::iterator ite = (yyvsp[-1].stringToString)->begin();
				ite != (yyvsp[-1].stringToString)->end();ite++) {
				actionVarSeq.push_back(ite->first);
			}
			map<string, vector<char> > visited;
			for(map<string, vector<string> >::iterator ite = objects.begin();
				ite != objects.end();ite++) {
				visited.insert(make_pair(ite->first, vector<char>(ite->second.size(), '0')));
			}
			visited.insert(make_pair("agent", vector<char>(agents.size(), '0')));
			actionVarGround(*(yyvsp[-1].stringToString), map<string, string>(), (yyvsp[-1].stringToString)->begin(), visited);
		}
	}
#line 2107 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 622 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.stringToString) = new map<string, string>;
		(*(yyval.stringToString))[*(yyvsp[-2].str)] = *(yyvsp[0].str);
	}
#line 2116 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 627 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.stringToString) = (yyvsp[-3].stringToString);
		(*(yyval.stringToString))[*(yyvsp[-2].str)] = *(yyvsp[0].str);
	}
#line 2125 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 633 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		*(yyval.kldnfVector) = *(yyvsp[0].kldnfVector);
	}
#line 2134 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 638 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		string generalAgentName = (yyvsp[-2].str)->substr(2, (yyvsp[-2].str)->length()-2);
		for(size_t i = 0;i < (yyvsp[-1].kldnfVector)->size();i++) {
			string agentName = ((actionVar.empty() || actionVar[i].find(generalAgentName)
				== actionVar[i].end()) ? generalAgentName : actionVar[i][generalAgentName]);
			KLDNF kld;
			KLTerm klt;
			klt.KPart[agentName] = (*(yyvsp[-1].kldnfVector))[i];
			kld.dnf.push_back(klt);
			(yyval.kldnfVector)->push_back(kld);
		}
	}
#line 2152 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 652 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		string generalAgentName = (yyvsp[-2].str)->substr(3, (yyvsp[-2].str)->length()-3);
		for(size_t i = 0;i < (yyvsp[-1].kldnfVector)->size();i++) {
			string agentName = ((actionVar.empty() || actionVar[i].find(generalAgentName)
				== actionVar[i].end()) ? generalAgentName : actionVar[i][generalAgentName]);
			KLDNF kld;
			KLTerm klt;
			klt.LPart[agentName].push_back((*(yyvsp[-1].kldnfVector))[i]);
			kld.dnf.push_back(klt);
			(yyval.kldnfVector)->push_back(kld);
		}
	}
#line 2170 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 666 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		PropDNF preConstraint;
		preConstraint.dnf.push_back(PropTerm(atomNum));
		for(size_t i = 0;i < (yyvsp[-1].kldnfVector)->size();i++) {
			(yyval.kldnfVector)->push_back((*(yyvsp[-1].kldnfVector))[i].negation(preConstraint));
		}
	}
#line 2183 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 675 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		size_t row = (yyvsp[-1].kldnfVectorVector)->size(), col = (*(yyvsp[-1].kldnfVectorVector))[0].size();
		for(size_t j = 0;j < col;j++) {
			KLDNF kld;
			for(size_t i = 0;i < row;i++) {
				kld = kld.conjunction((*(yyvsp[-1].kldnfVectorVector))[i][j]);
			}
			(yyval.kldnfVector)->push_back(kld);
		}
	}
#line 2199 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 687 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		size_t row = (yyvsp[-1].kldnfVectorVector)->size(), col = (*(yyvsp[-1].kldnfVectorVector))[0].size();
		for(size_t j = 0;j < col;j++) {
			KLDNF kld;
			for(size_t i = 0;i < row;i++) {
				kld = kld.disjunction((*(yyvsp[-1].kldnfVectorVector))[i][j]);
			}
			(yyval.kldnfVector)->push_back(kld);
		}
	}
#line 2215 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 700 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVectorVector) = new vector<vector<KLDNF> >;
		(yyval.kldnfVectorVector)->push_back(*(yyvsp[-1].kldnfVector));
		(yyval.kldnfVectorVector)->push_back(*(yyvsp[0].kldnfVector));
	}
#line 2225 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 706 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVectorVector) = (yyvsp[-1].kldnfVectorVector);
		(yyval.kldnfVectorVector)->push_back(*(yyvsp[0].kldnfVector));
	}
#line 2234 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 712 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		for(size_t i = 0;i < (yyvsp[-1].stringVector)->size();i++) {
			PropTerm pt(atomNum);
			KLDNF kld;
			KLTerm klt;
			string atomName = "(" + (*(yyvsp[-1].stringVector))[i] + ")";
			if(atomName != "(True)") {
				pt.literal[findAtomsByName[atomName]] = TRUE;
			}
			klt.PPart.dnf.push_back(pt);
			kld.dnf.push_back(klt);
			(yyval.kldnfVector)->push_back(kld);
		}
	}
#line 2254 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 729 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.stringVector) = new vector<string>;
		for(size_t i = 0;i < actionVar.size();i++) {
			(yyval.stringVector)->push_back((actionVar[i].find(*(yyvsp[0].str)) == actionVar[i].end()) ?
				*(yyvsp[0].str) : actionVar[i][*(yyvsp[0].str)]);
		}
	}
#line 2266 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 737 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.stringVector) = (yyvsp[-1].stringVector);
		for(size_t i = 0;i < actionVar.size();i++) {
			(*(yyval.stringVector))[i] += (" " + ((actionVar[i].find(*(yyvsp[0].str)) == actionVar[i].end()) ?
				*(yyvsp[0].str) : actionVar[i][*(yyvsp[0].str)]));
		}
	}
#line 2278 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 751 "epddlParser.y" /* yacc.c:1646  */
    {
		string actionNamePre = *(yyvsp[-15].str);
		string actionType = *(yyvsp[-11].str);
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

			oa.preCon = (*(yyvsp[-6].kldnfVector))[i];
			for(size_t j = 0;j < (yyvsp[-2].kldnfVectorVectorVector)->size();j++) {
				ConditionalEffect ce;
				ce.condition = (*(yyvsp[-2].kldnfVectorVectorVector))[j][i][0];
				ce.effect = (*(yyvsp[-2].kldnfVectorVectorVector))[j][i][1];
				oa.eff.push_back(ce);
			}
			oActions.push_back(oa);
		}
	}
#line 2311 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 785 "epddlParser.y" /* yacc.c:1646  */
    {
		string actionName = *(yyvsp[-18].str);
		string actionType = *(yyvsp[-14].str);
		OnticAction oa;
		oa.name = actionName;
		if (actionType == "ontic") { oa.category = ONTIC; }
		else if (actionType == "observation") { oa.category = OBSERVATION; }
		else if (actionType == "communication") { oa.category = COMMUNICATION; }
		else if (actionType == "sensing") { oa.category = SENSING; }
		else { cout << "something wrong in category in parse.y" << endl; }
		oa.preCon = (*(yyvsp[-6].kldnfVector))[0];
		for(size_t i = 0;i < (*(yyvsp[-2].kldnfVectorVector)).size();i++) {
			ConditionalEffect ce;
			ce.condition = (*(yyvsp[-2].kldnfVectorVector))[i][0];
			ce.effect = (*(yyvsp[-2].kldnfVectorVector))[i][1];
			oa.eff.push_back(ce);
		}
		oActions.push_back(oa);
	}
#line 2335 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 806 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVectorVectorVector) = new vector<vector<vector<KLDNF>>>;
		(yyval.kldnfVectorVectorVector)->push_back(*(yyvsp[0].kldnfVectorVector));
	}
#line 2344 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 811 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVectorVectorVector) = (yyvsp[-1].kldnfVectorVectorVector);
		(yyval.kldnfVectorVectorVector)->push_back(*(yyvsp[0].kldnfVectorVector));
	}
#line 2353 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 820 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVectorVector) = new vector<vector<KLDNF>>;
		for(size_t i = 0;i < actionVar.size();i++) {
			vector<KLDNF> temp;
			temp.push_back((*(yyvsp[-5].kldnfVector))[i]);
			temp.push_back((*(yyvsp[-2].kldnfVector))[i]);
			(yyval.kldnfVectorVector)->push_back(temp);
		}
	}
#line 2367 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 831 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVectorVector) = new vector<vector<KLDNF>>;
		(yyval.kldnfVectorVector)->push_back(*(yyvsp[0].kldnfVector));
	}
#line 2376 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 836 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVectorVector) = (yyvsp[-1].kldnfVectorVector);
		(yyval.kldnfVectorVector)->push_back(*(yyvsp[0].kldnfVector));
	}
#line 2385 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 845 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		(yyval.kldnfVector)->push_back((*(yyvsp[-5].kldnfVector))[0]);
		(yyval.kldnfVector)->push_back(*(yyvsp[-2].kldnf));
	}
#line 2395 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 852 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		*(yyval.kldnfVector) = *(yyvsp[0].kldnfVector);
	}
#line 2404 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 857 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		string generalAgentName = (yyvsp[-2].str)->substr(2, (yyvsp[-2].str)->length()-2);
		for(size_t i = 0;i < (yyvsp[-1].kldnfVector)->size();i++) {
			string agentName = ((actionVar[i].find(generalAgentName)
				== actionVar[i].end()) ? generalAgentName : actionVar[i][generalAgentName]);
			KLDNF kld;
			KLTerm klt;
			klt.LPart[agentName].push_back((*(yyvsp[-1].kldnfVector))[i]);
			kld.dnf.push_back(klt);
			(yyval.kldnfVector)->push_back(kld);
		}
	}
#line 2422 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 871 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		string generalAgentName = (yyvsp[-2].str)->substr(3, (yyvsp[-2].str)->length()-3);
		for(size_t i = 0;i < (yyvsp[-1].kldnfVector)->size();i++) {
			string agentName = ((actionVar[i].find(generalAgentName)
				== actionVar[i].end()) ? generalAgentName : actionVar[i][generalAgentName]);
			KLDNF kld;
			KLTerm klt;
			klt.KPart[agentName] = (*(yyvsp[-1].kldnfVector))[i];
			kld.dnf.push_back(klt);
			(yyval.kldnfVector)->push_back(kld);
		}
	}
#line 2440 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 885 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		PropDNF preConstraint;
		preConstraint.dnf.push_back(PropTerm(atomNum));
		for(size_t i = 0;i < (yyvsp[-1].kldnfVector)->size();i++) {
			(yyval.kldnfVector)->push_back((*(yyvsp[-1].kldnfVector))[i].negation(preConstraint));
		}
	}
#line 2453 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 894 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		size_t row = (yyvsp[-1].kldnfVectorVector)->size(), col = (*(yyvsp[-1].kldnfVectorVector))[0].size();
		for(size_t j = 0;j < col;j++) {
			KLDNF kld;
			for(size_t i = 0;i < row;i++) {
				kld = kld.disjunction((*(yyvsp[-1].kldnfVectorVector))[i][j]);
			}
			(yyval.kldnfVector)->push_back(kld);
		}
	}
#line 2469 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 906 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		size_t row = (yyvsp[-1].kldnfVectorVector)->size(), col = (*(yyvsp[-1].kldnfVectorVector))[0].size();
		for(size_t j = 0;j < col;j++) {
			KLDNF kld;
			for(size_t i = 0;i < row;i++) {
				kld = kld.conjunction((*(yyvsp[-1].kldnfVectorVector))[i][j]);
			}
			(yyval.kldnfVector)->push_back(kld);
		}
	}
#line 2485 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 919 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVectorVector) = new vector<vector<KLDNF> >;
		(yyval.kldnfVectorVector)->push_back(*(yyvsp[-1].kldnfVector));
		(yyval.kldnfVectorVector)->push_back(*(yyvsp[0].kldnfVector));
	}
#line 2495 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 925 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVectorVector) = (yyvsp[-1].kldnfVectorVector);
		(yyval.kldnfVectorVector)->push_back(*(yyvsp[0].kldnfVector));
	}
#line 2504 "epddlParser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 931 "epddlParser.y" /* yacc.c:1646  */
    {
		(yyval.kldnfVector) = new vector<KLDNF>;
		for(size_t i = 0;i < (yyvsp[-1].stringVector)->size();i++) {
			PropTerm pt(atomNum);
			KLDNF kld;
			KLTerm klt;
			string atomName = "(" + (*(yyvsp[-1].stringVector))[i] + ")";
			if(atomName != "(True)") {
				pt.literal[findAtomsByName[atomName]] = FALSE;
			}
			else {
				pt.literal[0] = UNSAT;
			}
			klt.PPart.dnf.push_back(pt);
			kld.dnf.push_back(klt);
			(yyval.kldnfVector)->push_back(kld);
		}
	}
#line 2527 "epddlParser.tab.c" /* yacc.c:1646  */
    break;


#line 2531 "epddlParser.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 949 "epddlParser.y" /* yacc.c:1906  */


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
