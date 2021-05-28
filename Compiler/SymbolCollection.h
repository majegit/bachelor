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
void scTraverseEXP(EXP* e, SYMBOLTABLE* st);
void scTraverseAPARAMETERNODE(APARAMETERNODE* apn, SYMBOLTABLE* st);

void scTraverseSTMTCOMP2(STMTCOMP* sc, SYMBOLTABLE* st);
void scTraverseSTMTNODE2(STMTNODE* sn, SYMBOLTABLE* st);
void scTraverseSTMT2(STMT* s, SYMBOLTABLE* st);
void scTraverseFUNCTION2(FUNCTION* f, SYMBOLTABLE* st);
void scTraverseEXP2(EXP* e, SYMBOLTABLE* st);
void scTraverseAPARAMETERNODE2(APARAMETERNODE* apn, SYMBOLTABLE* st);



#endif