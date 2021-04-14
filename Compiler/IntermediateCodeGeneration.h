#ifndef __IntermediateCodeGeneration_h
#define __IntermediateCodeGeneration_h

typedef struct LinkedList {
    struct LinkedListNode* first;
    struct LinkedListNode* last;
} LL;

LL* icgTraversePROGRAM(PROGRAM* prog);
void icgTraverseSTMTCOMP(STMTCOMP* sc);
void icgTraverseSTMTNODE(STMTNODE* sn);
void icgTraverseSTMT(STMT* s);
void icgTraverseEXP(EXP* e);
void icgTraverseAPARAMETERNODE(APARAMETERNODE* apn);
void icgTraverseFUNCTIONNODE(FUNCTIONNODE* fn);
void icgTraverseFUNCTION(FUNCTION* f);
void icgTraverseFPARAMETERNODE(FPARAMETERNODE* fpn);

typedef struct LinkedListNode{
    enum {insK,labelK,funCallK,setBaseK,exitK,initK} kind;
    union {
        struct Instruction* ins;
    } val;
    struct LinkedListNode* next;
} LLN;

typedef struct Instruction {
    struct Operation* x;
} Instruction;

typedef struct Operation {
    enum {moveK,arithemeticK} kind;
    union {

    } val;
    int byteSizeModifier;
} Operation;

void addToLL(LL *currentCode, LLN *newCode);

void quickAddNode(const char* kind);

#endif

