%{
#include <stdio.h>
#include <stdlib.h>
extern char *yytext;
%}

%union {
   int intconst;
   char *stringconst;
   int boolconst;
   double doubleconst;
   char charconst;
   char unknown;
}

%token <stringconst> tIDENTIFIER
%token <intconst> tINTCONST
%token <doubleconst> tDOUBLECONST
%token <boolconst> tBOOLCONST
%token <charconst> tCHARCONST
%token <unknown> tUNKNOWN

%start exp

%left '+' '-'
%left '*' '/'
%left "L" "G" "LEQ" "GEQ" "EQ" "NEQ"
%left "OR"
%left "AND"

%type <exp> exp
%type <stmt> stmt
%type <stmtcompound> stmtcompound
%type <stmtnode> stmtnode
%type <variable> variable

%%
end : mainfunction
;

exp : tIDENTIFIER
      {$$ = makeEXPid($1);}
    | tINTCONST
      {$$ = makeEXPint($1);}
    | tDOUBLECONST
      {$$ = makeEXPint($1);}
    | tBOOLCONST
      {$$ = makeEXPint($1);}
    | tCHARCONST
      {$$ = makeEXPint($1);}
    | variable
      {$$ = makeEXPvar($1);}
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
 3+3; 2/4;
 modifyObject(o)

 modifyObject(object o) {
 	o.val
 	return;
 }

 exp;
int a;
variable;
exp;

variable : type tIDENTIFIER
	   {$$ = makeVARIABLE($1,$2);}
;

stmtcompound : '{' stmtnode '}'
	       {$$ = $2;}
;

stmtnode : stmt
	   {$$ = makeSTMTNODE($1,NULL);}
	 | stmt stmtnode
	   {$$ = makeSTMTNODE($1,$2);}
;

declaration : variable ';'
	    | type tIDENTIFIER '=' exp
	      { ;}

function : "FUNCTION" '(' ... ')' stmtcompound
         | "FUNCTION" '(' ... ')' stmt

parameterlist : type tIDENTIFIER
              |

parameter : type tIDENTIFIER
            {$$ = $}



type : "BOOLEAN"
       {$$ = $1;}
     | "CHAR"
       {$$ = $1;}
     | "DOUBLE"
       {$$ = $1;}
     | "INT"
       {$$ = $1;}
%%