#ifndef __TypeChecking_h
#define __TypeChecking_h
#include "Tree.h"
typedef struct TYPESYSTEM
{
    struct SUBTYPE* group[3];
} TYPESYSTEM;

typedef struct SUBTYPE
{
    char* type;
    struct SUBTYPE* up;
    struct SUBTYPE* down;
} SUBTYPE;

typedef struct OPERATION
{
    char* operator;
    int argc;
    char* returnType;
    char* argTypes[];
} OPERATION;

void tcTraversePROGRAM(PROGRAM* prog);
void tcTraverseSTMTCOMP(STMTCOMP* sc);
void tcTraverseSTMTNODE(STMTNODE* sn);
void tcTraverseSTMT(STMT* s);
void tcTraverseFUNCTIONNODE(FUNCTIONNODE* fn);
void tcTraverseFUNCTION(FUNCTION* f);
void tcTraverseFPARAMETERNODE(FPARAMETERNODE* fpn);
void tcTraverseEXP(EXP* e);
void tcTraverseAPARAMETERNODE(APARAMETERNODE* apn);





#endif