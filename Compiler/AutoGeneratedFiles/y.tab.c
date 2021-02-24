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
#line 1 "Compiler\\Parser.y"

#include "Compiler\Tree.h"
#include <stdio.h>
#include <stdlib.h>
extern char *yytext;
extern int lineno;
extern PROGRAM* program;
void yyerror (char const *s) {
   printf ("yyerror triggered by: %s, lineno: %d\n", yytext,lineno);
}

#line 83 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    tIDENTIFIER = 258,             /* tIDENTIFIER  */
    tINT = 259,                    /* tINT  */
    tDOUBLE = 260,                 /* tDOUBLE  */
    tBOOLEAN = 261,                /* tBOOLEAN  */
    tCHAR = 262,                   /* tCHAR  */
    MAIN = 263,                    /* MAIN  */
    PRINT = 264,                   /* PRINT  */
    FUNC = 265,                    /* FUNC  */
    RETURN = 266,                  /* RETURN  */
    WHILE = 267,                   /* WHILE  */
    IF = 268,                      /* IF  */
    ELSE = 269,                    /* ELSE  */
    L = 270,                       /* L  */
    G = 271,                       /* G  */
    LEQ = 272,                     /* LEQ  */
    GEQ = 273,                     /* GEQ  */
    EQ = 274,                      /* EQ  */
    NEQ = 275,                     /* NEQ  */
    OR = 276,                      /* OR  */
    AND = 277,                     /* AND  */
    BOOLEAN = 278,                 /* BOOLEAN  */
    CHAR = 279,                    /* CHAR  */
    DOUBLE = 280,                  /* DOUBLE  */
    INT = 281,                     /* INT  */
    ASSIGN = 282                   /* ASSIGN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define tIDENTIFIER 258
#define tINT 259
#define tDOUBLE 260
#define tBOOLEAN 261
#define tCHAR 262
#define MAIN 263
#define PRINT 264
#define FUNC 265
#define RETURN 266
#define WHILE 267
#define IF 268
#define ELSE 269
#define L 270
#define G 271
#define LEQ 272
#define GEQ 273
#define EQ 274
#define NEQ 275
#define OR 276
#define AND 277
#define BOOLEAN 278
#define CHAR 279
#define DOUBLE 280
#define INT 281
#define ASSIGN 282

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 13 "Compiler\\Parser.y"

   int intconst;
   char* stringconst;
   int boolconst;
   double doubleconst;
   char charconst;
   char unknown;
   EXP* exp;
   FUNCTION* function;
   FUNCTIONNODE* functionnode;
   APARAMETER* aparameter;
   APARAMETERNODE* aparameternode;
   FPARAMETER* fparameter;
   FPARAMETERNODE* fparameternode;
   STMT* stmt;
   STMTNODE* stmtnode;
   PROGRAM* program;

#line 209 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
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
  YYSYMBOL_MAIN = 8,                       /* MAIN  */
  YYSYMBOL_PRINT = 9,                      /* PRINT  */
  YYSYMBOL_FUNC = 10,                      /* FUNC  */
  YYSYMBOL_RETURN = 11,                    /* RETURN  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_IF = 13,                        /* IF  */
  YYSYMBOL_ELSE = 14,                      /* ELSE  */
  YYSYMBOL_L = 15,                         /* L  */
  YYSYMBOL_G = 16,                         /* G  */
  YYSYMBOL_LEQ = 17,                       /* LEQ  */
  YYSYMBOL_GEQ = 18,                       /* GEQ  */
  YYSYMBOL_EQ = 19,                        /* EQ  */
  YYSYMBOL_NEQ = 20,                       /* NEQ  */
  YYSYMBOL_OR = 21,                        /* OR  */
  YYSYMBOL_AND = 22,                       /* AND  */
  YYSYMBOL_BOOLEAN = 23,                   /* BOOLEAN  */
  YYSYMBOL_CHAR = 24,                      /* CHAR  */
  YYSYMBOL_DOUBLE = 25,                    /* DOUBLE  */
  YYSYMBOL_INT = 26,                       /* INT  */
  YYSYMBOL_ASSIGN = 27,                    /* ASSIGN  */
  YYSYMBOL_28_ = 28,                       /* '+'  */
  YYSYMBOL_29_ = 29,                       /* '-'  */
  YYSYMBOL_30_ = 30,                       /* '*'  */
  YYSYMBOL_31_ = 31,                       /* '/'  */
  YYSYMBOL_32_ = 32,                       /* '('  */
  YYSYMBOL_33_ = 33,                       /* ')'  */
  YYSYMBOL_34_ = 34,                       /* ';'  */
  YYSYMBOL_35_ = 35,                       /* '{'  */
  YYSYMBOL_36_ = 36,                       /* '}'  */
  YYSYMBOL_37_ = 37,                       /* ','  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_program = 39,                   /* program  */
  YYSYMBOL_exp = 40,                       /* exp  */
  YYSYMBOL_stmt = 41,                      /* stmt  */
  YYSYMBOL_stmtcompound = 42,              /* stmtcompound  */
  YYSYMBOL_stmtnode = 43,                  /* stmtnode  */
  YYSYMBOL_aparameter = 44,                /* aparameter  */
  YYSYMBOL_aparameternode = 45,            /* aparameternode  */
  YYSYMBOL_fparameter = 46,                /* fparameter  */
  YYSYMBOL_fparameternode = 47,            /* fparameternode  */
  YYSYMBOL_function = 48,                  /* function  */
  YYSYMBOL_functionnode = 49,              /* functionnode  */
  YYSYMBOL_type = 50                       /* type  */
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
#define YYLAST   279

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  114

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
      32,    33,    30,    28,    37,    29,     2,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    34,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    60,    60,    63,    68,    70,    72,    74,    76,    78,
      80,    82,    84,    86,    88,    90,    92,    94,    96,    98,
     100,   102,   104,   106,   110,   112,   114,   116,   118,   120,
     122,   124,   126,   128,   130,   134,   138,   140,   144,   146,
     148,   150,   152,   156,   158,   162,   166,   168,   172,   174,
     178,   180,   184,   186,   188,   190
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
  "tDOUBLE", "tBOOLEAN", "tCHAR", "MAIN", "PRINT", "FUNC", "RETURN",
  "WHILE", "IF", "ELSE", "L", "G", "LEQ", "GEQ", "EQ", "NEQ", "OR", "AND",
  "BOOLEAN", "CHAR", "DOUBLE", "INT", "ASSIGN", "'+'", "'-'", "'*'", "'/'",
  "'('", "')'", "';'", "'{'", "'}'", "','", "$accept", "program", "exp",
  "stmt", "stmtcompound", "stmtnode", "aparameter", "aparameternode",
  "fparameter", "fparameternode", "function", "functionnode", "type", YY_NULLPTR
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
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,    43,    45,
      42,    47,    40,    41,    59,   123,   125,    44
};
#endif

#define YYPACT_NINF (-32)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       4,   -31,    21,    -1,   -32,     1,    51,    26,    30,    32,
      24,    24,    29,    41,   -32,   -32,   -32,   -32,    51,    46,
      16,    26,   -32,    73,    24,    24,    53,   -32,   -32,   -32,
     -32,    24,    50,    74,    24,    24,   -32,   -32,   -14,   -10,
     -32,    83,    94,   114,     0,   183,    24,    24,    24,    24,
      24,    24,    24,    24,    24,    24,    24,    24,   -32,   -32,
     202,   221,    24,   -32,    24,   -32,    56,   -32,   -32,   -32,
     -32,   -32,   -32,   -32,   -32,    60,    65,   -32,    13,    13,
      13,    13,    13,    13,    77,   -32,   240,   240,   257,   257,
       1,     1,   134,   154,   -15,   203,   -32,   -32,    86,   -32,
     -32,     1,    69,    84,   104,   -32,     1,   -32,    26,     1,
     -32,   -32,   -32,   -32
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     3,     0,     0,
       0,     0,     0,     0,    52,    53,    54,    55,    36,     0,
       0,    50,     2,     0,     0,     0,     4,     5,     6,     7,
       8,     0,     0,     0,     0,     0,    37,    35,     0,     0,
      51,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    28,    27,
       0,     0,     0,    29,     0,    32,     0,    31,    34,    38,
      42,    40,    41,    39,    23,    43,     0,     9,    14,    15,
      16,    17,    18,    19,    21,    20,    11,    10,    12,    13,
       0,     0,     0,     0,     0,     0,    22,    24,    26,    30,
      33,     0,    46,     0,     0,    44,     0,    49,     0,     0,
      45,    25,    47,    48
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -32,   -32,    -9,   -32,    88,   100,   -32,    25,   -32,    11,
     -32,   105,    -7
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    32,    18,     7,    19,    75,    76,   102,   103,
      21,    22,    20
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      23,     3,    33,    69,    70,    71,    72,    73,    14,    15,
      16,    17,     1,    62,    23,    42,    43,    64,   101,    38,
      63,     4,    45,    39,    65,    60,    61,    26,    27,    28,
      29,    30,     5,    74,    52,    53,     6,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    14,
      15,    16,    17,    92,     8,    93,    31,    24,     9,    25,
      10,    34,    11,    12,    13,    46,    47,    48,    49,    50,
      51,    52,    53,    35,    14,    15,    16,    17,    54,    55,
      56,    57,    37,    41,    58,    44,    66,   104,    94,    46,
      47,    48,    49,    50,    51,    52,    53,    95,    96,    53,
     106,   104,    54,    55,    56,    57,   108,   110,    59,    46,
      47,    48,    49,    50,    51,    52,    53,   109,    36,   112,
     105,     0,    54,    55,    56,    57,    40,     0,    67,    46,
      47,    48,    49,    50,    51,    52,    53,     0,     0,     0,
       0,     0,    54,    55,    56,    57,     0,     0,    68,    46,
      47,    48,    49,    50,    51,    52,    53,     0,     0,     0,
       0,     0,    54,    55,    56,    57,     0,     0,    99,    46,
      47,    48,    49,    50,    51,    52,    53,     0,    97,    98,
       0,     0,    54,    55,    56,    57,     0,     0,   100,   107,
       0,     0,     0,     0,   111,     0,     0,   113,    46,    47,
      48,    49,    50,    51,    52,    53,    69,    70,    71,    72,
      73,    54,    55,    56,    57,     0,    77,    46,    47,    48,
      49,    50,    51,    52,    53,     0,     0,     0,     0,     0,
      54,    55,    56,    57,     0,    90,    46,    47,    48,    49,
      50,    51,    52,    53,     0,     0,     0,     0,     0,    54,
      55,    56,    57,     0,    91,    46,    47,    48,    49,    50,
      51,    52,    53,     0,     0,     0,     0,     0,     0,     0,
      56,    57,    46,    47,    48,    49,    50,    51,    52,    53
};

static const yytype_int8 yycheck[] =
{
       7,    32,    11,     3,     4,     5,     6,     7,    23,    24,
      25,    26,     8,    27,    21,    24,    25,    27,    33,     3,
      34,     0,    31,     7,    34,    34,    35,     3,     4,     5,
       6,     7,    33,    33,    21,    22,    35,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    23,
      24,    25,    26,    62,     3,    64,    32,    27,     7,    27,
       9,    32,    11,    12,    13,    15,    16,    17,    18,    19,
      20,    21,    22,    32,    23,    24,    25,    26,    28,    29,
      30,    31,    36,    10,    34,    32,     3,    94,    32,    15,
      16,    17,    18,    19,    20,    21,    22,    37,    33,    22,
      14,   108,    28,    29,    30,    31,    37,     3,    34,    15,
      16,    17,    18,    19,    20,    21,    22,    33,    18,   108,
      95,    -1,    28,    29,    30,    31,    21,    -1,    34,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    28,    29,    30,    31,    -1,    -1,    34,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    28,    29,    30,    31,    -1,    -1,    34,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    90,    91,
      -1,    -1,    28,    29,    30,    31,    -1,    -1,    34,   101,
      -1,    -1,    -1,    -1,   106,    -1,    -1,   109,    15,    16,
      17,    18,    19,    20,    21,    22,     3,     4,     5,     6,
       7,    28,    29,    30,    31,    -1,    33,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,
      28,    29,    30,    31,    -1,    33,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,    28,
      29,    30,    31,    -1,    33,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    15,    16,    17,    18,    19,    20,    21,    22
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,    39,    32,     0,    33,    35,    42,     3,     7,
       9,    11,    12,    13,    23,    24,    25,    26,    41,    43,
      50,    48,    49,    50,    27,    27,     3,     4,     5,     6,
       7,    32,    40,    40,    32,    32,    43,    36,     3,     7,
      49,    10,    40,    40,    32,    40,    15,    16,    17,    18,
      19,    20,    21,    22,    28,    29,    30,    31,    34,    34,
      40,    40,    27,    34,    27,    34,     3,    34,    34,     3,
       4,     5,     6,     7,    33,    44,    45,    33,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      33,    33,    40,    40,    32,    37,    33,    42,    42,    34,
      34,    33,    46,    47,    50,    45,    14,    42,    37,    33,
       3,    42,    47,    42
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    39,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    41,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    41,    42,    43,    43,    44,    44,
      44,    44,    44,    45,    45,    46,    47,    47,    48,    48,
      49,    49,    50,    50,    50,    50
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     4,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     3,     5,     7,     5,     3,     3,     3,
       5,     4,     3,     5,     4,     3,     1,     2,     1,     1,
       1,     1,     1,     1,     3,     2,     1,     3,     7,     6,
       1,     2,     1,     1,     1,     1
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
  case 2: /* program: MAIN '(' ')' stmtcompound functionnode  */
#line 61 "Compiler\\Parser.y"
          {program = makePROGRAM((yyvsp[-1].stmtnode),(yyvsp[0].functionnode));
          printf("Great Success!");}
#line 1333 "y.tab.c"
    break;

  case 3: /* program: MAIN '(' ')' stmtcompound  */
#line 64 "Compiler\\Parser.y"
          {program = makePROGRAM((yyvsp[0].stmtnode),NULL);
           printf("Great Success!");}
#line 1340 "y.tab.c"
    break;

  case 4: /* exp: tIDENTIFIER  */
#line 69 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPid((yyvsp[0].stringconst));}
#line 1346 "y.tab.c"
    break;

  case 5: /* exp: tINT  */
#line 71 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPint((yyvsp[0].intconst));}
#line 1352 "y.tab.c"
    break;

  case 6: /* exp: tDOUBLE  */
#line 73 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPint((yyvsp[0].doubleconst));}
#line 1358 "y.tab.c"
    break;

  case 7: /* exp: tBOOLEAN  */
#line 75 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPint((yyvsp[0].boolconst));}
#line 1364 "y.tab.c"
    break;

  case 8: /* exp: tCHAR  */
#line 77 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPint((yyvsp[0].charconst));}
#line 1370 "y.tab.c"
    break;

  case 9: /* exp: '(' exp ')'  */
#line 79 "Compiler\\Parser.y"
      {(yyval.exp) = (yyvsp[-1].exp);}
#line 1376 "y.tab.c"
    break;

  case 10: /* exp: exp '-' exp  */
#line 81 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"-",(yyvsp[0].exp));}
#line 1382 "y.tab.c"
    break;

  case 11: /* exp: exp '+' exp  */
#line 83 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"+",(yyvsp[0].exp));}
#line 1388 "y.tab.c"
    break;

  case 12: /* exp: exp '*' exp  */
#line 85 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"*",(yyvsp[0].exp));}
#line 1394 "y.tab.c"
    break;

  case 13: /* exp: exp '/' exp  */
#line 87 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"/",(yyvsp[0].exp));}
#line 1400 "y.tab.c"
    break;

  case 14: /* exp: exp L exp  */
#line 89 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"L",(yyvsp[0].exp));}
#line 1406 "y.tab.c"
    break;

  case 15: /* exp: exp G exp  */
#line 91 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"G",(yyvsp[0].exp));}
#line 1412 "y.tab.c"
    break;

  case 16: /* exp: exp LEQ exp  */
#line 93 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"LEQ",(yyvsp[0].exp));}
#line 1418 "y.tab.c"
    break;

  case 17: /* exp: exp GEQ exp  */
#line 95 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"GEQ",(yyvsp[0].exp));}
#line 1424 "y.tab.c"
    break;

  case 18: /* exp: exp EQ exp  */
#line 97 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"EQ",(yyvsp[0].exp));}
#line 1430 "y.tab.c"
    break;

  case 19: /* exp: exp NEQ exp  */
#line 99 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"NEQ",(yyvsp[0].exp));}
#line 1436 "y.tab.c"
    break;

  case 20: /* exp: exp AND exp  */
#line 101 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"AND",(yyvsp[0].exp));}
#line 1442 "y.tab.c"
    break;

  case 21: /* exp: exp OR exp  */
#line 103 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"OR",(yyvsp[0].exp));}
#line 1448 "y.tab.c"
    break;

  case 22: /* exp: tIDENTIFIER '(' aparameternode ')'  */
#line 105 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPfun((yyvsp[-3].stringconst),(yyvsp[-1].aparameternode));}
#line 1454 "y.tab.c"
    break;

  case 23: /* exp: tIDENTIFIER '(' ')'  */
#line 107 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPfun((yyvsp[-2].stringconst),NULL);}
#line 1460 "y.tab.c"
    break;

  case 24: /* stmt: WHILE '(' exp ')' stmtcompound  */
#line 111 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTwhile((yyvsp[-2].exp),(yyvsp[0].stmtnode));}
#line 1466 "y.tab.c"
    break;

  case 25: /* stmt: IF '(' exp ')' stmtcompound ELSE stmtcompound  */
#line 113 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTifElse((yyvsp[-4].exp),(yyvsp[-2].stmtnode),(yyvsp[0].stmtnode));}
#line 1472 "y.tab.c"
    break;

  case 26: /* stmt: IF '(' exp ')' stmtcompound  */
#line 115 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTifElse((yyvsp[-2].exp),(yyvsp[0].stmtnode),NULL);}
#line 1478 "y.tab.c"
    break;

  case 27: /* stmt: RETURN exp ';'  */
#line 117 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTreturn((yyvsp[-1].exp));}
#line 1484 "y.tab.c"
    break;

  case 28: /* stmt: PRINT exp ';'  */
#line 119 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTprint((yyvsp[-1].exp));}
#line 1490 "y.tab.c"
    break;

  case 29: /* stmt: type tIDENTIFIER ';'  */
#line 121 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTdecl((yyvsp[-2].stringconst),(yyvsp[-1].stringconst),NULL);}
#line 1496 "y.tab.c"
    break;

  case 30: /* stmt: type tIDENTIFIER ASSIGN exp ';'  */
#line 123 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTdecl((yyvsp[-4].stringconst),(yyvsp[-3].stringconst),(yyvsp[-1].exp));}
#line 1502 "y.tab.c"
    break;

  case 31: /* stmt: tIDENTIFIER ASSIGN exp ';'  */
#line 125 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTassign((yyvsp[-3].stringconst),(yyvsp[-1].exp));}
#line 1508 "y.tab.c"
    break;

  case 32: /* stmt: type tCHAR ';'  */
#line 127 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTdecl((yyvsp[-2].stringconst),(yyvsp[-1].charconst),NULL);}
#line 1514 "y.tab.c"
    break;

  case 33: /* stmt: type tCHAR ASSIGN exp ';'  */
#line 129 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTdecl((yyvsp[-4].stringconst),(yyvsp[-3].charconst),(yyvsp[-1].exp));}
#line 1520 "y.tab.c"
    break;

  case 34: /* stmt: tCHAR ASSIGN exp ';'  */
#line 131 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTassign((yyvsp[-3].charconst),(yyvsp[-1].exp));}
#line 1526 "y.tab.c"
    break;

  case 35: /* stmtcompound: '{' stmtnode '}'  */
#line 135 "Compiler\\Parser.y"
               {(yyval.stmtnode) = (yyvsp[-1].stmtnode);}
#line 1532 "y.tab.c"
    break;

  case 36: /* stmtnode: stmt  */
#line 139 "Compiler\\Parser.y"
           {(yyval.stmtnode) = makeSTMTNODE((yyvsp[0].stmt),NULL);}
#line 1538 "y.tab.c"
    break;

  case 37: /* stmtnode: stmt stmtnode  */
#line 141 "Compiler\\Parser.y"
           {(yyval.stmtnode) = makeSTMTNODE((yyvsp[-1].stmt),(yyvsp[0].stmtnode));}
#line 1544 "y.tab.c"
    break;

  case 38: /* aparameter: tIDENTIFIER  */
#line 145 "Compiler\\Parser.y"
            {(yyval.aparameter) = makeAPARAMETERid((yyvsp[0].stringconst));}
#line 1550 "y.tab.c"
    break;

  case 39: /* aparameter: tCHAR  */
#line 147 "Compiler\\Parser.y"
            {(yyval.aparameter) = makeAPARAMETERchar((yyvsp[0].charconst));}
#line 1556 "y.tab.c"
    break;

  case 40: /* aparameter: tDOUBLE  */
#line 149 "Compiler\\Parser.y"
            {(yyval.aparameter) = makeAPARAMETERdouble((yyvsp[0].doubleconst));}
#line 1562 "y.tab.c"
    break;

  case 41: /* aparameter: tBOOLEAN  */
#line 151 "Compiler\\Parser.y"
            {(yyval.aparameter) = makeAPARAMETERbool((yyvsp[0].boolconst));}
#line 1568 "y.tab.c"
    break;

  case 42: /* aparameter: tINT  */
#line 153 "Compiler\\Parser.y"
            {(yyval.aparameter) = makeAPARAMETERint((yyvsp[0].intconst));}
#line 1574 "y.tab.c"
    break;

  case 43: /* aparameternode: aparameter  */
#line 157 "Compiler\\Parser.y"
                {(yyval.aparameternode) = makeAPARAMETERNODE((yyvsp[0].aparameter),NULL);}
#line 1580 "y.tab.c"
    break;

  case 44: /* aparameternode: aparameter ',' aparameternode  */
#line 159 "Compiler\\Parser.y"
                {(yyval.aparameternode) = makeAPARAMETERNODE((yyvsp[-2].aparameter),(yyvsp[0].aparameternode));}
#line 1586 "y.tab.c"
    break;

  case 45: /* fparameter: type tIDENTIFIER  */
#line 163 "Compiler\\Parser.y"
             {(yyval.fparameter) = makeFPARAMETER((yyvsp[-1].stringconst),(yyvsp[0].stringconst));}
#line 1592 "y.tab.c"
    break;

  case 46: /* fparameternode: fparameter  */
#line 167 "Compiler\\Parser.y"
                 {(yyval.fparameternode) = makeFPARAMETERNODE((yyvsp[0].fparameter),NULL);}
#line 1598 "y.tab.c"
    break;

  case 47: /* fparameternode: fparameter ',' fparameternode  */
#line 169 "Compiler\\Parser.y"
                 {(yyval.fparameternode) = makeFPARAMETERNODE((yyvsp[-2].fparameter),(yyvsp[0].fparameternode));}
#line 1604 "y.tab.c"
    break;

  case 48: /* function: type FUNC tIDENTIFIER '(' fparameternode ')' stmtcompound  */
#line 173 "Compiler\\Parser.y"
            {(yyval.function) = makeFUNCTION((yyvsp[-6].stringconst),(yyvsp[-4].stringconst),(yyvsp[-2].fparameternode),(yyvsp[0].stmtnode));}
#line 1610 "y.tab.c"
    break;

  case 49: /* function: type FUNC tIDENTIFIER '(' ')' stmtcompound  */
#line 175 "Compiler\\Parser.y"
            {(yyval.function) = makeFUNCTION((yyvsp[-5].stringconst),(yyvsp[-3].stringconst),NULL,(yyvsp[0].stmtnode));}
#line 1616 "y.tab.c"
    break;

  case 50: /* functionnode: function  */
#line 179 "Compiler\\Parser.y"
               {(yyval.functionnode) = makeFUNCTIONNODE((yyvsp[0].function),NULL);}
#line 1622 "y.tab.c"
    break;

  case 51: /* functionnode: function functionnode  */
#line 181 "Compiler\\Parser.y"
               {(yyval.functionnode) = makeFUNCTIONNODE((yyvsp[-1].function),(yyvsp[0].functionnode));}
#line 1628 "y.tab.c"
    break;

  case 52: /* type: BOOLEAN  */
#line 185 "Compiler\\Parser.y"
       {(yyval.stringconst) = "BOOLEAN";}
#line 1634 "y.tab.c"
    break;

  case 53: /* type: CHAR  */
#line 187 "Compiler\\Parser.y"
       {(yyval.stringconst) = "CHAR";}
#line 1640 "y.tab.c"
    break;

  case 54: /* type: DOUBLE  */
#line 189 "Compiler\\Parser.y"
       {(yyval.stringconst) = "DOUBLE";}
#line 1646 "y.tab.c"
    break;

  case 55: /* type: INT  */
#line 191 "Compiler\\Parser.y"
       {(yyval.stringconst) = "INT";}
#line 1652 "y.tab.c"
    break;


#line 1656 "y.tab.c"

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

#line 194 "Compiler\\Parser.y"
