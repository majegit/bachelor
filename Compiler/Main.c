#include <stdio.h>
#include <string.h>
#include "Tree.h"
#include "SymbolCollection.h"
#include "TypeChecking.h"
/*
#include "IntermediateCodeGeneration.h"
#include "DebugUtils.h"
#include "Emit.h"
 */

int lineno;
void yyparse();
PROGRAM* program;

int main()
{
    lineno = 1;

    printf("STARTING SCANNING AND PARSING\n");
    yyparse();
    printf("STARTING SYMBOL COLLECTION\n");
    symbolCollection(program);
    printf("STARTING TYPECHECK\n");
    typeChecking(program);
    //printf("STARTING INTERMEDIATE CODE GENERATION\n");
    //LL* iCode = icgTraversePROGRAM(program);
    //printIC(iCode);
    /*
    printf("STARTING CODE EMIT\n");
    emit(iCode,"test.s");
     */

    return 0;
}