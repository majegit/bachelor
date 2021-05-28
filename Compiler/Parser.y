%{
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
	#include "Compiler\Tree.h"
#else
	#include "Tree.h"
#endif

extern char *yytext;
extern int lineno;
extern PROGRAM* program;
void yyerror (char const *s) {
   printf ("yyerror triggered by: %s, lineno: %d\n", yytext,lineno);
}
int yylex();
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
   APARAMETER* aparameter;
   APARAMETERNODE* aparameternode;
   FPARAMETER* fparameter;
   FPARAMETERNODE* fparameternode;
   STMT* stmt;
   STMTNODE* stmtnode;
   STMTCOMP* stmtcomp;
   PROGRAM* program;
}

%token <stringconst> tIDENTIFIER
%token <intconst> tINT
%token <doubleconst> tDOUBLE
%token <boolconst> tBOOLEAN
%token PRINT RETURN WHILE IF ELSE L G LEQ GEQ EQ NEQ OR AND BOOLEAN CHAR DOUBLE INT ASSIGN

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
%type <stmtnode> stmtnode syntactic_sugar
%type <stmtcomp> stmtcompound
%type <aparameter> aparameter
%type <aparameternode> aparameternode opt_aparameternode
%type <fparameter> fparameter
%type <fparameternode> fparameternode opt_fparameternode
%type <function> functionDecl

%%
program : stmtnode
          {program = makePROGRAM($1);}
;

exp : tIDENTIFIER
      {$$ = makeEXPid($1);}
    | '-' tIDENTIFIER
      {$$ = makeEXPUnaryMinusId($2);}
    | tINT
      {$$ = makeEXPint($1);}
    | '-' tINT
      {$$ = makeEXPint($2*-1);}
    | tDOUBLE
      {$$ = makeEXPdouble($1);}
    | '-' tDOUBLE
      {$$ = makeEXPdouble($2*-1);}
    | tBOOLEAN
      {$$ = makeEXPbool($1);}
    | '\'' tIDENTIFIER '\''
      {$$ = makeEXPchar(* $2);}
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
    | tIDENTIFIER '(' opt_aparameternode ')'
      {$$ = makeEXPfun($1,$3);}
;

stmt : WHILE '(' exp ')' stmtcompound
       {$$ = makeSTMTwhile($3,$5);}
     | IF '(' exp ')' stmtcompound ELSE stmtcompound
       {$$ = makeSTMTifElse($3,$5,$7);}
     | IF '(' exp ')' stmtcompound
       {$$ = makeSTMTifElse($3,$5,NULL);}
     | RETURN exp ';'
       {$$ = makeSTMTreturn($2);}
     | PRINT '(' exp ')' ';'
       {$$ = makeSTMTprint($3);}
     | tIDENTIFIER ASSIGN exp ';'
       {$$ = makeSTMTassign($1,$3);}
     | type tIDENTIFIER ';'
       {$$ = makeSTMTvarDecl($1,$2);}
     | functionDecl
       {$$ = makeSTMTfunDecl($1);}
     | exp ';'
       {$$ = makeSTMTexp($1);}
;

stmtcompound : '{' stmtnode '}'
	       {$$ = makeSTMTCOMP($2);}
;

/*
stmt_or_stmtcompound : stmtcompound
		       {$$ = $1;}
		     | stmt
		       {STMTNODE* stmtnode = makeSTMTNODE($1, NULL);
		        $$ = makeSTMTCOMP(stmtnode);}
		        */

syntactic_sugar : type tIDENTIFIER ASSIGN exp ';'
                  {STMT* stmt1 = makeSTMTvarDecl($1,$2);
                   STMT* stmt2 = makeSTMTassign($2,$4);
                   STMTNODE* stmtnode1 = makeSTMTNODE(stmt1,NULL);
                   STMTNODE* stmtnode2 = makeSTMTNODE(stmt2,NULL);
                   stmtnode1->next = stmtnode2;
                   $$ = stmtnode1;}
;

stmtnode : stmt
	   {$$ = makeSTMTNODE($1,NULL);}
	 | stmt stmtnode
	   {$$ = makeSTMTNODE($1,$2);}
	 | syntactic_sugar
	   {$$ = $1;}
	 | syntactic_sugar stmtnode
	   {STMTNODE* curr = $1;
	    while(curr->next != NULL)
	    	curr = curr->next;
	    curr->next = $2;
	    $$ = $1;}
;



aparameter : exp
	     {$$ = makeAPARAMETER($1);}
;

aparameternode : aparameter
		{$$ = makeAPARAMETERNODE($1,NULL);}
	      | aparameter ',' aparameternode
	      	{$$ = makeAPARAMETERNODE($1,$3);}
;

opt_aparameternode :
		     {$$ = NULL;}
		   | aparameternode
		     {$$ = $1;}
;

fparameter : type tIDENTIFIER
	     {$$ = makeFPARAMETER($1,$2);}
;

fparameternode : fparameter
                 {$$ = makeFPARAMETERNODE(NULL,$1);}
	       | fparameternode ',' fparameter
	         {$$ = makeFPARAMETERNODE($1,$3);}
;

opt_fparameternode :
                     {$$ = NULL;}
                   | fparameternode
                     {$$ = $1;}
;

functionDecl : type tIDENTIFIER '(' opt_fparameternode ')' stmtcompound
	   {$$ = makeFUNCTION($1,$2,$4,$6);}
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
