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

    printf("STARTING SCANNING AND PARSING\n");
    yyparse();
    symbolCollection(program);
    printf("STARTING TYPECHECK\n");
    typeChecking(program);
    printf("STARTING INTERMEDIATE CODE GENERATION\n");
    LL* iCode = icgTraversePROGRAM(program);
    printIC(iCode);
    printf("STARTING CODE EMIT\n");
    return 0;
}