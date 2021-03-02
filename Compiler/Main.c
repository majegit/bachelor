#include "Tree.h"
#include <stdio.h>
#include "SCTraversal.h"

int lineno;
void yyparse();
PROGRAM* program;

int main()
{
    lineno = 1;

    printf("STARTING!\n");
    yyparse();
    printf("\n");
    symbolCollection(program);
    return 0;
}