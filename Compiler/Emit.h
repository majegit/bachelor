#ifndef __Emit_h
#define __Emit_h
#include "IntermediateCodeGeneration.h"

void emit(LL* code, const char* outputFileName);
char* convertInsToAsm(INS* ins);

char* convertMetaIns(INS* ins);
char* meta_function_declaration(INS* ins);
char* convertTarget(Target* t, opSize size);

#endif


