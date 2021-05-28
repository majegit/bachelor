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
    PRINT = 262,                   /* PRINT  */
    RETURN = 263,                  /* RETURN  */
    WHILE = 264,                   /* WHILE  */
    IF = 265,                      /* IF  */
    ELSE = 266,                    /* ELSE  */
    L = 267,                       /* L  */
    G = 268,                       /* G  */
    LEQ = 269,                     /* LEQ  */
    GEQ = 270,                     /* GEQ  */
    EQ = 271,                      /* EQ  */
    NEQ = 272,                     /* NEQ  */
    OR = 273,                      /* OR  */
    AND = 274,                     /* AND  */
    BOOLEAN = 275,                 /* BOOLEAN  */
    CHAR = 276,                    /* CHAR  */
    DOUBLE = 277,                  /* DOUBLE  */
    INT = 278,                     /* INT  */
    ASSIGN = 279                   /* ASSIGN  */
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
#define PRINT 262
#define RETURN 263
#define WHILE 264
#define IF 265
#define ELSE 266
#define L 267
#define G 268
#define LEQ 269
#define GEQ 270
#define EQ 271
#define NEQ 272
#define OR 273
#define AND 274
#define BOOLEAN 275
#define CHAR 276
#define DOUBLE 277
#define INT 278
#define ASSIGN 279

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "Compiler\\Parser.y"

   int intconst;
   char* stringconst;
   int boolconst;
   double doubleconst;
   char charconst;
   char unknown;
   EXP* exp;
   FUNCTION* function;
   APARAMETER* aparameter;
   APARAMETERNODE* aparameternode;
   FPARAMETER* fparameter;
   FPARAMETERNODE* fparameternode;
   STMT* stmt;
   STMTNODE* stmtnode;
   STMTCOMP* stmtcomp;
   PROGRAM* program;

#line 134 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
