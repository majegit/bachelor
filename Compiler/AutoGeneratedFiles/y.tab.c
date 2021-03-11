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
int yylex();

#line 84 "y.tab.c"

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
    MAIN = 262,                    /* MAIN  */
    PRINT = 263,                   /* PRINT  */
    FUNC = 264,                    /* FUNC  */
    RETURN = 265,                  /* RETURN  */
    WHILE = 266,                   /* WHILE  */
    IF = 267,                      /* IF  */
    ELSE = 268,                    /* ELSE  */
    L = 269,                       /* L  */
    G = 270,                       /* G  */
    LEQ = 271,                     /* LEQ  */
    GEQ = 272,                     /* GEQ  */
    EQ = 273,                      /* EQ  */
    NEQ = 274,                     /* NEQ  */
    OR = 275,                      /* OR  */
    AND = 276,                     /* AND  */
    BOOLEAN = 277,                 /* BOOLEAN  */
    CHAR = 278,                    /* CHAR  */
    DOUBLE = 279,                  /* DOUBLE  */
    INT = 280,                     /* INT  */
    ASSIGN = 281                   /* ASSIGN  */
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
#define MAIN 262
#define PRINT 263
#define FUNC 264
#define RETURN 265
#define WHILE 266
#define IF 267
#define ELSE 268
#define L 269
#define G 270
#define LEQ 271
#define GEQ 272
#define EQ 273
#define NEQ 274
#define OR 275
#define AND 276
#define BOOLEAN 277
#define CHAR 278
#define DOUBLE 279
#define INT 280
#define ASSIGN 281

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "Compiler\\Parser.y"

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
   STMTCOMP* stmtcomp;
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
  YYSYMBOL_MAIN = 7,                       /* MAIN  */
  YYSYMBOL_PRINT = 8,                      /* PRINT  */
  YYSYMBOL_FUNC = 9,                       /* FUNC  */
  YYSYMBOL_RETURN = 10,                    /* RETURN  */
  YYSYMBOL_WHILE = 11,                     /* WHILE  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_L = 14,                         /* L  */
  YYSYMBOL_G = 15,                         /* G  */
  YYSYMBOL_LEQ = 16,                       /* LEQ  */
  YYSYMBOL_GEQ = 17,                       /* GEQ  */
  YYSYMBOL_EQ = 18,                        /* EQ  */
  YYSYMBOL_NEQ = 19,                       /* NEQ  */
  YYSYMBOL_OR = 20,                        /* OR  */
  YYSYMBOL_AND = 21,                       /* AND  */
  YYSYMBOL_BOOLEAN = 22,                   /* BOOLEAN  */
  YYSYMBOL_CHAR = 23,                      /* CHAR  */
  YYSYMBOL_DOUBLE = 24,                    /* DOUBLE  */
  YYSYMBOL_INT = 25,                       /* INT  */
  YYSYMBOL_ASSIGN = 26,                    /* ASSIGN  */
  YYSYMBOL_27_ = 27,                       /* '+'  */
  YYSYMBOL_28_ = 28,                       /* '-'  */
  YYSYMBOL_29_ = 29,                       /* '*'  */
  YYSYMBOL_30_ = 30,                       /* '/'  */
  YYSYMBOL_31_ = 31,                       /* '('  */
  YYSYMBOL_32_ = 32,                       /* ')'  */
  YYSYMBOL_33_ = 33,                       /* '\''  */
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
  YYSYMBOL_opt_aparameternode = 46,        /* opt_aparameternode  */
  YYSYMBOL_fparameter = 47,                /* fparameter  */
  YYSYMBOL_fparameternode = 48,            /* fparameternode  */
  YYSYMBOL_opt_fparameternode = 49,        /* opt_fparameternode  */
  YYSYMBOL_function = 50,                  /* function  */
  YYSYMBOL_functionnode = 51,              /* functionnode  */
  YYSYMBOL_opt_functionnode = 52,          /* opt_functionnode  */
  YYSYMBOL_type = 53                       /* type  */
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
#define YYLAST   285

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  107

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   281


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,    33,
      31,    32,    29,    27,    37,    28,     2,    30,     2,     2,
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
      25,    26
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    62,    62,    67,    69,    71,    73,    75,    77,    79,
      81,    83,    85,    87,    89,    91,    93,    95,    97,    99,
     101,   103,   107,   109,   111,   113,   115,   117,   119,   121,
     123,   128,   132,   134,   138,   142,   144,   149,   150,   154,
     158,   160,   165,   166,   170,   174,   176,   181,   182,   186,
     188,   190,   192
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
  "tDOUBLE", "tBOOLEAN", "MAIN", "PRINT", "FUNC", "RETURN", "WHILE", "IF",
  "ELSE", "L", "G", "LEQ", "GEQ", "EQ", "NEQ", "OR", "AND", "BOOLEAN",
  "CHAR", "DOUBLE", "INT", "ASSIGN", "'+'", "'-'", "'*'", "'/'", "'('",
  "')'", "'\\''", "';'", "'{'", "'}'", "','", "$accept", "program", "exp",
  "stmt", "stmtcompound", "stmtnode", "aparameter", "aparameternode",
  "opt_aparameternode", "fparameter", "fparameternode",
  "opt_fparameternode", "function", "functionnode", "opt_functionnode",
  "type", YY_NULLPTR
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
     275,   276,   277,   278,   279,   280,   281,    43,    45,    42,
      47,    40,    41,    39,    59,   123,   125,    44
};
#endif

#define YYPACT_NINF (-87)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -2,   -18,     9,   -17,   -87,   -12,    38,    33,   -20,   -87,
     -87,   -87,   -14,    48,    -4,    -3,   -87,   -87,   -87,   -87,
      48,    15,    70,    38,    11,    21,    33,   -87,   -87,    36,
      48,    48,    48,    28,    91,    48,    48,   154,    31,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,   -87,   -87,   -87,   -22,   -87,    62,   112,   230,    29,
     -87,    35,   173,   -87,   192,   211,   -87,   -87,   -13,   -13,
     -13,   -13,   -13,   -13,    47,   -87,   247,   247,   264,   264,
      48,   -87,    41,   -87,    48,   -87,    39,   -12,   -12,   133,
      33,   -87,   -87,   -87,    63,   -87,    40,   -87,    43,    75,
     -12,    33,   -12,   -87,   -87,   -87,   -87
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,    47,     3,     4,
       5,     6,     0,     0,     0,     0,    49,    50,    51,    52,
       0,     0,     0,    32,     0,     0,    45,    48,     2,     0,
       0,    37,     0,     3,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    30,    33,    31,     0,    46,     0,     0,    34,    35,
      38,     0,     0,    25,     0,     0,     8,     7,    13,    14,
      15,    16,    17,    18,    20,    19,    10,     9,    11,    12,
       0,    27,     0,    29,     0,    21,     0,     0,     0,     0,
      42,    36,    26,    22,    24,    28,    40,    43,     0,     0,
       0,     0,     0,    39,    23,    41,    44
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -87,   -87,   -10,   -87,   -86,    57,   -87,     8,   -87,   -87,
     -19,   -87,   -87,    67,   -87,    -7
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    22,    23,     7,    24,    59,    60,    61,    96,
      97,    98,    26,    27,    28,    25
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      29,    93,    94,    34,    80,     1,    30,    45,    46,     4,
      37,    31,    81,     3,   104,     5,   106,    32,    38,    29,
      57,    58,    62,     6,    54,    64,    65,    35,    36,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,     8,     9,    10,    11,    56,    12,    53,    13,    14,
      15,    33,     9,    10,    11,    16,    17,    18,    19,    31,
      16,    17,    18,    19,    67,    82,    84,    85,    46,    20,
      89,    21,    90,    92,    58,   102,   100,   101,   103,    20,
      52,    21,   105,    99,    39,    40,    41,    42,    43,    44,
      45,    46,    91,    55,    99,     0,     0,    47,    48,    49,
      50,     0,     0,     0,    51,    39,    40,    41,    42,    43,
      44,    45,    46,     0,     0,     0,     0,     0,    47,    48,
      49,    50,     0,     0,     0,    63,    39,    40,    41,    42,
      43,    44,    45,    46,     0,     0,     0,     0,     0,    47,
      48,    49,    50,     0,     0,     0,    83,    39,    40,    41,
      42,    43,    44,    45,    46,     0,     0,     0,     0,     0,
      47,    48,    49,    50,     0,     0,     0,    95,    39,    40,
      41,    42,    43,    44,    45,    46,     0,     0,     0,     0,
       0,    47,    48,    49,    50,     0,    66,    39,    40,    41,
      42,    43,    44,    45,    46,     0,     0,     0,     0,     0,
      47,    48,    49,    50,     0,    86,    39,    40,    41,    42,
      43,    44,    45,    46,     0,     0,     0,     0,     0,    47,
      48,    49,    50,     0,    87,    39,    40,    41,    42,    43,
      44,    45,    46,     0,     0,     0,     0,     0,    47,    48,
      49,    50,     0,    88,    39,    40,    41,    42,    43,    44,
      45,    46,     0,     0,     0,     0,     0,    47,    48,    49,
      50,    39,    40,    41,    42,    43,    44,    45,    46,     0,
       0,     0,     0,     0,     0,     0,    49,    50,    39,    40,
      41,    42,    43,    44,    45,    46
};

static const yytype_int8 yycheck[] =
{
       7,    87,    88,    13,    26,     7,    26,    20,    21,     0,
      20,    31,    34,    31,   100,    32,   102,    31,     3,    26,
      30,    31,    32,    35,     3,    35,    36,    31,    31,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,     3,     4,     5,     6,     9,     8,    36,    10,    11,
      12,     3,     4,     5,     6,    22,    23,    24,    25,    31,
      22,    23,    24,    25,    33,     3,    37,    32,    21,    31,
      80,    33,    31,    34,    84,    32,    13,    37,     3,    31,
      23,    33,   101,    90,    14,    15,    16,    17,    18,    19,
      20,    21,    84,    26,   101,    -1,    -1,    27,    28,    29,
      30,    -1,    -1,    -1,    34,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    -1,    -1,    -1,    -1,    27,    28,
      29,    30,    -1,    -1,    -1,    34,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    27,
      28,    29,    30,    -1,    -1,    -1,    34,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      27,    28,    29,    30,    -1,    -1,    -1,    34,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    27,    28,    29,    30,    -1,    32,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      27,    28,    29,    30,    -1,    32,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    27,
      28,    29,    30,    -1,    32,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    -1,    -1,    -1,    -1,    27,    28,
      29,    30,    -1,    32,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    27,    28,    29,
      30,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    14,    15,
      16,    17,    18,    19,    20,    21
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    39,    31,     0,    32,    35,    42,     3,     4,
       5,     6,     8,    10,    11,    12,    22,    23,    24,    25,
      31,    33,    40,    41,    43,    53,    50,    51,    52,    53,
      26,    31,    31,     3,    40,    31,    31,    40,     3,    14,
      15,    16,    17,    18,    19,    20,    21,    27,    28,    29,
      30,    34,    43,    36,     3,    51,     9,    40,    40,    44,
      45,    46,    40,    34,    40,    40,    32,    33,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      26,    34,     3,    34,    37,    32,    32,    32,    32,    40,
      31,    45,    34,    42,    42,    34,    47,    48,    49,    53,
      13,    37,    32,     3,    42,    48,    42
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    41,    41,    41,    41,    41,    41,    41,    41,
      41,    42,    43,    43,    44,    45,    45,    46,    46,    47,
      48,    48,    49,    49,    50,    51,    51,    52,    52,    53,
      53,    53,    53
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     5,     7,     5,     3,     5,     3,     5,     4,
       2,     3,     1,     2,     1,     1,     3,     0,     1,     2,
       1,     3,     0,     1,     7,     1,     2,     0,     1,     1,
       1,     1,     1
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
  case 2: /* program: MAIN '(' ')' stmtcompound opt_functionnode  */
#line 63 "Compiler\\Parser.y"
          {program = makePROGRAM((yyvsp[-1].stmtcomp),(yyvsp[0].functionnode));
          printf("Great Success!");}
#line 1337 "y.tab.c"
    break;

  case 3: /* exp: tIDENTIFIER  */
#line 68 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPid((yyvsp[0].stringconst));}
#line 1343 "y.tab.c"
    break;

  case 4: /* exp: tINT  */
#line 70 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPint((yyvsp[0].intconst));}
#line 1349 "y.tab.c"
    break;

  case 5: /* exp: tDOUBLE  */
#line 72 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPdouble((yyvsp[0].doubleconst));}
#line 1355 "y.tab.c"
    break;

  case 6: /* exp: tBOOLEAN  */
#line 74 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbool((yyvsp[0].boolconst));}
#line 1361 "y.tab.c"
    break;

  case 7: /* exp: '\'' tIDENTIFIER '\''  */
#line 76 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPchar(* (yyvsp[-1].stringconst));}
#line 1367 "y.tab.c"
    break;

  case 8: /* exp: '(' exp ')'  */
#line 78 "Compiler\\Parser.y"
      {(yyval.exp) = (yyvsp[-1].exp);}
#line 1373 "y.tab.c"
    break;

  case 9: /* exp: exp '-' exp  */
#line 80 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"-",(yyvsp[0].exp));}
#line 1379 "y.tab.c"
    break;

  case 10: /* exp: exp '+' exp  */
#line 82 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"+",(yyvsp[0].exp));}
#line 1385 "y.tab.c"
    break;

  case 11: /* exp: exp '*' exp  */
#line 84 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"*",(yyvsp[0].exp));}
#line 1391 "y.tab.c"
    break;

  case 12: /* exp: exp '/' exp  */
#line 86 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"/",(yyvsp[0].exp));}
#line 1397 "y.tab.c"
    break;

  case 13: /* exp: exp L exp  */
#line 88 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"L",(yyvsp[0].exp));}
#line 1403 "y.tab.c"
    break;

  case 14: /* exp: exp G exp  */
#line 90 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"G",(yyvsp[0].exp));}
#line 1409 "y.tab.c"
    break;

  case 15: /* exp: exp LEQ exp  */
#line 92 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"LEQ",(yyvsp[0].exp));}
#line 1415 "y.tab.c"
    break;

  case 16: /* exp: exp GEQ exp  */
#line 94 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"GEQ",(yyvsp[0].exp));}
#line 1421 "y.tab.c"
    break;

  case 17: /* exp: exp EQ exp  */
#line 96 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"EQ",(yyvsp[0].exp));}
#line 1427 "y.tab.c"
    break;

  case 18: /* exp: exp NEQ exp  */
#line 98 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"NEQ",(yyvsp[0].exp));}
#line 1433 "y.tab.c"
    break;

  case 19: /* exp: exp AND exp  */
#line 100 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"AND",(yyvsp[0].exp));}
#line 1439 "y.tab.c"
    break;

  case 20: /* exp: exp OR exp  */
#line 102 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPbinop((yyvsp[-2].exp),"OR",(yyvsp[0].exp));}
#line 1445 "y.tab.c"
    break;

  case 21: /* exp: tIDENTIFIER '(' opt_aparameternode ')'  */
#line 104 "Compiler\\Parser.y"
      {(yyval.exp) = makeEXPfun((yyvsp[-3].stringconst),(yyvsp[-1].aparameternode));}
#line 1451 "y.tab.c"
    break;

  case 22: /* stmt: WHILE '(' exp ')' stmtcompound  */
#line 108 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTwhile((yyvsp[-2].exp),(yyvsp[0].stmtcomp));}
#line 1457 "y.tab.c"
    break;

  case 23: /* stmt: IF '(' exp ')' stmtcompound ELSE stmtcompound  */
#line 110 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTifElse((yyvsp[-4].exp),(yyvsp[-2].stmtcomp),(yyvsp[0].stmtcomp));}
#line 1463 "y.tab.c"
    break;

  case 24: /* stmt: IF '(' exp ')' stmtcompound  */
#line 112 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTifElse((yyvsp[-2].exp),(yyvsp[0].stmtcomp),NULL);}
#line 1469 "y.tab.c"
    break;

  case 25: /* stmt: RETURN exp ';'  */
#line 114 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTreturn((yyvsp[-1].exp));}
#line 1475 "y.tab.c"
    break;

  case 26: /* stmt: PRINT '(' exp ')' ';'  */
#line 116 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTprint((yyvsp[-2].exp));}
#line 1481 "y.tab.c"
    break;

  case 27: /* stmt: type tIDENTIFIER ';'  */
#line 118 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTdecl((yyvsp[-2].stringconst),(yyvsp[-1].stringconst),NULL);}
#line 1487 "y.tab.c"
    break;

  case 28: /* stmt: type tIDENTIFIER ASSIGN exp ';'  */
#line 120 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTdecl((yyvsp[-4].stringconst),(yyvsp[-3].stringconst),(yyvsp[-1].exp));}
#line 1493 "y.tab.c"
    break;

  case 29: /* stmt: tIDENTIFIER ASSIGN exp ';'  */
#line 122 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTassign((yyvsp[-3].stringconst),(yyvsp[-1].exp));}
#line 1499 "y.tab.c"
    break;

  case 30: /* stmt: exp ';'  */
#line 124 "Compiler\\Parser.y"
       {(yyval.stmt) = makeSTMTexp((yyvsp[-1].exp));}
#line 1505 "y.tab.c"
    break;

  case 31: /* stmtcompound: '{' stmtnode '}'  */
#line 129 "Compiler\\Parser.y"
               {(yyval.stmtcomp) = makeSTMTCOMP((yyvsp[-1].stmtnode));}
#line 1511 "y.tab.c"
    break;

  case 32: /* stmtnode: stmt  */
#line 133 "Compiler\\Parser.y"
           {(yyval.stmtnode) = makeSTMTNODE((yyvsp[0].stmt),NULL);}
#line 1517 "y.tab.c"
    break;

  case 33: /* stmtnode: stmt stmtnode  */
#line 135 "Compiler\\Parser.y"
           {(yyval.stmtnode) = makeSTMTNODE((yyvsp[-1].stmt),(yyvsp[0].stmtnode));}
#line 1523 "y.tab.c"
    break;

  case 34: /* aparameter: exp  */
#line 139 "Compiler\\Parser.y"
             {(yyval.aparameter) = makeAPARAMETER((yyvsp[0].exp));}
#line 1529 "y.tab.c"
    break;

  case 35: /* aparameternode: aparameter  */
#line 143 "Compiler\\Parser.y"
                {(yyval.aparameternode) = makeAPARAMETERNODE((yyvsp[0].aparameter),NULL);}
#line 1535 "y.tab.c"
    break;

  case 36: /* aparameternode: aparameter ',' aparameternode  */
#line 145 "Compiler\\Parser.y"
                {(yyval.aparameternode) = makeAPARAMETERNODE((yyvsp[-2].aparameter),(yyvsp[0].aparameternode));}
#line 1541 "y.tab.c"
    break;

  case 37: /* opt_aparameternode: %empty  */
#line 149 "Compiler\\Parser.y"
                     {(yyval.aparameternode) = NULL;}
#line 1547 "y.tab.c"
    break;

  case 38: /* opt_aparameternode: aparameternode  */
#line 151 "Compiler\\Parser.y"
                     {(yyval.aparameternode) = (yyvsp[0].aparameternode);}
#line 1553 "y.tab.c"
    break;

  case 39: /* fparameter: type tIDENTIFIER  */
#line 155 "Compiler\\Parser.y"
             {(yyval.fparameter) = makeFPARAMETER((yyvsp[-1].stringconst),(yyvsp[0].stringconst));}
#line 1559 "y.tab.c"
    break;

  case 40: /* fparameternode: fparameter  */
#line 159 "Compiler\\Parser.y"
                 {(yyval.fparameternode) = makeFPARAMETERNODE((yyvsp[0].fparameter),NULL);}
#line 1565 "y.tab.c"
    break;

  case 41: /* fparameternode: fparameter ',' fparameternode  */
#line 161 "Compiler\\Parser.y"
                 {(yyval.fparameternode) = makeFPARAMETERNODE((yyvsp[-2].fparameter),(yyvsp[0].fparameternode));}
#line 1571 "y.tab.c"
    break;

  case 42: /* opt_fparameternode: %empty  */
#line 165 "Compiler\\Parser.y"
                     {(yyval.fparameternode) = NULL;}
#line 1577 "y.tab.c"
    break;

  case 43: /* opt_fparameternode: fparameternode  */
#line 167 "Compiler\\Parser.y"
                     {(yyval.fparameternode) = (yyvsp[0].fparameternode);}
#line 1583 "y.tab.c"
    break;

  case 44: /* function: type FUNC tIDENTIFIER '(' opt_fparameternode ')' stmtcompound  */
#line 171 "Compiler\\Parser.y"
           {(yyval.function) = makeFUNCTION((yyvsp[-6].stringconst),(yyvsp[-4].stringconst),(yyvsp[-2].fparameternode),(yyvsp[0].stmtcomp));}
#line 1589 "y.tab.c"
    break;

  case 45: /* functionnode: function  */
#line 175 "Compiler\\Parser.y"
               {(yyval.functionnode) = makeFUNCTIONNODE((yyvsp[0].function),NULL);}
#line 1595 "y.tab.c"
    break;

  case 46: /* functionnode: function functionnode  */
#line 177 "Compiler\\Parser.y"
               {(yyval.functionnode) = makeFUNCTIONNODE((yyvsp[-1].function),(yyvsp[0].functionnode));}
#line 1601 "y.tab.c"
    break;

  case 47: /* opt_functionnode: %empty  */
#line 181 "Compiler\\Parser.y"
                   {(yyval.functionnode) = NULL;}
#line 1607 "y.tab.c"
    break;

  case 48: /* opt_functionnode: functionnode  */
#line 183 "Compiler\\Parser.y"
                   {(yyval.functionnode) = (yyvsp[0].functionnode);}
#line 1613 "y.tab.c"
    break;

  case 49: /* type: BOOLEAN  */
#line 187 "Compiler\\Parser.y"
       {(yyval.stringconst) = "BOOLEAN";}
#line 1619 "y.tab.c"
    break;

  case 50: /* type: CHAR  */
#line 189 "Compiler\\Parser.y"
       {(yyval.stringconst) = "CHAR";}
#line 1625 "y.tab.c"
    break;

  case 51: /* type: DOUBLE  */
#line 191 "Compiler\\Parser.y"
       {(yyval.stringconst) = "DOUBLE";}
#line 1631 "y.tab.c"
    break;

  case 52: /* type: INT  */
#line 193 "Compiler\\Parser.y"
       {(yyval.stringconst) = "INT";}
#line 1637 "y.tab.c"
    break;


#line 1641 "y.tab.c"

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

#line 196 "Compiler\\Parser.y"
