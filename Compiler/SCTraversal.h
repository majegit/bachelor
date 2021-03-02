#ifndef __SCTraversal_h
#define __SCTraversal_h
#include "Tree.h"

void symbolCollection(PROGRAM* p);
void scTraversePROGRAM(PROGRAM* prog);
void scTraverseSTMTCOMP(STMTCOMP* sc, SYMBOLTABLE* st);
void scTraverseSTMTNODE(STMTNODE* sn, SYMBOLTABLE* st);
void scTraverseSTMT(STMT* s, SYMBOLTABLE* st);
//void scTraverseEXP(EXP* e, SYMBOLTABLE* st);
//void scTraverseAPARAMETERNODE(APARAMETERNODE* apn, SYMBOLTABLE* st);
void scTraverseFUNCTIONNODE(FUNCTIONNODE* fn, SYMBOLTABLE* st);
void scTraverseFUNCTION(FUNCTION* f, SYMBOLTABLE* st);
void scTraverseFPARAMETERNODE(FPARAMETERNODE* fpn, SYMBOLTABLE* st);

#endif