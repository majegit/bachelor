#include <stdio.h>
#include "Tree.h"
#include "SymbolCollection.h"
#include "TypeChecking.h"
#include "IntermediateCodeGeneration.h"
#include "Peephole.h"
#include "DebugUtils.h"
#include "Emit.h"


int lineno = 1;
void yyparse();
PROGRAM* program;

int main()
{
    printf("STARTING SCANNING AND PARSING\n");
    yyparse();
    printf("STARTING SYMBOL COLLECTION\n");
    symbolCollection(program);
    printf("STARTING TYPECHECK\n");
    typeChecking(program);
    printf("STARTING INTERMEDIATE CODE GENERATION\n");
    LL* iCode = icgTraversePROGRAM(program);
    printf("STARTING PEEPHOLE OPTIMIZATION\n");
    peepholeOptimize(iCode);
    printf("STARTING CODE EMIT\n");
    emit(iCode,"asmCode.s");
    return 0;
}