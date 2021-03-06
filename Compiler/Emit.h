#ifndef __Emit_h
#define __Emit_h
#include "IntermediateCodeGeneration.h"

extern FILE* fp;
extern const char* indentation;

void emit(LL* code, const char* outputFileName);
char* convertInsToAsm(INS* ins);

void fputMeta(INS* ins);
void fputARG(ARG* a, opSuffix suffix);
void fputTarget(Target* t, opSuffix suffix);
void putLongsFromDouble(double val);

const char* printCHAR;
const char* printBOOLEAN;
const char* printINT;
const char* printDOUBLE;
const char* printNewline;

#endif


