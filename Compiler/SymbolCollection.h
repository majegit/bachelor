#ifndef __SymbolCollection_h
#define __SymbolCollection_h
#include "Tree.h"

void symbolCollection(PROGRAM* p);
void scTraversePROGRAM(PROGRAM* prog);
void scTraverseSTMTCOMP(STMTCOMP* sc, SYMBOLTABLE* st);
void scTraverseSTMTNODE(STMTNODE* sn, SYMBOLTABLE* st);
void scTraverseSTMT(STMT* s, SYMBOLTABLE* st);
void scTraverseFUNCTION(FUNCTION* f, SYMBOLTABLE* st);
void scTraverseFPARAMETERNODE(FPARAMETERNODE* fpn, SYMBOLTABLE* st);
void scTraverseGlobalSTMTNODE(STMTNODE* sn);
void scTraverseEXP(EXP* e, SYMBOLTABLE* st);

//This function checks if all branches of a function contains a return stmt
//Also used to find unreachable code
int allBranchesReturn(STMTNODE* sn);

#endif