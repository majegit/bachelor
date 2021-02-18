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
%type

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

stmt : exp ';'
     | stmt stmt

%%