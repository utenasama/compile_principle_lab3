/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"

#include <ast/ast.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <errno.h>


extern Root_ptr root;
extern int line_count;
extern int yylineno;
extern char *yytext;
extern int yylex();
extern int yyparse();
extern bool error;
void yyerror(const char *s);
int syntax_error = 0;

#line 90 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "sysy.tab.hh"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INT_CONST = 4,                  /* INT_CONST  */
  YYSYMBOL_ADD = 5,                        /* ADD  */
  YYSYMBOL_SUB = 6,                        /* SUB  */
  YYSYMBOL_MUL = 7,                        /* MUL  */
  YYSYMBOL_DIV = 8,                        /* DIV  */
  YYSYMBOL_MOD = 9,                        /* MOD  */
  YYSYMBOL_LT = 10,                        /* LT  */
  YYSYMBOL_LE = 11,                        /* LE  */
  YYSYMBOL_GT = 12,                        /* GT  */
  YYSYMBOL_GE = 13,                        /* GE  */
  YYSYMBOL_L_AND = 14,                     /* L_AND  */
  YYSYMBOL_L_OR = 15,                      /* L_OR  */
  YYSYMBOL_L_EQUAL = 16,                   /* L_EQUAL  */
  YYSYMBOL_L_NOT = 17,                     /* L_NOT  */
  YYSYMBOL_ASSIGN = 18,                    /* ASSIGN  */
  YYSYMBOL_NE = 19,                        /* NE  */
  YYSYMBOL_INT = 20,                       /* INT  */
  YYSYMBOL_VOID = 21,                      /* VOID  */
  YYSYMBOL_RETURN = 22,                    /* RETURN  */
  YYSYMBOL_IF = 23,                        /* IF  */
  YYSYMBOL_ELSE = 24,                      /* ELSE  */
  YYSYMBOL_WHILE = 25,                     /* WHILE  */
  YYSYMBOL_BREAK = 26,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 27,                  /* CONTINUE  */
  YYSYMBOL_LP = 28,                        /* LP  */
  YYSYMBOL_RP = 29,                        /* RP  */
  YYSYMBOL_LB = 30,                        /* LB  */
  YYSYMBOL_RB = 31,                        /* RB  */
  YYSYMBOL_LC = 32,                        /* LC  */
  YYSYMBOL_RC = 33,                        /* RC  */
  YYSYMBOL_COMMA = 34,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 35,                 /* SEMICOLON  */
  YYSYMBOL_YYACCEPT = 36,                  /* $accept  */
  YYSYMBOL_Root = 37,                      /* Root  */
  YYSYMBOL_CompUnit = 38,                  /* CompUnit  */
  YYSYMBOL_VarDecl = 39,                   /* VarDecl  */
  YYSYMBOL_VarDef = 40,                    /* VarDef  */
  YYSYMBOL_InitVal = 41,                   /* InitVal  */
  YYSYMBOL_Cond = 42,                      /* Cond  */
  YYSYMBOL_LOrExp = 43,                    /* LOrExp  */
  YYSYMBOL_LOrExp_Sub = 44,                /* LOrExp_Sub  */
  YYSYMBOL_LAndExp = 45,                   /* LAndExp  */
  YYSYMBOL_LAndExp_Sub = 46,               /* LAndExp_Sub  */
  YYSYMBOL_EqExp = 47,                     /* EqExp  */
  YYSYMBOL_RelExp = 48,                    /* RelExp  */
  YYSYMBOL_Stmt = 49,                      /* Stmt  */
  YYSYMBOL_M_Stmt = 50,                    /* M_Stmt  */
  YYSYMBOL_U_Stmt = 51,                    /* U_Stmt  */
  YYSYMBOL_Exp = 52,                       /* Exp  */
  YYSYMBOL_AddExp = 53,                    /* AddExp  */
  YYSYMBOL_MulExp = 54,                    /* MulExp  */
  YYSYMBOL_FuncDef = 55,                   /* FuncDef  */
  YYSYMBOL_FuncFParam = 56,                /* FuncFParam  */
  YYSYMBOL_Block = 57,                     /* Block  */
  YYSYMBOL_BlockItem = 58,                 /* BlockItem  */
  YYSYMBOL_UnaryExp = 59,                  /* UnaryExp  */
  YYSYMBOL_FuncRParams = 60,               /* FuncRParams  */
  YYSYMBOL_PrimaryExp = 61,                /* PrimaryExp  */
  YYSYMBOL_LVal = 62,                      /* LVal  */
  YYSYMBOL_ExpArray = 63                   /* ExpArray  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   164

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  148

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    85,    85,    92,    93,    94,    95,    98,   100,   101,
     102,   103,   106,   108,   110,   111,   112,   118,   119,   120,
     131,   132,   133,   142,   143,   144,   145,   146,   148,   148,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     163,   164,   165,   168,   171,   172,   173,   182,   183,   184,
     185,   193,   194,   195,   196,   198,   199,   200,   201,   203,
     204,   205,   206,   208,   209,   210,   211,   212,   213,   215,
     216,   218,   219,   220,   222,   225,   226
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INT_CONST",
  "ADD", "SUB", "MUL", "DIV", "MOD", "LT", "LE", "GT", "GE", "L_AND",
  "L_OR", "L_EQUAL", "L_NOT", "ASSIGN", "NE", "INT", "VOID", "RETURN",
  "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "LP", "RP", "LB", "RB", "LC",
  "RC", "COMMA", "SEMICOLON", "$accept", "Root", "CompUnit", "VarDecl",
  "VarDef", "InitVal", "Cond", "LOrExp", "LOrExp_Sub", "LAndExp",
  "LAndExp_Sub", "EqExp", "RelExp", "Stmt", "M_Stmt", "U_Stmt", "Exp",
  "AddExp", "MulExp", "FuncDef", "FuncFParam", "Block", "BlockItem",
  "UnaryExp", "FuncRParams", "PrimaryExp", "LVal", "ExpArray", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-117)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      38,     1,     4,    20,  -117,    38,    38,    34,   -10,    11,
    -117,  -117,  -117,    -8,    32,    -3,  -117,    -6,    62,    37,
      83,    66,  -117,    32,    32,    32,    32,  -117,   101,    52,
      76,    91,    78,    72,  -117,  -117,  -117,    32,   124,    37,
      99,    10,    50,  -117,    37,   131,  -117,  -117,  -117,  -117,
     100,    32,  -117,    32,    32,    32,  -117,    32,    32,    32,
      32,   102,    32,    32,    32,    32,    32,    97,  -117,   102,
    -117,  -117,    37,   107,   119,   124,    13,   112,   113,   108,
     109,  -117,    50,    50,  -117,  -117,   110,  -117,   114,   128,
    -117,  -117,   115,   121,  -117,   101,    52,    76,    76,    78,
      78,    78,    78,  -117,    72,    72,  -117,  -117,  -117,   124,
    -117,   102,  -117,  -117,   116,    32,    32,  -117,  -117,  -117,
    -117,  -117,  -117,    32,    32,  -117,  -117,  -117,  -117,   118,
    -117,   125,  -117,   126,   122,  -117,   119,    98,    98,  -117,
    -117,  -117,   129,  -117,  -117,    98,  -117,  -117
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     2,     3,     4,    75,     0,     0,
       1,     5,     6,     0,     0,     8,     7,     0,     0,     0,
       0,    75,    73,     0,     0,     0,     0,    43,    16,    19,
      20,     0,    27,    44,    47,    63,    72,     0,     0,     0,
       0,    55,    60,    51,     0,     0,    74,    66,    67,    68,
       0,     0,    14,     0,     0,     0,    17,     0,     0,     0,
       0,    75,     0,     0,     0,     0,     0,     9,    12,    75,
      11,    52,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    38,    60,    60,    28,    29,     0,    37,     0,    72,
      54,    64,    69,     0,    71,    16,    19,    21,    22,    23,
      24,    25,    26,    76,    45,    46,    48,    49,    50,     0,
      53,    75,    58,    34,     0,     0,     0,    31,    32,    61,
      62,    36,    59,     0,     0,    65,    15,    18,    10,    56,
      33,     0,    13,     0,     0,    70,     0,     0,     0,    35,
      57,    40,    28,    39,    42,     0,    30,    41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -117,  -117,    94,   -36,   -35,  -117,    26,    -9,    61,   111,
      65,   105,    54,    27,  -111,  -116,   -13,    33,    51,  -117,
     -17,   -11,    35,   -14,    39,  -117,   -40,   -16
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     4,     5,     8,    67,   131,    27,    52,    28,
      56,    29,    30,    83,    84,    85,    86,    32,    33,     6,
      20,    87,    88,    34,    93,    35,    36,    15
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      40,    31,    89,    70,     7,    46,    82,     9,    43,    47,
      48,    49,    18,    50,    18,    37,    21,    22,    23,    24,
      10,    19,   144,    39,    68,    16,   142,   143,    71,   147,
      25,    38,    92,    90,   146,    21,    22,    23,    24,    17,
      73,    26,    89,    89,    74,   103,    82,    82,   113,    25,
     106,   107,   108,    21,    22,    23,    24,   112,     1,     2,
      26,   110,    13,   114,    14,    41,    53,    25,    54,    42,
      75,    55,    76,    77,   128,    78,    79,    80,    26,    64,
      65,    66,    42,    62,    63,    81,    57,    58,    59,    60,
      99,   100,   101,   102,    45,   129,    14,    89,    89,    11,
      12,    21,    22,    23,    24,    89,   132,   132,    97,    98,
     134,    92,    44,   104,   105,    25,    51,   119,   120,   140,
      76,    77,    61,    78,    79,    80,    26,    69,    72,    94,
      42,   109,    14,    81,    21,    22,    23,    24,   111,    18,
     115,   116,   133,   117,   118,   121,   123,   122,    25,   124,
     125,   130,   136,   145,   137,   138,   126,   139,    96,    26,
      91,   127,    95,   135,   141
};

static const yytype_uint8 yycheck[] =
{
      17,    14,    42,    38,     3,    21,    42,     3,    19,    23,
      24,    25,    20,    26,    20,    18,     3,     4,     5,     6,
       0,    29,   138,    29,    37,    35,   137,   138,    39,   145,
      17,    34,    45,    44,   145,     3,     4,     5,     6,    28,
      30,    28,    82,    83,    34,    61,    82,    83,    35,    17,
      64,    65,    66,     3,     4,     5,     6,    74,    20,    21,
      28,    72,    28,    76,    30,     3,    14,    17,    16,    32,
      20,    19,    22,    23,   109,    25,    26,    27,    28,     7,
       8,     9,    32,     5,     6,    35,    10,    11,    12,    13,
      57,    58,    59,    60,    28,   111,    30,   137,   138,     5,
       6,     3,     4,     5,     6,   145,   115,   116,    54,    55,
     123,   124,    29,    62,    63,    17,    15,    82,    83,   136,
      22,    23,    31,    25,    26,    27,    28,     3,    29,    29,
      32,    34,    30,    35,     3,     4,     5,     6,    31,    20,
      28,    28,   116,    35,    35,    35,    18,    33,    17,    34,
      29,    35,    34,    24,    29,    29,    95,    35,    53,    28,
      29,    96,    51,   124,   137
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    20,    21,    37,    38,    39,    55,     3,    40,     3,
       0,    38,    38,    28,    30,    63,    35,    28,    20,    29,
      56,     3,     4,     5,     6,    17,    28,    43,    45,    47,
      48,    52,    53,    54,    59,    61,    62,    18,    34,    29,
      56,     3,    32,    57,    29,    28,    63,    59,    59,    59,
      52,    15,    44,    14,    16,    19,    46,    10,    11,    12,
      13,    31,     5,     6,     7,     8,     9,    41,    52,     3,
      40,    57,    29,    30,    34,    20,    22,    23,    25,    26,
      27,    35,    39,    49,    50,    51,    52,    57,    58,    62,
      57,    29,    52,    60,    29,    45,    47,    48,    48,    53,
      53,    53,    53,    63,    54,    54,    59,    59,    59,    34,
      57,    31,    56,    35,    52,    28,    28,    35,    35,    58,
      58,    35,    33,    18,    34,    29,    44,    46,    40,    63,
      35,    42,    43,    42,    52,    60,    34,    29,    29,    35,
      56,    49,    50,    50,    51,    24,    50,    51
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    37,    38,    38,    38,    38,    39,    40,    40,
      40,    40,    41,    42,    43,    44,    44,    45,    46,    46,
      47,    47,    47,    48,    48,    48,    48,    48,    49,    49,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      51,    51,    51,    52,    53,    53,    53,    54,    54,    54,
      54,    55,    55,    55,    55,    56,    56,    56,    56,    57,
      58,    58,    58,    59,    59,    59,    59,    59,    59,    60,
      60,    61,    61,    61,    62,    63,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     2,     3,     2,     4,
       6,     4,     1,     1,     2,     3,     0,     2,     3,     0,
       1,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       7,     2,     2,     3,     2,     4,     2,     1,     1,     5,
       5,     7,     5,     1,     1,     3,     3,     1,     3,     3,
       3,     5,     5,     6,     6,     2,     5,     7,     4,     3,
       0,     2,     2,     1,     3,     4,     2,     2,     2,     1,
       3,     3,     1,     1,     2,     0,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* Root: CompUnit  */
#line 85 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
               { root = new TreeRoot((yyvsp[0].compunit_ptr)); }
#line 1506 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 3: /* CompUnit: VarDecl  */
#line 92 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                  { (yyval.compunit_ptr) = new Node_CompUnitValDec((yyvsp[0].valdec_ptr), nullptr); }
#line 1512 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 4: /* CompUnit: FuncDef  */
#line 93 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                  { (yyval.compunit_ptr) = new Node_CompUnitFunDec((yyvsp[0].fundef_ptr), nullptr); }
#line 1518 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 5: /* CompUnit: VarDecl CompUnit  */
#line 94 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                           { (yyval.compunit_ptr) = new Node_CompUnitValDec((yyvsp[-1].valdec_ptr), (yyvsp[0].compunit_ptr)); }
#line 1524 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 6: /* CompUnit: FuncDef CompUnit  */
#line 95 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                           { (yyval.compunit_ptr) = new Node_CompUnitFunDec((yyvsp[-1].fundef_ptr), (yyvsp[0].compunit_ptr)); }
#line 1530 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 7: /* VarDecl: INT VarDef SEMICOLON  */
#line 98 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                              { (yyval.valdec_ptr) = (yyvsp[-1].valdec_ptr); }
#line 1536 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 8: /* VarDef: ID ExpArray  */
#line 100 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                    { (yyval.valdec_ptr) = new Node_ValDec((yyvsp[-1].str_Val), (yyvsp[0].exparr_ptr), nullptr, nullptr); }
#line 1542 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 9: /* VarDef: ID ExpArray ASSIGN InitVal  */
#line 101 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                         { (yyval.valdec_ptr) = new Node_ValDec((yyvsp[-3].str_Val), (yyvsp[-2].exparr_ptr), (yyvsp[0].lor_ptr), nullptr); }
#line 1548 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 10: /* VarDef: ID ExpArray ASSIGN InitVal COMMA VarDef  */
#line 102 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                                      { (yyval.valdec_ptr) = new Node_ValDec((yyvsp[-5].str_Val), (yyvsp[-4].exparr_ptr), (yyvsp[-2].lor_ptr), (yyvsp[0].valdec_ptr)); }
#line 1554 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 11: /* VarDef: ID ExpArray COMMA VarDef  */
#line 103 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                       { (yyval.valdec_ptr) = new Node_ValDec((yyvsp[-3].str_Val), (yyvsp[-2].exparr_ptr), nullptr, (yyvsp[0].valdec_ptr)); }
#line 1560 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 12: /* InitVal: Exp  */
#line 106 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
             { (yyval.lor_ptr) = (yyvsp[0].lor_ptr); }
#line 1566 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 13: /* Cond: LOrExp  */
#line 108 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
             { (yyval.lor_ptr) = (yyvsp[0].lor_ptr); }
#line 1572 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 14: /* LOrExp: LAndExp LOrExp_Sub  */
#line 110 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                           { (yyval.lor_ptr) = new Node_LOr((yyvsp[0].lor_ptr), (yyvsp[-1].land_ptr)); }
#line 1578 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 15: /* LOrExp_Sub: L_OR LAndExp LOrExp_Sub  */
#line 111 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                    { (yyval.lor_ptr) = new Node_LOr((yyvsp[0].lor_ptr), (yyvsp[-1].land_ptr)); }
#line 1584 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 16: /* LOrExp_Sub: %empty  */
#line 112 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                    { (yyval.lor_ptr) = nullptr; }
#line 1590 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 17: /* LAndExp: EqExp LAndExp_Sub  */
#line 118 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                           { (yyval.land_ptr) = new Node_LAnd((yyvsp[0].land_ptr), (yyvsp[-1].eq_ptr)); }
#line 1596 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 18: /* LAndExp_Sub: L_AND EqExp LAndExp_Sub  */
#line 119 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                     { (yyval.land_ptr) = new Node_LAnd((yyvsp[0].land_ptr), (yyvsp[-1].eq_ptr)); }
#line 1602 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 19: /* LAndExp_Sub: %empty  */
#line 120 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
              { (yyval.land_ptr) = nullptr; }
#line 1608 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 20: /* EqExp: RelExp  */
#line 131 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
              { (yyval.eq_ptr) = new Node_Eq(nullptr, OP_None, (yyvsp[0].rel_ptr)); }
#line 1614 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 21: /* EqExp: EqExp L_EQUAL RelExp  */
#line 132 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                   { (yyval.eq_ptr) = new Node_Eq((yyvsp[-2].eq_ptr), OP_Eq, (yyvsp[0].rel_ptr)); }
#line 1620 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 22: /* EqExp: EqExp NE RelExp  */
#line 133 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                              { (yyval.eq_ptr) = new Node_Eq((yyvsp[-2].eq_ptr), OP_Ne, (yyvsp[0].rel_ptr)); }
#line 1626 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 23: /* RelExp: RelExp LT AddExp  */
#line 142 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                          { (yyval.rel_ptr) = new Node_Rel((yyvsp[-2].rel_ptr), OP_Lt, (yyvsp[0].addexp_ptr)); }
#line 1632 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 24: /* RelExp: RelExp LE AddExp  */
#line 143 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                               { (yyval.rel_ptr) = new Node_Rel((yyvsp[-2].rel_ptr), OP_Le, (yyvsp[0].addexp_ptr)); }
#line 1638 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 25: /* RelExp: RelExp GT AddExp  */
#line 144 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                               { (yyval.rel_ptr) = new Node_Rel((yyvsp[-2].rel_ptr), OP_Gt, (yyvsp[0].addexp_ptr)); }
#line 1644 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 26: /* RelExp: RelExp GE AddExp  */
#line 145 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                               { (yyval.rel_ptr) = new Node_Rel((yyvsp[-2].rel_ptr), OP_Ge, (yyvsp[0].addexp_ptr)); }
#line 1650 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 27: /* RelExp: AddExp  */
#line 146 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                     { (yyval.rel_ptr) = new Node_Rel(nullptr, OP_None, (yyvsp[0].addexp_ptr)); }
#line 1656 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 28: /* Stmt: M_Stmt  */
#line 148 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
             { (yyval.stmt_ptr) = (yyvsp[0].stmt_ptr); }
#line 1662 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 29: /* Stmt: U_Stmt  */
#line 148 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                   { (yyval.stmt_ptr) = (yyvsp[0].stmt_ptr); }
#line 1668 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 30: /* M_Stmt: IF LP Cond RP M_Stmt ELSE M_Stmt  */
#line 151 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                         { (yyval.stmt_ptr) = new Node_IfStmt((yyvsp[-4].lor_ptr), (yyvsp[-2].stmt_ptr), (yyvsp[0].stmt_ptr)); }
#line 1674 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 31: /* M_Stmt: BREAK SEMICOLON  */
#line 152 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                              { (yyval.stmt_ptr) = new Node_BreakStmt(); }
#line 1680 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 32: /* M_Stmt: CONTINUE SEMICOLON  */
#line 153 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                 { (yyval.stmt_ptr) = new Node_ContiStmt(); }
#line 1686 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 33: /* M_Stmt: RETURN Exp SEMICOLON  */
#line 154 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                   { (yyval.stmt_ptr) = new Node_RetStmt((yyvsp[-1].lor_ptr)); }
#line 1692 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 34: /* M_Stmt: RETURN SEMICOLON  */
#line 155 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                               { (yyval.stmt_ptr) = new Node_RetStmt(nullptr); }
#line 1698 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 35: /* M_Stmt: LVal ASSIGN Exp SEMICOLON  */
#line 156 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                        { (yyval.stmt_ptr) = new Node_LValStmt((yyvsp[-3].lval_ptr), (yyvsp[-1].lor_ptr)); }
#line 1704 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 36: /* M_Stmt: Exp SEMICOLON  */
#line 157 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                            { (yyval.stmt_ptr) = new Node_ExpStmt((yyvsp[-1].lor_ptr)); }
#line 1710 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 37: /* M_Stmt: Block  */
#line 158 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                    { (yyval.stmt_ptr) = new Node_BlockInStmt((yyvsp[0].block_ptr)); }
#line 1716 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 38: /* M_Stmt: SEMICOLON  */
#line 159 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                        { (yyval.stmt_ptr) = new Node_EmptyStmt();  }
#line 1722 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 39: /* M_Stmt: WHILE LP Cond RP M_Stmt  */
#line 160 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                      { (yyval.stmt_ptr) = new Node_WhileStmt((yyvsp[-2].lor_ptr), (yyvsp[0].stmt_ptr)); }
#line 1728 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 40: /* U_Stmt: IF LP Cond RP Stmt  */
#line 163 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                           { (yyval.stmt_ptr) = new Node_IfStmt((yyvsp[-2].lor_ptr), (yyvsp[0].stmt_ptr), nullptr); }
#line 1734 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 41: /* U_Stmt: IF LP Cond RP M_Stmt ELSE U_Stmt  */
#line 164 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                               { (yyval.stmt_ptr) = new Node_IfStmt((yyvsp[-4].lor_ptr), (yyvsp[-2].stmt_ptr), (yyvsp[0].stmt_ptr)); }
#line 1740 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 42: /* U_Stmt: WHILE LP Cond RP U_Stmt  */
#line 165 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                      { (yyval.stmt_ptr) = new Node_WhileStmt((yyvsp[-2].lor_ptr), (yyvsp[0].stmt_ptr)); }
#line 1746 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 43: /* Exp: LOrExp  */
#line 168 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
            { (yyval.lor_ptr) = (yyvsp[0].lor_ptr); }
#line 1752 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 44: /* AddExp: MulExp  */
#line 171 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
               { (yyval.addexp_ptr) = new Node_AddExpr(nullptr, OP_None, (yyvsp[0].mulexp_ptr)); }
#line 1758 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 45: /* AddExp: AddExp ADD MulExp  */
#line 172 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                { (yyval.addexp_ptr) = new Node_AddExpr((yyvsp[-2].addexp_ptr), OP_Add, (yyvsp[0].mulexp_ptr)); }
#line 1764 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 46: /* AddExp: AddExp SUB MulExp  */
#line 173 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                { (yyval.addexp_ptr) = new Node_AddExpr((yyvsp[-2].addexp_ptr), OP_Sub, (yyvsp[0].mulexp_ptr)); }
#line 1770 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 47: /* MulExp: UnaryExp  */
#line 182 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                 { (yyval.mulexp_ptr) = new Node_MulExpr(nullptr, OP_None, (yyvsp[0].unaexpr_ptr)); }
#line 1776 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 48: /* MulExp: MulExp MUL UnaryExp  */
#line 183 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                  { (yyval.mulexp_ptr) = new Node_MulExpr((yyvsp[-2].mulexp_ptr), OP_Mul, (yyvsp[0].unaexpr_ptr)); }
#line 1782 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 49: /* MulExp: MulExp DIV UnaryExp  */
#line 184 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                  { (yyval.mulexp_ptr) = new Node_MulExpr((yyvsp[-2].mulexp_ptr), OP_Div, (yyvsp[0].unaexpr_ptr)); }
#line 1788 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 50: /* MulExp: MulExp MOD UnaryExp  */
#line 185 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                  { (yyval.mulexp_ptr) = new Node_MulExpr((yyvsp[-2].mulexp_ptr), OP_Mod, (yyvsp[0].unaexpr_ptr)); }
#line 1794 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 51: /* FuncDef: INT ID LP RP Block  */
#line 193 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                            { (yyval.fundef_ptr) = new Node_FunDef(Ret_Int, (yyvsp[-3].str_Val), nullptr, (yyvsp[0].block_ptr)); }
#line 1800 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 52: /* FuncDef: VOID ID LP RP Block  */
#line 194 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                  { (yyval.fundef_ptr) = new Node_FunDef(Ret_Void, (yyvsp[-3].str_Val), nullptr, (yyvsp[0].block_ptr)); }
#line 1806 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 53: /* FuncDef: VOID ID LP FuncFParam RP Block  */
#line 195 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                             { (yyval.fundef_ptr) = new Node_FunDef(Ret_Void, (yyvsp[-4].str_Val), (yyvsp[-2].funfparam_ptr), (yyvsp[0].block_ptr)); }
#line 1812 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 54: /* FuncDef: INT ID LP FuncFParam RP Block  */
#line 196 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                            { (yyval.fundef_ptr) = new Node_FunDef(Ret_Int, (yyvsp[-4].str_Val), (yyvsp[-2].funfparam_ptr), (yyvsp[0].block_ptr)); }
#line 1818 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 55: /* FuncFParam: INT ID  */
#line 198 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                   { (yyval.funfparam_ptr) = new Node_FunFParam((yyvsp[0].str_Val), false, nullptr, nullptr); }
#line 1824 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 56: /* FuncFParam: INT ID LB RB ExpArray  */
#line 199 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                    { (yyval.funfparam_ptr) = new Node_FunFParam((yyvsp[-3].str_Val), true, (yyvsp[0].exparr_ptr), nullptr); }
#line 1830 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 57: /* FuncFParam: INT ID LB RB ExpArray COMMA FuncFParam  */
#line 200 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                                     { (yyval.funfparam_ptr) = new Node_FunFParam((yyvsp[-5].str_Val), true, (yyvsp[-2].exparr_ptr), (yyvsp[0].funfparam_ptr)); }
#line 1836 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 58: /* FuncFParam: INT ID COMMA FuncFParam  */
#line 201 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                      { (yyval.funfparam_ptr) = new Node_FunFParam((yyvsp[-2].str_Val), false, nullptr, (yyvsp[0].funfparam_ptr)); }
#line 1842 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 59: /* Block: LC BlockItem RC  */
#line 203 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                       { (yyval.block_ptr) = new Node_Block((yyvsp[-1].blockitem_ptr)); }
#line 1848 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 60: /* BlockItem: %empty  */
#line 204 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
           { (yyval.blockitem_ptr) = nullptr; }
#line 1854 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 61: /* BlockItem: VarDecl BlockItem  */
#line 205 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                { (yyval.blockitem_ptr) = new Node_BlockValDecItem((yyvsp[-1].valdec_ptr), (yyvsp[0].blockitem_ptr)); }
#line 1860 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 62: /* BlockItem: Stmt BlockItem  */
#line 206 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                             { (yyval.blockitem_ptr) = new Node_BlockStmtItem((yyvsp[-1].stmt_ptr), (yyvsp[0].blockitem_ptr)); }
#line 1866 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 63: /* UnaryExp: PrimaryExp  */
#line 208 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                     { (yyval.unaexpr_ptr) = (yyvsp[0].primexpr_ptr); }
#line 1872 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 64: /* UnaryExp: ID LP RP  */
#line 209 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                       { (yyval.unaexpr_ptr) = new Node_FuncUnaExpr((yyvsp[-2].str_Val), nullptr); }
#line 1878 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 65: /* UnaryExp: ID LP FuncRParams RP  */
#line 210 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                   { (yyval.unaexpr_ptr) = new Node_FuncUnaExpr((yyvsp[-3].str_Val), (yyvsp[-1].funrparam_ptr)); }
#line 1884 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 66: /* UnaryExp: ADD UnaryExp  */
#line 211 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                           { (yyval.unaexpr_ptr) = new Node_PMNUnaExpr(OP_Pos, (yyvsp[0].unaexpr_ptr)); }
#line 1890 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 67: /* UnaryExp: SUB UnaryExp  */
#line 212 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                           { (yyval.unaexpr_ptr) = new Node_PMNUnaExpr(OP_Neg, (yyvsp[0].unaexpr_ptr)); }
#line 1896 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 68: /* UnaryExp: L_NOT UnaryExp  */
#line 213 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                             { (yyval.unaexpr_ptr) = new Node_PMNUnaExpr(OP_Lnot, (yyvsp[0].unaexpr_ptr)); }
#line 1902 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 69: /* FuncRParams: Exp  */
#line 215 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                 { (yyval.funrparam_ptr) = new Node_FunRParam((yyvsp[0].lor_ptr), nullptr); }
#line 1908 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 70: /* FuncRParams: Exp COMMA FuncRParams  */
#line 216 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                    { (yyval.funrparam_ptr) = new Node_FunRParam((yyvsp[-2].lor_ptr), (yyvsp[0].funrparam_ptr)); }
#line 1914 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 71: /* PrimaryExp: LP Exp RP  */
#line 218 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                      { (yyval.primexpr_ptr) = new Node_LpExprRp((yyvsp[-1].lor_ptr)); }
#line 1920 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 72: /* PrimaryExp: LVal  */
#line 219 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                   { (yyval.primexpr_ptr) = (yyvsp[0].lval_ptr); }
#line 1926 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 73: /* PrimaryExp: INT_CONST  */
#line 220 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                        { (yyval.primexpr_ptr) = new Node_Integer((yyvsp[0].int_Val)); }
#line 1932 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 74: /* LVal: ID ExpArray  */
#line 222 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                  { (yyval.lval_ptr) = new Node_LVal((yyvsp[-1].str_Val), (yyvsp[0].exparr_ptr)); }
#line 1938 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 75: /* ExpArray: %empty  */
#line 225 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
          { (yyval.exparr_ptr) = nullptr; }
#line 1944 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;

  case 76: /* ExpArray: LB Exp RB ExpArray  */
#line 226 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"
                                 { (yyval.exparr_ptr) = new Node_ExpArr((yyvsp[-2].lor_ptr), (yyvsp[0].exparr_ptr)); }
#line 1950 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"
    break;


#line 1954 "/home/kaill/Desktop/lab3/compile_principle_lab3/build/sysy.tab.cc"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 227 "/home/kaill/Desktop/lab3/compile_principle_lab3/src/sysy.y"



#include<stdarg.h>
void yyerror(const char *s) {
    printf("line: %d  error: %s\n", yylineno, s);
    error = 1;
}

