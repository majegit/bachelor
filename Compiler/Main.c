#include <stdio.h>
#include "Tree.h"
#include "SymbolCollection.h"
#include "TypeChecking.h"
#include "IntermediateCodeGeneration.h"
#include "Peephole.h"
#include "Emit.h"


int lineno = 1;
void yyparse();
PROGRAM* program;

int main()
{
    yyparse();
    printf("here");
    symbolCollection(program);
    printf("here2");
    typeChecking(program);
    LL* iCode = icgTraversePROGRAM(program);
    printf("here1");
    peepholeOptimize(iCode);
    printf("here");
    emit(iCode,"asmCode.s");

    return 0;
}
