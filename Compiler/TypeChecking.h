#ifndef __TypeChecking_h
#define __TypeChecking_h
#include "Tree.h"
typedef struct TYPE
{
    char* type;
    struct TYPE* up;
    struct TYPE* down;
} TYPE;

typedef struct OPERATION
{
    char* operator;
    int argc;
    TYPE* returnType;
    TYPE* argTypes[];
} OPERATION;

typedef struct OPERATION_WRAPPER
{
    int opCount;
    OPERATION* op;
} OPERATION_WRAPPER;


void typeChecking(PROGRAM* p);
void tcTraversePROGRAM(PROGRAM* prog);
void tcTraverseSTMTCOMP(STMTCOMP* sc);
void tcTraverseSTMTNODE(STMTNODE* sn);
void tcTraverseSTMT(STMT* s);
void tcTraverseFUNCTION(FUNCTION* f);
void tcTraverseEXP(EXP* e);
void tcTraverseAPARAMETERNODE(APARAMETERNODE* apn,FPARAMETERNODE* fpn);





#endif