%{
#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
extern char *yytext;
extern int lineno;
extern PROGRAM* program;
void yyerror (char const *s) {
   printf ("yyerror triggered by: %s, lineno: %d\n", yytext,lineno);
}
%}

%union {
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
}

%token <stringconst> tIDENTIFIER
%token <intconst> tINT
%token <doubleconst> tDOUBLE
%token <boolconst> tBOOLEAN
%token <charconst> tCHAR
%token MAIN PRINT FUNC RETURN WHILE IF ELSE L G LEQ GEQ EQ NEQ OR AND BOOLEAN CHAR DOUBLE INT ASSIGN

%start program

%left '+' '-'
%left '*' '/'
%left L G LEQ GEQ EQ NEQ
%left OR
%left AND

%type <stringconst> type
%type <program> program
%type <exp> exp
%type <stmt> stmt
%type <stmtnode> stmtcompound stmtnode
%type <aparameter> aparameter
%type <aparameternode> aparameternode
%type <fparameter> fparameter
%type <fparameternode> fparameternode
%type <function> function
%type <functionnode> functionnode

%%
program : MAIN '(' ')' stmtcompound functionnode
          {program = makePROGRAM($4,$5);
          printf("Great Success!");}
        | MAIN '(' ')' stmtcompound
          {program = makePROGRAM($4,NULL);
           printf("Great Success!");}
;

exp : tIDENTIFIER
      {$$ = makeEXPid($1);}
    | tINT
      {$$ = makeEXPint($1);}
    | tDOUBLE
      {$$ = makeEXPint($1);}
    | tBOOLEAN
      {$$ = makeEXPint($1);}
    | tCHAR
      {$$ = makeEXPint($1);}
    | '(' exp ')'
      {$$ = $2;}
    | exp '-' exp
      {$$ = makeEXPbinop($1,"-",$3);}
    | exp '+' exp
      {$$ = makeEXPbinop($1,"+",$3);}
    | exp '*' exp
      {$$ = makeEXPbinop($1,"*",$3);}
    | exp '/' exp
      {$$ = makeEXPbinop($1,"/",$3);}
    | exp L exp
      {$$ = makeEXPbinop($1,"L",$3);}
    | exp G exp
      {$$ = makeEXPbinop($1,"G",$3);}
    | exp LEQ exp
      {$$ = makeEXPbinop($1,"LEQ",$3);}
    | exp GEQ exp
      {$$ = makeEXPbinop($1,"GEQ",$3);}
    | exp EQ exp
      {$$ = makeEXPbinop($1,"EQ",$3);}
    | exp NEQ exp
      {$$ = makeEXPbinop($1,"NEQ",$3);}
    | exp AND exp
      {$$ = makeEXPbinop($1,"AND",$3);}
    | exp OR exp
      {$$ = makeEXPbinop($1,"OR",$3);}
    | tIDENTIFIER '(' aparameternode ')'
      {$$ = makeEXPfun($1,$3);}
    | tIDENTIFIER '(' ')'
      {$$ = makeEXPfun($1,NULL);}
;

stmt : WHILE '(' exp ')' stmtcompound
       {$$ = makeSTMTwhile($3,$5);}
     | IF '(' exp ')' stmtcompound ELSE stmtcompound
       {$$ = makeSTMTifElse($3,$5,$7);}
     | IF '(' exp ')' stmtcompound
       {$$ = makeSTMTifElse($3,$5,NULL);}
     | RETURN exp ';'
       {$$ = makeSTMTreturn($2);}
     | PRINT exp ';'
       {$$ = makeSTMTprint($2);}
     | type tIDENTIFIER ';'
       {$$ = makeSTMTdecl($1,$2,NULL);}
     | type tIDENTIFIER ASSIGN exp ';'
       {$$ = makeSTMTdecl($1,$2,$4);}
     | tIDENTIFIER ASSIGN exp ';'
       {$$ = makeSTMTassign($1,$3);}
     | type tCHAR ';'
       {$$ = makeSTMTdecl($1,$2,NULL);}
     | type tCHAR ASSIGN exp ';'
       {$$ = makeSTMTdecl($1,$2,$4);}
     | tCHAR ASSIGN exp ';'
       {$$ = makeSTMTassign($1,$3);}
;

stmtcompound : '{' stmtnode '}'
	       {$$ = $2;}
;

stmtnode : stmt
	   {$$ = makeSTMTNODE($1,NULL);}
	 | stmt stmtnode
	   {$$ = makeSTMTNODE($1,$2);}
;

aparameter : tIDENTIFIER
	    {$$ = makeAPARAMETERid($1);}
	  | tCHAR
	    {$$ = makeAPARAMETERchar($1);}
	  | tDOUBLE
	    {$$ = makeAPARAMETERdouble($1);}
	  | tBOOLEAN
	    {$$ = makeAPARAMETERbool($1);}
	  | tINT
	    {$$ = makeAPARAMETERint($1);}
;

aparameternode : aparameter
		{$$ = makeAPARAMETERNODE($1,NULL);}
	      | aparameter ',' aparameternode
	      	{$$ = makeAPARAMETERNODE($1,$3);}
;

fparameter : type tIDENTIFIER
	     {$$ = makeFPARAMETER($1,$2);}
;

fparameternode : fparameter
                 {$$ = makeFPARAMETERNODE($1,NULL);}
	       | fparameter ',' fparameternode
	         {$$ = makeFPARAMETERNODE($1,$3);}
;

function : type FUNC tIDENTIFIER '(' fparameternode ')' stmtcompound
	    {$$ = makeFUNCTION($1,$3,$5,$7);}
	  | type FUNC tIDENTIFIER '(' ')' stmtcompound
	    {$$ = makeFUNCTION($1,$3,NULL,$6);}
;

functionnode : function
	       {$$ = makeFUNCTIONNODE($1,NULL);}
	     | function functionnode
	       {$$ = makeFUNCTIONNODE($1,$2);}
;

type : BOOLEAN
       {$$ = "BOOLEAN";}
     | CHAR
       {$$ = "CHAR";}
     | DOUBLE
       {$$ = "DOUBLE";}
     | INT
       {$$ = "INT";}
;

%%