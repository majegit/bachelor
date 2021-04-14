#include "Tree.h"
#include <stdio.h>
#include "SymbolCollection.h"
#include "TypeChecking.h"
//#include "IntermediateCodeGeneration.h"

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
    printf("STARTING TYPECHECK\n");
    typeChecking(program);
    printf("STARTING INTERMEDIATE CODE GENERATION\n");
    //LL* code = icgTraversePROGRAM(program);
    printf("STARTING CODE EMIT\n");
    return 0;
}