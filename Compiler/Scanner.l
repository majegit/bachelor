/*** Definitions ***/
%{
    #include <string.h>
    #include "Compiler\Tree.h"
    #include "y.tab.h"
    extern int lineno;
%}


/*** Rule section ***/
%option noyywrap

%%
print               return PRINT;
return              return RETURN;
boolean             return BOOLEAN;
int                 return INT;
double              return DOUBLE;
char                return CHAR;
while               return WHILE;
if                  return IF;
else                return ELSE;
true|false          {
                        yylval.boolconst = strcmp(yytext, "true") == 0;
                        return tBOOLEAN;
                    }
[0-9]+              {
                        yylval.intconst = atoi(yytext);
                        return tINT;
                    }
[0-9]+\.[0-9]+      {
                        yylval.doubleconst = strtod(yytext, NULL);
                        return tDOUBLE;
                    }
[a-zA-Z][a-zA-Z0-9]* {
                        yylval.stringconst = (char*)malloc(strlen(yytext)+1);
                        sprintf(yylval.stringconst,"%s",yytext);
                        return tIDENTIFIER;
                    }
\'                  return '\'';
,                   return ',';
;                   return ';';
"("                 return '(';
")"                 return ')';
"{"                 return '{';
"}"                 return '}';
"+"                 return '+';
"-"                 return '-';
"*"                 return '*';
"/"                 return '/';
=                   return ASSIGN;
==                  return EQ;
!=                  return NEQ;
&&                  return AND;
\|\|                return OR;
\<                  return L;
\>                  return G;
\<=|=\<             return LEQ;
\>=|=\>             return GEQ;
\n                  lineno++;
[ \t]               ;
\#[^\n]*\n          ;
.                   printf("Unknown char: %s\n", yytext);

%%
