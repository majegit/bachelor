%{
#include <stdio.h>
#include <stdlib.h>
extern char *yytext;
%}

%union {
   int intconst;
   char* stringconst;
   int boolconst;
   double doubleconst;
   char charconst;
   char unknown;
   PROGRAM* program;
}

%token <stringconst> tIDENTIFIER
%token <intconst> tINT
%token <doubleconst> tDOUBLE
%token <boolconst> tBOOLEAN
%token <charconst> tCHAR
%token <unknown> tUNKNOWN

%start program

%left '+' '-'
%left '*' '/'
%left "L" "G" "LEQ" "GEQ" "EQ" "NEQ"
%left "OR"
%left "AND"

%type <stringconst> '-' '+'
%type <program> program
%type <exp> exp
%type <stmt> stmt
%type <stmtcompound> stmtcompound
%type <stmtnode> stmtnode
%type <aparameter> aparameter
%type <aparameternode> aparameternode
%type <fparameter> fparameter
%type <fparameternode> fparameternode
%type <function> function
%type <functionnode> functionnode
%type <type> type

%%
program : "MAIN" '(' ')' stmtcompound functionnode
          {$$ = makePROGRAM($4,$5);
          printf("Great Success!");}
;

exp : tIDENTIFIER
      {$$ = makeEXPid($1);}
    | type tIDENTIFIER
      {$$ = makeEXPvar($1,$2);}
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
      {$$ = makeEXPbinop($1,$2,$3);}
    | exp '+' exp
      {$$ = makeEXPbinop($1,$2,$3);}
    | exp '*' exp
      {$$ = makeEXPbinop($1,$2,$3);}
    | exp '/' exp
      {$$ = makeEXPbinop($1,$2,$3);}
    | exp "L" exp
      {$$ = makeEXPbinop($1,$2,$3);}
    | exp "G" exp
      {$$ = makeEXPbinop($1,$2,$3);}
    | exp "LEQ" exp
      {$$ = makeEXPbinop($1,$2,$3);}
    | exp "GEQ" exp
      {$$ = makeEXPbinop($1,$2,$3);}
    | exp "EQ" exp
      {$$ = makeEXPbinop($1,$2,$3);}
    | exp "NEQ" exp
      {$$ = makeEXPbinop($1,$2,$3);}
    | exp "AND" exp
      {$$ = makeEXPbinop($1,$2,$3);}
    | exp "OR" exp
      {$$ = makeEXPbinop($1,$2,$3);}
    | tIDENTIFIER '(' aparameternode ')'
      {$$ = makeEXPfun($1,$3);}
    | tIDENTIFIER '(' ')'
      {$$ = makeEXPfun($1,NULL);}
    | tUNKNOWN
      {printf("unknown character %s at line: %d", tUNKNOWN.yylval, lineno);
       exit(1);}
;

stmt : "WHILE" exp stmtcompound
       {$$ = makeSTMTwhile($2,$3);}
     | "WHILE" exp stmt
       {$$ = makeSTMTwhile($2,makeSTMTNODE($3));}
     | "IF" exp stmtcompound "ELSE" stmtcompound
       {$$ = makeSTMTifElse($2,$3,$5);}
     | "IF" exp stmt "ELSE" stmtcompound
       {$$ = makeSTMTifElse($2,$3,$5);}
     | "IF" exp stmtcompound "ELSE" stmt
       {$$ = makeSTMTifElse($2,$3,makeSTMTNODE($5));}
     | "IF" exp stmt "ELSE" stmt
       {$$ = makeSTMTifElse($2,makeSTMTNODE($3),makeSTMTNODE($5));}
     | exp '=' exp
       {$$ = makeSTMTassign($1,$3);}
     | exp ';'
       {  }
     | "RETURN" exp
       {$$ = makeSTMTreturn($2);}
     | "PRINT" exp
       {$$ = makeSTMTprint($2);}
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
	      | aparameter aparameternode
	      	{$$ = makeAPARAMETERNODE($1,$2);}
;

fparameter : type tIDENTIFIER
	     {$$ = makeFPARAMETER($1,$2);}
;

fparameternode : fparameter
                 {$$ = makeFPARAMETERNODE($1,NULL);}
	       | fparameter fparameternode
	         {$$ = makeFPARAMETERNODE($1,$2);}
;

function : type "FUNCTION" tIDENTIFIER '(' fparameternode ')' stmtcompound
	   {$$ = makeFUNCTION($1,$3,$5,$7);}
	 | type "FUNCTION" tIDENTIFIER '(' ')' stmtcompound
	   {$$ = makeFUNCTION($1,$3,NULL,$6);}
;

functionnode : function
	       {$$ = makeFUNCTIONNODE($1,NULL);}
	     | function functionnode
	       {$$ = makeFUNCTIONNODE($1,$2);}
;

type : "BOOLEAN"
       {$$ = $1;}
     | "CHAR"
       {$$ = $1;}
     | "DOUBLE"
       {$$ = $1;}
     | "INT"
       {$$ = $1;}
;

%%