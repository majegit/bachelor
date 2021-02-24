/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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

#line 140 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
