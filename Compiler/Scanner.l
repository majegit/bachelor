/*** Definitions ***/
%{
    #include "Tree.h"
    #include "y.tab.h"
    extern int lineno;
%}


/*** Rule section ***/
%option noyywrap

%%
print               return "PRINT";
function            return "FUNCTION";
return              return "RETURN";
boolean             return "BOOLEAN";
int                 return "INT";
double              return "DOUBLE";
char                return "CHAR";
while               return "WHILE";
main                {printf("MAIN"); return "MAIN";}
if                  return "IF";
else                return "ELSE";
true|false          {
                        yylval.boolconst = yytext == "true";
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
[a-zA-Z]            {
                        yylval.charconst = yytext;
                        return tCHAR;
                    }
[a-zA-Z]+           {
                        yylval.stringconst = (char *)malloc(strlen(yytext)+1);
                        sprintf(yylval.stringconst,"%s",yytext);
                        return tIDENTIFIER;
                    }
,                   return ',';
;                   return ';';
(                   {printf("YOOO"); return '(';}
\                   return ')';
{                   return '{';
}                   return '}';
+                   return '+';
-                   return '-';
*                   return '*';
/                   return '/';
=                   return "ASSIGN";
==                  return "EQ";
!=                  return "NEQ";
&&                  return "AND";
\|\|                return "OR";
\<                  return "L";
\>                  return "G";
\<=|=\<             return "LEQ";
\>=|=\>             return "GEQ";
\n                  lineno++;
[ \t]               ;
.                   {
                        printf("WTF is this char");
                        yylval.unknown = yytext;
                        return tUNKNOWN;
                    }
%%
