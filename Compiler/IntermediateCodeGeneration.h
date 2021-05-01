#ifndef __IntermediateCodeGeneration_h
#define __IntermediateCodeGeneration_h
#include "Tree.h"

typedef enum opKind {
    move,  //0
    push,
    pop,
    add,
    sub,
    mul,   //5
    divi,
    call,
    ret,
    cmp,
    jmp,   //10
    je,
    jne,
    jg,
    jge,
    jl,     //15
    jle,
    sete,
    setne,
    setg,
    setge,   //20
    setl,
    setle,
    xor,
    and,
    or,     //25
    meta,
    label,  //27
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
    PROGRAM_PROLOGUE,         //0
    PROGRAM_EPILOGUE,
    MAIN_CALLEE_SAVE,
    MAIN_CALLEE_RESTORE,
    FUNCTION_DECLARATION,
    CALLEE_PROLOGUE,          //5
    CALLEE_SAVE,
    CALLEE_RESTORE,
    CALLEE_EPILOGUE,
    CALLER_PROLOGUE,
    CALLER_EPILOGUE,          //10
    CALLER_SAVE,
    CALLER_RESTORE,
    CALL_PRINTF,
    ALLOCATE_STACK_SPACE,
    DEALLOCATE_STACK_SPACE,   //15
    REVERSE_PUSH_ARGUMENTS,
    FOLLOW_STATIC_LINK
} metaKind;

typedef enum labelKind {
    while_label,
    endwhile_label,
    if_label,
    endif_label,
    endelse_label,
    function_label,
    endfunction_label
} labelKind;

typedef struct Mode {
    addressingMode mode;
    int offset; //if mode is IRL, the offset is found here
} Mode;

typedef struct Target {
    targetKind targetK;
    opSize size;
    int additionalInfo;  //This is used to determine register number or immediate value
    labelKind labelK;    //This is relevant if target kind is label
    char* labelName;     //This is relevant if target kind is label
} Target;

typedef struct Operation {
    opKind opK;
    opSize size;
    metaKind metaK;      //This is only relevant if opKind is meta also
    int metaInformation; //This is only relevant if opkind is meta also
    char* metaString;    //This is only relevant if opkind is meta also
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
    int pFlagCHAR;
    int pFlagBOOLEAN;
    int pFlagINT;
    int pFlagDOUBLE;
} LL;

typedef struct LinkedListNodeFUN {
    FUNCTION* f;
    struct LinkedListNodeFUN* next;
} LLNFUN;

typedef struct LLFUN {
    LLNFUN* first;
    LLNFUN* last;
} LLFUN;

LL* icgTraversePROGRAM(PROGRAM* prog);
void icgTraverseSTMTCOMP(STMTCOMP* sc);
void icgTraverseSTMTNODE(STMTNODE* sn);
void icgTraverseSTMT(STMT* s);
void icgTraverseEXP(EXP* e);
void icgTraverseAPARAMETERNODE(APARAMETERNODE* apn);
void icgTraverseFUNCTION(FUNCTION* f);

void addToLL(LLN *moreCode);
void addToLLFUN(FUNCTION* f);

Mode* makeMode(addressingMode mode);
Mode* makeModeIRL(int offset);

Target* makeTarget(targetKind k, opSize s);
Target* makeTargetLabel(labelKind k, char* name);
Target* makeTargetReg(opSize size, int reg);
Target* makeTargetIMI(int imiValue);

OP* makeOP(opKind opK, opSize size);
OP* makeOPMeta(metaKind k, int metaInfo, char* metaLabel);

ARG* makeARG(Target* target, Mode* mode);
INS* makeINS(OP* op, ARG** args);
LLN* makeLLN(INS* ins);






//Quick Add Functions
void quickAddIns(INS* ins);
void quickAddMeta(metaKind kind);
void quickAddMetaWithInfo(metaKind kind, int metaInformation);
void quickAddMetaString(metaKind metaK, char* str);
void quickAddLabelString(labelKind kind, char* label);
void quickAddPush(opSize size, Target* target, Mode* mode);
void quickAddPushId(char* name);
void quickAddPopRRT(opSize size);
void quickAddPopReg(opSize size, int registerNumber);
void quickAddPop(Target* t, Mode* m);
void quickAddMoveRBPToRSL();
void quickAddMoveRSLToRBP();
void quickAddCheckTruthValue();
void quickAddJumpIfFalse(labelKind k, char* labelName);
void quickAddUnconditionalJmp(labelKind k, char* labelString);
void quickAddArithmeticINS(opKind k, opSize size);
void quickAddCompareINS(opKind k, opSize size);
void quickAddBooleanINS(opKind k);
void quickAddPushReg(int regNumber,opSize size);
void quickAddCallFun(char* funLabel);
void quickAddPushRSP();
void quickAddMoveRBPToRSP();
void quickAddPopRBP();
void quickAddPushRRT();


//Other
char* labelGenerator(labelKind kind);
opSize getSizeOfType(char* typeName);
opSize getSizeOfId(char* idName);
int getIntFromopSize(opSize size);


#endif

