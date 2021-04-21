#ifndef __IntermediateCodeGeneration_h
#define __IntermediateCodeGeneration_h

typedef enum opKind {
    move,
    push,
    pop,
    add,
    sub,
    mul,
    divi,
    call,
    ret,
    cmp,
    je,
    jne,
    jg,
    jge,
    jl,
    jle,
    meta,
    label,
    dconst
} opKind;

typedef enum opSize {
    bits_8,
    bits_32,
    bits_64
} opSize;

typedef enum addressingMode {
    dir, //Direct:                     X
    ind, //Indirect:                  (X)
    irl  //Indirect Relative:   offset(X)
} addressingMode;

typedef enum targetKind {
    imi, //Immediate Integer
    mem, //Label
    rbp, //Base pointer        rbp
    rsp, //Stack pointer
    rrt, //Return register
    rsl, //Register for static link computation
    reg  //Other registers
} targetKind;

typedef enum metaKind {
    PROGRAM_PROLOGUE,
    PROGRAM_EPILOGUE,
    MAIN_CALLEE_SAVE,
    MAIN_CALLEE_RESTORE,
    CALLEE_PROLOGUE,
    CALLEE_EPILOGUE,
    CALLEE_SAVE,
    CALLEE_RESTORE,
    CALLER_PROLOGUE,
    CALLER_EPILOGUE,
    CALLER_SAVE,
    CALLER_RESTORE,
    CALL_PRINTF,
    ALLOCATE_STACK_SPACE,
    DEALLOCATE_STACK_SPACE,
    REVERSE_PUSH_ARGUMENTS,
    FOLLOW_STATIC_LINK
} metaKind;

typedef enum labelKind {
    while_label,
    endwhile_label,
    if_label,
    endif_label,
    else_label
} labelKind;

typedef struct Mode {
    addressingMode mode;
    int offset;
} Mode;

typedef struct Target {
    targetKind targetK;
    labelKind labelK;
    int additionalInfo;
} Target;

typedef struct Operation {
    opKind opK;
    metaKind metaK; //This is only relevant if opKind is meta also
    opSize size; //For some operations this is relevant
} OP;

typedef struct Argument {
    Target* target;
    Mode* mode;
} ARG;

typedef struct Instruction {
    OP* op;
    ARG* args[2];
} INS;

typedef struct LinkedListNode {
    INS* ins;
    struct LinkedListNode* next;
} LLN;

typedef struct LinkedList {
    LLN* first;
    LLN* last;
} LL;

LL* code;
LL* icgTraversePROGRAM(PROGRAM* prog);
void icgTraverseSTMTCOMP(STMTCOMP* sc);
void icgTraverseSTMTNODE(STMTNODE* sn);
void icgTraverseSTMT(STMT* s);
void icgTraverseEXP(EXP* e);
void icgTraverseAPARAMETERNODE(APARAMETERNODE* apn);
void icgTraverseFUNCTIONNODE(FUNCTIONNODE* fn);
void icgTraverseFUNCTION(FUNCTION* f);
void icgTraverseFPARAMETERNODE(FPARAMETERNODE* fpn);

void addToLL(LLN *moreCode);
Mode* makeMode(addressingMode mode, int offset);
Target* makeTarget(targetKind targetK, labelKind labelK, int additionalInfo);
OP* makeOP(opKind opK, metaKind metaK, opSize size);
ARG* makeARG(Target* target, Mode* mode);
INS* makeINS(OP* op, ARG** args);
LLN* makeLLN(INS* ins);

void quickAddIns(INS* ins);
void quickAddMeta(metaKind kind);
void quickAddLabel(labelKind kind, int labelNumber);
void quickAddPush(Mode* mode, Target* target);
void quickAddPushId(char* name);
void quickAddPopRRT();
void quickAddMoveRBPToRSL();

int labelGenerator(labelKind kind);
opSize getSizeOfType(char* typeName);
opSize getSizeOfId(char* idName);


#endif

