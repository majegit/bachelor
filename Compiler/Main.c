#include "Tree.h"
#include <stdio.h>

int lineno;
void yyparse();
PROGRAM* program;

int main()
{
    lineno = 1;
    printf("STARTING!\n");
    yyparse();
    return 0;
}