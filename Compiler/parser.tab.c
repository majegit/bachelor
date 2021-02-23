/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
#define YYBISON 30704

/* Bison version string.  */
#define YYBISON_VERSION "3.7.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "Parser.y"

#include <stdio.h>
#include <stdlib.h>
extern char *yytext;
struct PROGRAM;

#line 78 "Parser.tab.c"

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

#include "Parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_tIDENTIFIER = 3,                /* tIDENTIFIER  */
  YYSYMBOL_tINT = 4,                       /* tINT  */
  YYSYMBOL_tDOUBLE = 5,                    /* tDOUBLE  */
  YYSYMBOL_tBOOLEAN = 6,                   /* tBOOLEAN  */
  YYSYMBOL_tCHAR = 7,                      /* tCHAR  */
  YYSYMBOL_tUNKNOWN = 8,                   /* tUNKNOWN  */
  YYSYMBOL_9_ = 9,                         /* '+'  */
  YYSYMBOL_10_ = 10,                       /* '-'  */
  YYSYMBOL_11_ = 11,                       /* '*'  */
  YYSYMBOL_12_ = 12,                       /* '/'  */
  YYSYMBOL_13_L_ = 13,                     /* "L"  */
  YYSYMBOL_14_G_ = 14,                     /* "G"  */
  YYSYMBOL_15_LEQ_ = 15,                   /* "LEQ"  */
  YYSYMBOL_16_GEQ_ = 16,                   /* "GEQ"  */
  YYSYMBOL_17_EQ_ = 17,                    /* "EQ"  */
  YYSYMBOL_18_NEQ_ = 18,                   /* "NEQ"  */
  YYSYMBOL_19_OR_ = 19,                    /* "OR"  */
  YYSYMBOL_20_AND_ = 20,                   /* "AND"  */
  YYSYMBOL_21_BOOLEAN_ = 21,               /* "BOOLEAN"  */
  YYSYMBOL_22_INT_ = 22,                   /* "INT"  */
  YYSYMBOL_23_CHAR_ = 23,                  /* "CHAR"  */
  YYSYMBOL_24_DOUBLE_ = 24,                /* "DOUBLE"  */
  YYSYMBOL_25_MAIN_ = 25,                  /* "MAIN"  */
  YYSYMBOL_26_ = 26,                       /* '('  */
  YYSYMBOL_27_ = 27,                       /* ')'  */
  YYSYMBOL_28_WHILE_ = 28,                 /* "WHILE"  */
  YYSYMBOL_29_IF_ = 29,                    /* "IF"  */
  YYSYMBOL_30_ELSE_ = 30,                  /* "ELSE"  */
  YYSYMBOL_31_RETURN_ = 31,                /* "RETURN"  */
  YYSYMBOL_32_ = 32,                       /* ';'  */
  YYSYMBOL_33_PRINT_ = 33,                 /* "PRINT"  */
  YYSYMBOL_34_ = 34,                       /* '='  */
  YYSYMBOL_35_ = 35,                       /* '{'  */
  YYSYMBOL_36_ = 36,                       /* '}'  */
  YYSYMBOL_37_ = 37,                       /* ','  */
  YYSYMBOL_38_FUNCTION_ = 38,              /* "FUNCTION"  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_program = 40,                   /* program  */
  YYSYMBOL_exp = 41,                       /* exp  */
  YYSYMBOL_stmt = 42,                      /* stmt  */
  YYSYMBOL_stmtcompound = 43,              /* stmtcompound  */
  YYSYMBOL_stmtnode = 44,                  /* stmtnode  */
  YYSYMBOL_aparameter = 45,                /* aparameter  */
  YYSYMBOL_aparameternode = 46,            /* aparameternode  */
  YYSYMBOL_fparameter = 47,                /* fparameter  */
  YYSYMBOL_fparameternode = 48,            /* fparameternode  */
  YYSYMBOL_function = 49,                  /* function  */
  YYSYMBOL_functionnode = 50,              /* functionnode  */
  YYSYMBOL_type = 51                       /* type  */
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
typedef yytype_int8 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   233

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  53
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  106

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   282


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
      26,    27,    11,     9,    37,    10,     2,    12,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    32,
       2,    34,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       5,     6,     7,     8,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    28,    29,    30,
      31,    33,    38
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    48,    48,    51,    56,    58,    60,    62,    64,    66,
      68,    70,    72,    74,    76,    78,    80,    82,    84,    86,
      88,    90,    92,    94,    96,   101,   103,   105,   107,   109,
     111,   113,   115,   119,   123,   125,   129,   131,   133,   135,
     137,   141,   143,   147,   151,   153,   157,   159,   163,   165,
     169,   171,   173,   175
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "tIDENTIFIER", "tINT",
  "tDOUBLE", "tBOOLEAN", "tCHAR", "tUNKNOWN", "'+'", "'-'", "'*'", "'/'",
  "\"L\"", "\"G\"", "\"LEQ\"", "\"GEQ\"", "\"EQ\"", "\"NEQ\"", "\"OR\"",
  "\"AND\"", "\"BOOLEAN\"", "\"INT\"", "\"CHAR\"", "\"DOUBLE\"",
  "\"MAIN\"", "'('", "')'", "\"WHILE\"", "\"IF\"", "\"ELSE\"",
  "\"RETURN\"", "';'", "\"PRINT\"", "'='", "'{'", "'}'", "','",
  "\"FUNCTION\"", "$accept", "program", "exp", "stmt", "stmtcompound",
  "stmtnode", "aparameter", "aparameternode", "fparameter",
  "fparameternode", "function", "functionnode", "type", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,    43,
      45,    42,    47,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,    40,    41,   277,   278,
     279,   280,    59,   281,    61,   123,   125,    44,   282
};
#endif

#define YYPACT_NINF (-50)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -18,     1,    19,     2,   -50,    11,    39,   121,    -6,   -50,
     -50,   -50,   -50,    21,    23,    17,    17,    39,    14,    48,
     121,   -50,    20,    17,    17,    17,    31,   -50,   -50,   -50,
     -50,   -50,    17,    72,    96,   -50,   -50,   -16,   -50,    61,
     120,   168,   187,    -1,   206,    17,    17,    17,    17,    17,
      17,    17,    17,    17,    17,    17,    17,   -50,   -50,   -50,
      17,    40,   -50,    11,    11,   -50,   -50,   -50,   -50,   -50,
     -50,    28,    42,   -50,    83,    83,   104,   104,    -8,    -8,
      -8,    -8,    -8,    -8,    51,   -50,   144,    32,   -50,    49,
      70,   -50,   -50,    11,    41,    98,   123,    11,   -50,   -50,
     121,    11,   -50,   -50,   -50,   -50
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     3,     0,    50,
      53,    51,    52,     0,     0,     0,     0,    34,     0,     0,
      48,     2,     0,     0,     0,     0,     4,     5,     6,     7,
       8,    24,     0,     0,     0,    35,    33,     0,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,    29,    30,
       0,     0,    32,     0,     0,    36,    40,    38,    39,    37,
      23,    41,     0,     9,    11,    10,    12,    13,    14,    15,
      16,    17,    18,    19,    21,    20,     0,     0,    25,    27,
       0,    22,    31,     0,    44,     0,     0,     0,    42,    47,
       0,     0,    43,    26,    45,    46
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -50,   -50,   -15,   -50,   -49,   110,   -50,    56,   -50,    47,
     -50,   128,    -7
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    33,    17,     7,    18,    71,    72,    94,    95,
      20,    21,    19
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      22,    34,    65,    66,    67,    68,    69,     1,    40,    41,
      42,    55,    56,    22,    88,    89,    59,    44,    60,     4,
      26,    27,    28,    29,    30,    31,    70,     3,    23,     5,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,     8,    32,    99,    86,     6,    24,   103,    25,
      36,    37,   105,     9,    10,    11,    12,    43,    39,    93,
       9,    10,    11,    12,    61,    90,    87,    13,    14,    91,
      15,    56,    16,    65,    66,    67,    68,    69,   100,    97,
      96,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    96,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    49,    50,    51,
      52,    53,    54,    55,    56,   101,   102,    35,    58,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,     0,     9,    10,    11,    12,    98,   104,    38,     0,
       0,     0,    62,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    92,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,     0,
       0,     0,     0,     0,     0,    63,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,     0,     0,
       0,     0,     0,     0,    64,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,     0,     0,     0,
       0,     0,     0,    73
};

static const yytype_int8 yycheck[] =
{
       7,    16,     3,     4,     5,     6,     7,    25,    23,    24,
      25,    19,    20,    20,    63,    64,    32,    32,    34,     0,
       3,     4,     5,     6,     7,     8,    27,    26,    34,    27,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,     3,    26,    93,    60,    35,    26,    97,    26,
      36,     3,   101,    21,    22,    23,    24,    26,    38,    27,
      21,    22,    23,    24,     3,    37,    26,    28,    29,    27,
      31,    20,    33,     3,     4,     5,     6,     7,    37,    30,
      87,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,   100,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    32,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    13,    14,    15,
      16,    17,    18,    19,    20,    27,     3,    17,    32,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    -1,    21,    22,    23,    24,    90,   100,    20,    -1,
      -1,    -1,    32,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    27,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    27,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    27
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    25,    40,    26,     0,    27,    35,    43,     3,    21,
      22,    23,    24,    28,    29,    31,    33,    42,    44,    51,
      49,    50,    51,    34,    26,    26,     3,     4,     5,     6,
       7,     8,    26,    41,    41,    44,    36,     3,    50,    38,
      41,    41,    41,    26,    41,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    32,    32,    32,
      34,     3,    32,    27,    27,     3,     4,     5,     6,     7,
      27,    45,    46,    27,    41,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    41,    41,    41,    26,    43,    43,
      37,    27,    32,    27,    47,    48,    51,    30,    46,    43,
      37,    27,     3,    43,    48,    43
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    40,    41,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    41,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    41,    42,    42,    42,    42,    42,
      42,    42,    42,    43,    44,    44,    45,    45,    45,    45,
      45,    46,    46,    47,    48,    48,    49,    49,    50,    50,
      51,    51,    51,    51
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     4,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     3,     1,     5,     7,     5,     3,     3,
       3,     5,     4,     3,     1,     2,     1,     1,     1,     1,
       1,     1,     3,     2,     1,     3,     7,     6,     1,     2,
       1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
  case 2: /* program: "MAIN" '(' ')' stmtcompound functionnode  */
#line 49 "Parser.y"
          {(yyval.program) = makePROGRAM((yyvsp[-1].stmtcompound),(yyvsp[0].functionnode));
          printf("Great Success!");}
#line 1204 "Parser.tab.c"
    break;

  case 3: /* program: "MAIN" '(' ')' stmtcompound  */
#line 52 "Parser.y"
          {(yyval.program) = makePROGRAM((yyvsp[0].stmtcompound),NULL);
           printf("Great Success!");}
#line 1211 "Parser.tab.c"
    break;

  case 4: /* exp: tIDENTIFIER  */
#line 57 "Parser.y"
      {(yyval.exp) = makeEXPid((yyvsp[0].stringconst));}
#line 1217 "Parser.tab.c"
    break;

  case 5: /* exp: tINT  */
#line 59 "Parser.y"
      {(yyval.exp) = makeEXPint((yyvsp[0].intconst));}
#line 1223 "Parser.tab.c"
    break;

  case 6: /* exp: tDOUBLE  */
#line 61 "Parser.y"
      {(yyval.exp) = makeEXPint((yyvsp[0].doubleconst));}
#line 1229 "Parser.tab.c"
    break;

  case 7: /* exp: tBOOLEAN  */
#line 63 "Parser.y"
      {(yyval.exp) = makeEXPint((yyvsp[0].boolconst));}
#line 1235 "Parser.tab.c"
    break;

  case 8: /* exp: tCHAR  */
#line 65 "Parser.y"
      {(yyval.exp) = makeEXPint((yyvsp[0].charconst));}
#line 1241 "Parser.tab.c"
    break;

  case 9: /* exp: '(' exp ')'  */
#line 67 "Parser.y"
      {(yyval.exp) = (yyvsp[-1].exp);}
#line 1247 "Parser.tab.c"
    break;

  case 10: /* exp: exp '-' exp  */
#line 69 "Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),(yyvsp[-1].stringconst),(yyvsp[0].exp));}
#line 1253 "Parser.tab.c"
    break;

  case 11: /* exp: exp '+' exp  */
#line 71 "Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),(yyvsp[-1].stringconst),(yyvsp[0].exp));}
#line 1259 "Parser.tab.c"
    break;

  case 12: /* exp: exp '*' exp  */
#line 73 "Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),(yyvsp[-1].stringconst),(yyvsp[0].exp));}
#line 1265 "Parser.tab.c"
    break;

  case 13: /* exp: exp '/' exp  */
#line 75 "Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),(yyvsp[-1].stringconst),(yyvsp[0].exp));}
#line 1271 "Parser.tab.c"
    break;

  case 14: /* exp: exp "L" exp  */
#line 77 "Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),(yyvsp[-1].stringconst),(yyvsp[0].exp));}
#line 1277 "Parser.tab.c"
    break;

  case 15: /* exp: exp "G" exp  */
#line 79 "Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),(yyvsp[-1].stringconst),(yyvsp[0].exp));}
#line 1283 "Parser.tab.c"
    break;

  case 16: /* exp: exp "LEQ" exp  */
#line 81 "Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),(yyvsp[-1].stringconst),(yyvsp[0].exp));}
#line 1289 "Parser.tab.c"
    break;

  case 17: /* exp: exp "GEQ" exp  */
#line 83 "Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),(yyvsp[-1].stringconst),(yyvsp[0].exp));}
#line 1295 "Parser.tab.c"
    break;

  case 18: /* exp: exp "EQ" exp  */
#line 85 "Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),(yyvsp[-1].stringconst),(yyvsp[0].exp));}
#line 1301 "Parser.tab.c"
    break;

  case 19: /* exp: exp "NEQ" exp  */
#line 87 "Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),(yyvsp[-1].stringconst),(yyvsp[0].exp));}
#line 1307 "Parser.tab.c"
    break;

  case 20: /* exp: exp "AND" exp  */
#line 89 "Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),(yyvsp[-1].stringconst),(yyvsp[0].exp));}
#line 1313 "Parser.tab.c"
    break;

  case 21: /* exp: exp "OR" exp  */
#line 91 "Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),(yyvsp[-1].stringconst),(yyvsp[0].exp));}
#line 1319 "Parser.tab.c"
    break;

  case 22: /* exp: tIDENTIFIER '(' aparameternode ')'  */
#line 93 "Parser.y"
      {(yyval.exp) = makeEXPfun((yyvsp[-3].stringconst),(yyvsp[-1].aparameternode));}
#line 1325 "Parser.tab.c"
    break;

  case 23: /* exp: tIDENTIFIER '(' ')'  */
#line 95 "Parser.y"
      {(yyval.exp) = makeEXPfun((yyvsp[-2].stringconst),NULL);}
#line 1331 "Parser.tab.c"
    break;

  case 24: /* exp: tUNKNOWN  */
#line 97 "Parser.y"
      {printf("unknown character %s at line: %d", tUNKNOWN.yylval, lineno);
       exit(1);}
#line 1338 "Parser.tab.c"
    break;

  case 25: /* stmt: "WHILE" '(' exp ')' stmtcompound  */
#line 102 "Parser.y"
       {(yyval.stmt) = makeSTMTwhile((yyvsp[-2].exp),(yyvsp[0].stmtcompound));}
#line 1344 "Parser.tab.c"
    break;

  case 26: /* stmt: "IF" '(' exp ')' stmtcompound "ELSE" stmtcompound  */
#line 104 "Parser.y"
       {(yyval.stmt) = makeSTMTifElse((yyvsp[-4].exp),(yyvsp[-2].stmtcompound),(yyvsp[0].stmtcompound));}
#line 1350 "Parser.tab.c"
    break;

  case 27: /* stmt: "IF" '(' exp ')' stmtcompound  */
#line 106 "Parser.y"
       {(yyval.stmt) = makeSTMTifElse((yyvsp[-2].exp),(yyvsp[0].stmtcompound),NULL);}
#line 1356 "Parser.tab.c"
    break;

  case 28: /* stmt: "RETURN" exp ';'  */
#line 108 "Parser.y"
       {(yyval.stmt) = makeSTMTreturn((yyvsp[-1].exp));}
#line 1362 "Parser.tab.c"
    break;

  case 29: /* stmt: "PRINT" exp ';'  */
#line 110 "Parser.y"
       {(yyval.stmt) = makeSTMTprint((yyvsp[-1].exp));}
#line 1368 "Parser.tab.c"
    break;

  case 30: /* stmt: type tIDENTIFIER ';'  */
#line 112 "Parser.y"
       {(yyval.stmt) = makeSTMTdecl((yyvsp[-2].stringconst),(yyvsp[-1].stringconst),NULL);}
#line 1374 "Parser.tab.c"
    break;

  case 31: /* stmt: type tIDENTIFIER '=' exp ';'  */
#line 114 "Parser.y"
       {(yyval.stmt) = makeSTMTdecl((yyvsp[-4].stringconst),(yyvsp[-3].stringconst),exp);}
#line 1380 "Parser.tab.c"
    break;

  case 32: /* stmt: tIDENTIFIER '=' exp ';'  */
#line 116 "Parser.y"
       {(yyval.stmt) = makeSTMTassign((yyvsp[-3].stringconst),(yyvsp[-1].exp));}
#line 1386 "Parser.tab.c"
    break;

  case 33: /* stmtcompound: '{' stmtnode '}'  */
#line 120 "Parser.y"
               {(yyval.stmtcompound) = (yyvsp[-1].stmtnode);}
#line 1392 "Parser.tab.c"
    break;

  case 34: /* stmtnode: stmt  */
#line 124 "Parser.y"
           {(yyval.stmtnode) = makeSTMTNODE((yyvsp[0].stmt),NULL);}
#line 1398 "Parser.tab.c"
    break;

  case 35: /* stmtnode: stmt stmtnode  */
#line 126 "Parser.y"
           {(yyval.stmtnode) = makeSTMTNODE((yyvsp[-1].stmt),(yyvsp[0].stmtnode));}
#line 1404 "Parser.tab.c"
    break;

  case 36: /* aparameter: tIDENTIFIER  */
#line 130 "Parser.y"
            {(yyval.aparameter) = makeAPARAMETERid((yyvsp[0].stringconst));}
#line 1410 "Parser.tab.c"
    break;

  case 37: /* aparameter: tCHAR  */
#line 132 "Parser.y"
            {(yyval.aparameter) = makeAPARAMETERchar((yyvsp[0].charconst));}
#line 1416 "Parser.tab.c"
    break;

  case 38: /* aparameter: tDOUBLE  */
#line 134 "Parser.y"
            {(yyval.aparameter) = makeAPARAMETERdouble((yyvsp[0].doubleconst));}
#line 1422 "Parser.tab.c"
    break;

  case 39: /* aparameter: tBOOLEAN  */
#line 136 "Parser.y"
            {(yyval.aparameter) = makeAPARAMETERbool((yyvsp[0].boolconst));}
#line 1428 "Parser.tab.c"
    break;

  case 40: /* aparameter: tINT  */
#line 138 "Parser.y"
            {(yyval.aparameter) = makeAPARAMETERint((yyvsp[0].intconst));}
#line 1434 "Parser.tab.c"
    break;

  case 41: /* aparameternode: aparameter  */
#line 142 "Parser.y"
                {(yyval.aparameternode) = makeAPARAMETERNODE((yyvsp[0].aparameter),NULL);}
#line 1440 "Parser.tab.c"
    break;

  case 42: /* aparameternode: aparameter ',' aparameternode  */
#line 144 "Parser.y"
                {(yyval.aparameternode) = makeAPARAMETERNODE((yyvsp[-2].aparameter),(yyvsp[0].aparameternode));}
#line 1446 "Parser.tab.c"
    break;

  case 43: /* fparameter: type tIDENTIFIER  */
#line 148 "Parser.y"
             {(yyval.fparameter) = makeFPARAMETER((yyvsp[-1].stringconst),(yyvsp[0].stringconst));}
#line 1452 "Parser.tab.c"
    break;

  case 44: /* fparameternode: fparameter  */
#line 152 "Parser.y"
                 {(yyval.fparameternode) = makeFPARAMETERNODE((yyvsp[0].fparameter),NULL);}
#line 1458 "Parser.tab.c"
    break;

  case 45: /* fparameternode: fparameter ',' fparameternode  */
#line 154 "Parser.y"
                 {(yyval.fparameternode) = makeFPARAMETERNODE((yyvsp[-2].fparameter),(yyvsp[0].fparameternode));}
#line 1464 "Parser.tab.c"
    break;

  case 46: /* function: type "FUNCTION" tIDENTIFIER '(' fparameternode ')' stmtcompound  */
#line 158 "Parser.y"
           {(yyval.function) = makeFUNCTION((yyvsp[-6].stringconst),(yyvsp[-4].stringconst),(yyvsp[-2].fparameternode),(yyvsp[0].stmtcompound));}
#line 1470 "Parser.tab.c"
    break;

  case 47: /* function: type "FUNCTION" tIDENTIFIER '(' ')' stmtcompound  */
#line 160 "Parser.y"
           {(yyval.function) = makeFUNCTION((yyvsp[-5].stringconst),(yyvsp[-3].stringconst),NULL,(yyvsp[0].stmtcompound));}
#line 1476 "Parser.tab.c"
    break;

  case 48: /* functionnode: function  */
#line 164 "Parser.y"
               {(yyval.functionnode) = makeFUNCTIONNODE((yyvsp[0].function),NULL);}
#line 1482 "Parser.tab.c"
    break;

  case 49: /* functionnode: function functionnode  */
#line 166 "Parser.y"
               {(yyval.functionnode) = makeFUNCTIONNODE((yyvsp[-1].function),(yyvsp[0].functionnode));}
#line 1488 "Parser.tab.c"
    break;

  case 50: /* type: "BOOLEAN"  */
#line 170 "Parser.y"
       {(yyval.stringconst) = (yyvsp[0].stringconst);}
#line 1494 "Parser.tab.c"
    break;

  case 51: /* type: "CHAR"  */
#line 172 "Parser.y"
       {(yyval.stringconst) = (yyvsp[0].stringconst);}
#line 1500 "Parser.tab.c"
    break;

  case 52: /* type: "DOUBLE"  */
#line 174 "Parser.y"
       {(yyval.stringconst) = (yyvsp[0].stringconst);}
#line 1506 "Parser.tab.c"
    break;

  case 53: /* type: "INT"  */
#line 176 "Parser.y"
       {(yyval.stringconst) = (yyvsp[0].stringconst);}
#line 1512 "Parser.tab.c"
    break;


#line 1516 "Parser.tab.c"

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
      yyerror (YY_("syntax error"));
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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 179 "Parser.y"
