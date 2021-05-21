#ifndef __DebugUtils_h
#define __DebugUtils_h
#include "Tree.h"
#include "IntermediateCodeGeneration.h"

void printEXP(EXP* exp);
void printIC(LL* iCode);
void printOP(OP* op);

void printTarget(Target* t);
void printARG(ARG* arg);
void printINS(INS* ins);




#endif