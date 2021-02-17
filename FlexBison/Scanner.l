/*** Definitions ***/
%{

%}


/*** Rule section ***/
%option noyywrap
%%
print               {printf("PRINT");}
function            {printf("FUNCTION");}
return              {printf("RETURN");}
boolean             {printf("BOOLEAN");}
int                 {printf("INT");}
double              {printf("DOUBLE");}
char                {printf("CHAR");}
true|false          {printf("BOOLEAN: %s", yytext);}
[0-9]+              {printf("INT: %s", yytext);}
[0-9]+\.[0-9]+      {printf("DOUBLE: %s", yytext);}
[a-zA-Z]            {printf("CHAR: %s", yytext);}
\;                  {printf(";");}
\(                  {printf("(");}
\)                  {printf(")");}
\{                  {printf("{");}
\}                  {printf("}");}
[a-zA-Z]+           {printf("IDENTIFIER: %s", yytext);}
\+                  {printf("ADDS");}
\-                  {printf("SUBTRACTS");}
\*                  {printf("MULTIPLIES");}
\/                  {printf("DIVISION");}
==                  {printf("EQUALS");}
=                   {printf("ASSIGN");}
&&                  {printf("AND");}
\|\|                {printf("OR");}
\<                  {printf("<");}
\>                  {printf(">");}
\<=                 {printf("<=");}
\>=                 {printf(">=");}
\n                  {printf("\n");}
[ \t]               {printf(" ");}
.     {printf("%s Unknown\n", yytext);}
%%

/*** Code section ***/
int main(int argc, char **argv){
    yylex();

    return 0;
}