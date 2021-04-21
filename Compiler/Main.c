#include "Tree.h"
#include <stdio.h>
#include "SymbolCollection.h"
#include "TypeChecking.h"
#include "IntermediateCodeGeneration.h"
#include "DebugUtils.h"

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
    LL* iCode = icgTraversePROGRAM(program);
    printIC(iCode);
    printf("AFTER PRINT IC");
    printf("STARTING CODE EMIT\n");
    return 0;
}