#ifndef __Emit_h
#define __Emit_h

void emit(LL* code, const char* outputFileName);
char* convertInsToAsm(INS* ins);
void appendCode(char* newAsmCode);

char* convertMetaIns(INS* ins);

#endif


