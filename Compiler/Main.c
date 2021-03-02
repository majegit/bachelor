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
    printf("WTF");
    symbolCollection(program);
    printf("WTF\n");
    printf("%s",program->symbolTable->symbols->current->name);
    printf("%s",program->symbolTable->symbols->next->current->name);
    return 0;
}