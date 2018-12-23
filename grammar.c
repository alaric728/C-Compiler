/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "grammar.y"

#include <math.h>
#include <stdlib.h>
#include <list>
#include "parser.H"
#include "ast.H"
#include <string.h>
#define YYERROR_VERBOSE

/* Line 371 of yacc.c  */
#line 78 "grammar.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
   by #include "grammar.h".  */
#ifndef YY_YY_GRAMMAR_H_INCLUDED
# define YY_YY_GRAMMAR_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     TRUE = 259,
     FALSE = 260,
     TID = 261,
     THIS = 262,
     TIF = 263,
     TELSE = 264,
     TEQ = 265,
     NEQ = 266,
     TAND = 267,
     TOR = 268,
     TNEW = 269,
     TINT = 270,
     TBOOL = 271,
     TVOID = 272,
     TDB = 273,
     TRETURN = 274,
     TWHILE = 275,
     TCLASS = 276,
     TEXTENDS = 277,
     GEQ = 278,
     LEQ = 279
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 11 "grammar.y"

   int        val;
   char*      id;
   AST::Node* node;
   AST::Class* cls;
   AST::Expr* expr;
   AST::Type* type;
   AST::Stmt* stmt;
   AST::Decl* decl;
   std::list<AST::Class*>* clist;
   std::list<AST::Decl*>*  dlist;
   std::list<AST::Expr*>*  elist;
   std::list<AST::Stmt*>*  slist;


/* Line 387 of yacc.c  */
#line 161 "grammar.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (Parser* parser);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_GRAMMAR_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 188 "grammar.c"
/* Unqualified %code blocks.  */
/* Line 391 of yacc.c  */
#line 26 "grammar.y"

   int yyerror(Parser* p,const char* s);
   int yylex(YYSTYPE*);


/* Line 391 of yacc.c  */
#line 198 "grammar.c"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   193

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNRULES -- Number of states.  */
#define YYNSTATES  138

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,     2,     2,     2,     2,     2,
      32,    38,    29,    27,    39,    28,    34,    30,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    37,
      23,    40,    24,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    33,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,    36,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    25,    26
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    16,    25,    28,    29,
      33,    42,    50,    52,    53,    55,    59,    62,    65,    66,
      69,    73,    78,    82,    88,    94,   102,   106,   108,   112,
     116,   119,   123,   127,   131,   135,   139,   143,   145,   149,
     153,   157,   161,   163,   165,   167,   170,   172,   178,   184,
     188,   190,   195,   199,   204,   206,   208,   209,   211,   215,
     217,   219,   221,   223,   225
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,    44,    -1,    45,    44,    -1,    -1,    21,
       6,    35,    46,    36,    37,    -1,    21,     6,    22,     6,
      35,    46,    36,    37,    -1,    47,    46,    -1,    -1,    59,
       6,    37,    -1,    59,     6,    32,    48,    38,    35,    51,
      36,    -1,     6,    32,    48,    38,    35,    51,    36,    -1,
      49,    -1,    -1,    50,    -1,    50,    39,    49,    -1,    59,
       6,    -1,    52,    51,    -1,    -1,    54,    37,    -1,    59,
       6,    37,    -1,    55,    40,    53,    37,    -1,    35,    51,
      36,    -1,    20,    32,    53,    38,    52,    -1,     8,    32,
      53,    38,    52,    -1,     8,    32,    53,    38,    52,     9,
      52,    -1,    19,    53,    37,    -1,    37,    -1,    53,    12,
      53,    -1,    53,    13,    53,    -1,    31,    53,    -1,    54,
      23,    54,    -1,    54,    24,    54,    -1,    54,    26,    54,
      -1,    54,    25,    54,    -1,    54,    10,    54,    -1,    54,
      11,    54,    -1,    54,    -1,    54,    27,    54,    -1,    54,
      28,    54,    -1,    54,    29,    54,    -1,    54,    30,    54,
      -1,     3,    -1,     4,    -1,     5,    -1,    28,    54,    -1,
      55,    -1,    14,     6,    32,    56,    38,    -1,    14,    59,
      33,    54,    41,    -1,    32,    53,    38,    -1,     6,    -1,
      55,    32,    56,    38,    -1,    55,    34,     6,    -1,    55,
      33,    54,    41,    -1,     7,    -1,    57,    -1,    -1,    53,
      -1,    53,    39,    57,    -1,    15,    -1,    16,    -1,    17,
      -1,     6,    -1,    58,    -1,    58,    18,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    66,    66,    69,    70,    73,    74,    77,    78,    81,
      82,    83,    86,    87,    90,    91,    94,    97,    98,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     138,   139,   140,   141,   142,   145,   146,   149,   150,   153,
     154,   155,   156,   159,   160
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "TRUE", "FALSE", "TID", "THIS",
  "TIF", "TELSE", "TEQ", "NEQ", "TAND", "TOR", "TNEW", "TINT", "TBOOL",
  "TVOID", "TDB", "TRETURN", "TWHILE", "TCLASS", "TEXTENDS", "'<'", "'>'",
  "GEQ", "LEQ", "'+'", "'-'", "'*'", "'/'", "'!'", "'('", "'['", "'.'",
  "'{'", "'}'", "';'", "')'", "','", "'='", "']'", "$accept", "Top",
  "ClassList", "ClassDecl", "DeclList", "Decl", "Formals",
  "OneOrMoreFormals", "Formal", "StatementList", "Statement", "Relation",
  "Expr", "LValue", "Actuals", "OneOrMoreActuals", "BasicType", "Type", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,    60,    62,   278,   279,    43,    45,    42,
      47,    33,    40,    91,    46,   123,   125,    59,    41,    44,
      61,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    46,    46,    47,
      47,    47,    48,    48,    49,    49,    50,    51,    51,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      55,    55,    55,    55,    55,    56,    56,    57,    57,    58,
      58,    58,    58,    59,    59
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     6,     8,     2,     0,     3,
       8,     7,     1,     0,     1,     3,     2,     2,     0,     2,
       3,     4,     3,     5,     5,     7,     3,     1,     3,     3,
       2,     3,     3,     3,     3,     3,     3,     1,     3,     3,
       3,     3,     1,     1,     1,     2,     1,     5,     5,     3,
       1,     4,     3,     4,     1,     1,     0,     1,     3,     1,
       1,     1,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     2,     4,     0,     1,     3,     0,     8,
       0,    62,    59,    60,    61,     0,     8,    63,     0,     8,
      13,     0,     7,    64,     0,     0,    62,     0,    12,    14,
       0,     5,    13,     9,     0,     0,     0,    16,     0,     6,
      18,    15,     0,    42,    43,    44,    50,    54,     0,     0,
       0,     0,     0,     0,    18,    27,     0,    18,     0,    46,
       0,    18,     0,    62,     0,    50,     0,     0,    37,    46,
       0,    45,     0,     0,    11,    17,     0,     0,     0,     0,
      19,    56,     0,     0,     0,     0,     0,     0,    56,     0,
      30,     0,     0,    26,     0,     0,     0,     0,     0,     0,
       0,    49,    22,    38,    39,    40,    41,    57,     0,    55,
       0,    52,     0,    20,    10,     0,     0,     0,    28,    29,
      35,    36,    31,    32,    34,    33,     0,     0,    51,    53,
      21,    24,    47,    48,    23,    58,     0,    25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,    15,    16,    27,    28,    29,    56,
      57,   107,    68,    69,   108,   109,    17,    60
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -111
static const yytype_int16 yypact[] =
{
     -17,    19,    27,  -111,   -17,   -11,  -111,  -111,    37,   149,
      12,    39,  -111,  -111,  -111,    38,   149,    65,    67,   149,
     152,    47,  -111,  -111,   -24,    59,  -111,    72,  -111,    64,
      99,  -111,   152,  -111,    85,    98,   152,  -111,   101,  -111,
      74,  -111,   110,  -111,  -111,  -111,    35,  -111,   104,   155,
     109,   112,   114,   109,    74,  -111,   120,    74,    71,    32,
     151,    74,   109,   127,   129,  -111,   109,    48,   124,   145,
     109,    22,    -6,   138,  -111,  -111,   114,   114,   114,   114,
    -111,   109,   114,   157,   109,   123,   139,    -3,   109,   114,
    -111,   109,   109,  -111,   114,   114,   114,   114,   114,   114,
       7,  -111,  -111,    22,    22,  -111,  -111,   -10,   147,  -111,
      97,  -111,    55,  -111,  -111,    74,   148,   102,  -111,   175,
     154,   154,   154,   154,   154,   154,    74,   109,  -111,  -111,
    -111,   179,  -111,  -111,  -111,  -111,    74,  -111
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -111,  -111,   185,  -111,    88,  -111,   158,   156,  -111,   119,
    -110,   -22,   -40,   -39,   103,    66,  -111,    14
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -63
static const yytype_int16 yytable[] =
{
      58,    59,    91,    92,     1,   131,    91,    92,    32,    91,
      92,     8,    71,    33,    58,    59,   134,    58,    59,    91,
      92,    58,    59,    18,     9,     5,   137,     6,    67,   127,
      18,    72,   101,    18,    30,   115,   103,   104,   105,   106,
      87,   -62,   110,    10,    90,   126,    30,    19,   100,   117,
      30,    78,    79,   -62,   120,   121,   122,   123,   124,   125,
      91,    92,   112,    64,    81,    82,    83,    91,    92,   118,
     119,    20,    84,    24,    21,    58,    59,    43,    44,    45,
      46,    47,    48,    23,    31,    93,    58,    59,    49,    12,
      13,    14,   130,    50,    51,    34,    58,    59,    76,    77,
      78,    79,    52,    36,    22,    37,    53,    25,    80,    54,
      35,    55,    43,    44,    45,    65,    47,    43,    44,    45,
      65,    47,    39,    49,    76,    77,    78,    79,    49,    76,
      77,    78,    79,    40,    94,    95,    62,    52,   129,    42,
      66,    53,    52,   133,    70,    61,    53,    96,    97,    98,
      99,    76,    77,    78,    79,    11,    74,    85,    26,    88,
     113,    63,    89,   111,    12,    13,    14,    12,    13,    14,
      12,    13,    14,    73,   102,   114,    75,    81,    82,    83,
      86,    76,    77,    78,    79,   128,   132,    91,   136,     7,
      38,   116,    41,   135
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-111)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_uint8 yycheck[] =
{
      40,    40,    12,    13,    21,   115,    12,    13,    32,    12,
      13,    22,    52,    37,    54,    54,   126,    57,    57,    12,
      13,    61,    61,     9,    35,     6,   136,     0,    50,    39,
      16,    53,    38,    19,    20,    38,    76,    77,    78,    79,
      62,     6,    82,     6,    66,    38,    32,    35,    70,    89,
      36,    29,    30,    18,    94,    95,    96,    97,    98,    99,
      12,    13,    84,    49,    32,    33,    34,    12,    13,    91,
      92,    32,    40,     6,    36,   115,   115,     3,     4,     5,
       6,     7,     8,    18,    37,    37,   126,   126,    14,    15,
      16,    17,    37,    19,    20,    36,   136,   136,    27,    28,
      29,    30,    28,    39,    16,     6,    32,    19,    37,    35,
      38,    37,     3,     4,     5,     6,     7,     3,     4,     5,
       6,     7,    37,    14,    27,    28,    29,    30,    14,    27,
      28,    29,    30,    35,    10,    11,    32,    28,    41,    38,
      31,    32,    28,    41,    32,    35,    32,    23,    24,    25,
      26,    27,    28,    29,    30,     6,    36,     6,     6,    32,
      37,     6,    33,     6,    15,    16,    17,    15,    16,    17,
      15,    16,    17,    54,    36,    36,    57,    32,    33,    34,
      61,    27,    28,    29,    30,    38,    38,    12,     9,     4,
      32,    88,    36,   127
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    21,    43,    44,    45,     6,     0,    44,    22,    35,
       6,     6,    15,    16,    17,    46,    47,    58,    59,    35,
      32,    36,    46,    18,     6,    46,     6,    48,    49,    50,
      59,    37,    32,    37,    36,    38,    39,     6,    48,    37,
      35,    49,    38,     3,     4,     5,     6,     7,     8,    14,
      19,    20,    28,    32,    35,    37,    51,    52,    54,    55,
      59,    35,    32,     6,    59,     6,    31,    53,    54,    55,
      32,    54,    53,    51,    36,    51,    27,    28,    29,    30,
      37,    32,    33,    34,    40,     6,    51,    53,    32,    33,
      53,    12,    13,    37,    10,    11,    23,    24,    25,    26,
      53,    38,    36,    54,    54,    54,    54,    53,    56,    57,
      54,     6,    53,    37,    36,    38,    56,    54,    53,    53,
      54,    54,    54,    54,    54,    54,    38,    39,    38,    41,
      37,    52,    38,    41,    52,    57,     9,    52
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      yyerror (parser, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
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
		  Type, Value, parser); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, Parser* parser)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    Parser* parser;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (parser);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, Parser* parser)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    Parser* parser;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, Parser* parser)
#else
static void
yy_reduce_print (yyvsp, yyrule, parser)
    YYSTYPE *yyvsp;
    int yyrule;
    Parser* parser;
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , parser);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, parser); \
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, Parser* parser)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, parser)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    Parser* parser;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (parser);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




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
yyparse (Parser* parser)
#else
int
yyparse (parser)
    Parser* parser;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;


#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
static YYSTYPE yyval_default;
# define YY_INITIAL_VALUE(Value) = Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
        case 2:
/* Line 1792 of yacc.c  */
#line 66 "grammar.y"
    { parser->saveRoot(new AST::Program((yyvsp[(1) - (1)].clist)));}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 69 "grammar.y"
    { if ((yyvsp[(1) - (2)].cls)) (yyvsp[(2) - (2)].clist)->push_front((yyvsp[(1) - (2)].cls));(yyval.clist)= (yyvsp[(2) - (2)].clist); }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 70 "grammar.y"
    { (yyval.clist) = new std::list<AST::Class*>();}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 73 "grammar.y"
    { (yyval.cls) = new AST::BClass((yyvsp[(2) - (6)].id),(yyvsp[(4) - (6)].dlist));}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 74 "grammar.y"
    { (yyval.cls) = new AST::DClass((yyvsp[(2) - (8)].id),(yyvsp[(4) - (8)].id),(yyvsp[(6) - (8)].dlist));}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 77 "grammar.y"
    { (yyval.dlist) = (yyvsp[(2) - (2)].dlist);(yyval.dlist)->push_front((yyvsp[(1) - (2)].decl));}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 78 "grammar.y"
    { (yyval.dlist) = new std::list<AST::Decl*>();}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 81 "grammar.y"
    { (yyval.decl) = new AST::Attribute((yyvsp[(1) - (3)].type),(yyvsp[(2) - (3)].id));}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 82 "grammar.y"
    { (yyval.decl) = new AST::Method((yyvsp[(1) - (8)].type),(yyvsp[(2) - (8)].id),(yyvsp[(4) - (8)].dlist),new AST::Block((yyvsp[(7) - (8)].slist)));}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 83 "grammar.y"
    { (yyval.decl) = new AST::Constructor((yyvsp[(1) - (7)].id),(yyvsp[(3) - (7)].dlist),new AST::Block((yyvsp[(6) - (7)].slist)));}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 86 "grammar.y"
    { (yyval.dlist) = (yyvsp[(1) - (1)].dlist);}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 87 "grammar.y"
    { (yyval.dlist) = new std::list<AST::Decl*>();}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 90 "grammar.y"
    { (yyval.dlist) = new std::list<AST::Decl*>();(yyval.dlist)->push_front((yyvsp[(1) - (1)].decl));}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 91 "grammar.y"
    { (yyval.dlist) = (yyvsp[(3) - (3)].dlist);(yyval.dlist)->push_front((yyvsp[(1) - (3)].decl));}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 94 "grammar.y"
    { (yyval.decl) = new AST::Formal((yyvsp[(1) - (2)].type),(yyvsp[(2) - (2)].id));}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 97 "grammar.y"
    { (yyval.slist) = (yyvsp[(2) - (2)].slist);if ((yyvsp[(1) - (2)].stmt)) (yyvsp[(2) - (2)].slist)->push_front((yyvsp[(1) - (2)].stmt));}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 98 "grammar.y"
    { (yyval.slist) = new std::list<AST::Stmt*>();}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 101 "grammar.y"
    { (yyval.stmt) = new AST::StmtExpr((yyvsp[(1) - (2)].expr));}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 102 "grammar.y"
    { (yyval.stmt) = new AST::StmtLocalDecl((yyvsp[(1) - (3)].type),new AST::Identifier((yyvsp[(2) - (3)].id)));}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 103 "grammar.y"
    { (yyval.stmt) = new AST::StmtAssign((yyvsp[(1) - (4)].expr),(yyvsp[(3) - (4)].expr));}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 104 "grammar.y"
    { (yyval.stmt) = new AST::Block((yyvsp[(2) - (3)].slist));}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 105 "grammar.y"
    { (yyval.stmt) = new AST::While((yyvsp[(3) - (5)].expr),(yyvsp[(5) - (5)].stmt));}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 106 "grammar.y"
    { (yyval.stmt) = new AST::IfTE((yyvsp[(3) - (5)].expr),(yyvsp[(5) - (5)].stmt),0);}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 107 "grammar.y"
    { (yyval.stmt) = new AST::IfTE((yyvsp[(3) - (7)].expr),(yyvsp[(5) - (7)].stmt),(yyvsp[(7) - (7)].stmt));}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 108 "grammar.y"
    { (yyval.stmt) = new AST::Return((yyvsp[(2) - (3)].expr));}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 109 "grammar.y"
    { (yyval.stmt) = 0;}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 112 "grammar.y"
    { (yyval.expr) = new AST::And((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 113 "grammar.y"
    { (yyval.expr) = new AST::Or((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 114 "grammar.y"
    { (yyval.expr) = new AST::Not((yyvsp[(2) - (2)].expr));}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 115 "grammar.y"
    { (yyval.expr) = new AST::LThen((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 116 "grammar.y"
    { (yyval.expr) = new AST::GThen((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 117 "grammar.y"
    { (yyval.expr) = new AST::LEThen((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 118 "grammar.y"
    { (yyval.expr) = new AST::GEThen((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 119 "grammar.y"
    { (yyval.expr) = new AST::Equal((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 120 "grammar.y"
    { (yyval.expr) = new AST::NEqual((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 121 "grammar.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr);}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 124 "grammar.y"
    { (yyval.expr) = new AST::Add((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 125 "grammar.y"
    { (yyval.expr) = new AST::Sub((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 126 "grammar.y"
    { (yyval.expr) = new AST::Mul((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 127 "grammar.y"
    { (yyval.expr) = new AST::Div((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].expr));}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 128 "grammar.y"
    { (yyval.expr) = new AST::Number((yyvsp[(1) - (1)].val));}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 129 "grammar.y"
    { (yyval.expr) = new AST::Boolean(1);}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 130 "grammar.y"
    { (yyval.expr) = new AST::Boolean(0);}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 131 "grammar.y"
    { (yyval.expr) = new AST::Opposite((yyvsp[(2) - (2)].expr));}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 132 "grammar.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr);}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 133 "grammar.y"
    { (yyval.expr) = new AST::InstantiateObject(new AST::Identifier((yyvsp[(2) - (5)].id)),(yyvsp[(4) - (5)].elist));}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 134 "grammar.y"
    { (yyval.expr) = new AST::InstantiateArray((yyvsp[(2) - (5)].type),(yyvsp[(4) - (5)].expr));}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 135 "grammar.y"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr);}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 138 "grammar.y"
    { (yyval.expr) = new AST::Identifier((yyvsp[(1) - (1)].id));}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 139 "grammar.y"
    { (yyval.expr) = new AST::MthCall((yyvsp[(1) - (4)].expr),(yyvsp[(3) - (4)].elist));}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 140 "grammar.y"
    { (yyval.expr) = new AST::Deref((yyvsp[(1) - (3)].expr),(yyvsp[(3) - (3)].id));}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 141 "grammar.y"
    { (yyval.expr) = new AST::ArrayIndex((yyvsp[(1) - (4)].expr),(yyvsp[(3) - (4)].expr));}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 142 "grammar.y"
    { (yyval.expr) = new AST::Identifier(strdup("this"));}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 145 "grammar.y"
    { (yyval.elist) = (yyvsp[(1) - (1)].elist);}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 146 "grammar.y"
    { (yyval.elist) = new std::list<AST::Expr*>();}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 149 "grammar.y"
    { (yyval.elist) = new std::list<AST::Expr*>();(yyval.elist)->push_front((yyvsp[(1) - (1)].expr));}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 150 "grammar.y"
    { (yyval.elist) = (yyvsp[(3) - (3)].elist);(yyval.elist)->push_front((yyvsp[(1) - (3)].expr));}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 153 "grammar.y"
    { (yyval.type) = new AST::TypeInt();}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 154 "grammar.y"
    { (yyval.type) = new AST::TypeBool();}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 155 "grammar.y"
    { (yyval.type) = new AST::TypeVoid();}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 156 "grammar.y"
    { (yyval.type) = new AST::TypeClass(new AST::Identifier((yyvsp[(1) - (1)].id)));}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 159 "grammar.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type);}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 160 "grammar.y"
    { (yyval.type) = new AST::TypeArray((yyvsp[(1) - (2)].type));}
    break;


/* Line 1792 of yacc.c  */
#line 1907 "grammar.c"
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (parser, YY_("syntax error"));
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
        yyerror (parser, yymsgp);
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
		      yytoken, &yylval, parser);
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
		  yystos[yystate], yyvsp, parser);
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
  yyerror (parser, YY_("memory exhausted"));
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
                  yytoken, &yylval, parser);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, parser);
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


/* Line 2055 of yacc.c  */
#line 163 "grammar.y"

