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
    symbolCollection(program);
    typeChecking(program);
    LL* iCode = icgTraversePROGRAM(program);
    peepholeOptimize(iCode);
    emit(iCode,"asmCode.s");

    return 0;
}
