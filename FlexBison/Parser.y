%{
#include <stdio.h>

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

%token <intconst> tINTCONST
%token <stringconst> tIDENTIFIER
%token <boolconst> tBOOLCONST
%token <doubleconst> tDOUBLECONST
%token <charconst> tCHARCONST
%token <unknown> tUKNOWN

%start exp

%left '+' '-'
%left '*' '/'
%left '||'
%left '&&'

%%
exp :

%%