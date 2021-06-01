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
    setb,  //used by doubles
    setbe, //used by doubles
    xor,    //25
    and,
    or,
    meta,
    label,
    dconst, //30
    cvtsi2sd
} opKind;

typedef enum opSuffix {
    bits_8,
    bits_32,
    bits_64,
    bits_64_d
} opSuffix;

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
    reg, //registers
} targetKind;

typedef enum metaKind {
    PROGRAM_PROLOGUE,           //0
    PROGRAM_EPILOGUE,
    MAIN_CALLEE_SAVE,
    MAIN_CALLEE_RESTORE,
    FUNCTION_DECLARATION,
    CALLEE_SAVE,                //5
    CALLEE_RESTORE,
    CALLEE_EPILOGUE,
    CALLER_SAVE,
    CALLER_RESTORE,
    ALLOCATE_STACK_SPACE,       //10
    DEALLOCATE_STACK_SPACE,
    FOLLOW_STATIC_LINK,
    DOUBLE_DECLARATION,         //13
} metaKind;

typedef enum labelKind {
    while_label,
    endwhile_label,
    if_label,
    endif_label,
    endelse_label,
    function_label,
    endfunction_label,
    double_label
} labelKind;

typedef struct Mode {
    addressingMode mode;
    int offset; //if mode is IRL, the offset is found here
} Mode;

typedef struct Target {
    targetKind targetK;
    int additionalInfo;  //This is used to determine register number or immediate value
    labelKind labelK;    //This is relevant if target kind is label
    char* labelName;     //This is relevant if target kind is label
} Target;

typedef struct Operation {
    opKind opK;
    opSuffix size;
    metaKind metaK;      //This is only relevant if opKind is meta also
    int metaInt;         //This is only relevant if opkind is meta also
    double metaDouble;   //This is only relevant if opkind is meta also
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

//For doubles
typedef struct LLND
{
    struct LLND* next;
    char* label;
    double val;
} LLND;

typedef struct LLD
{
    LLND* first;
    LLND* last;
} LLD;


LL* icgTraversePROGRAM(PROGRAM* prog);
void icgTraverseSTMTCOMP(STMTCOMP* sc);
void icgTraverseSTMTNODE(STMTNODE* sn);
void icgTraverseSTMT(STMT* s);
void icgTraverseEXP(EXP* e);
void icgTraverseAPARAMETERNODE(APARAMETERNODE* apn);
void icgTraverseFUNCTION(FUNCTION* f);

void addToLL(LLN* moreCode);
void addToLLFUN(FUNCTION* f);
void addToLLD(LLND* llnd);

Mode* makeMode(addressingMode mode);
Mode* makeModeIRL(int offset);

Target* makeTarget(targetKind k);
Target* makeTargetLabel(labelKind k, char* name);
Target* makeTargetReg(int reg);
Target* makeTargetIMI(int imiValue);
Target* makeTargetDouble(double doubleVal);

OP* makeOP(opKind opK, opSuffix size);
OP* makeOPMeta(metaKind k, int metaInfo, double metaDouble, char* metaLabel);

ARG* makeARG(Target* target, Mode* mode);
INS* makeINS(OP* op, ARG** args);
LLN* makeLLN(INS* ins);


//Quick Add Functions
void quickIns(INS* ins);
void quickMeta(metaKind kind);
void quickMetaWithInfo(metaKind kind, int metaInt);

void quickMetaString(metaKind metaK, char* str);
void quickLabelString(labelKind kind, char* label);
void quickPush(opSuffix size, Target* target, Mode* mode);
void quickPushId(SYMBOL* s);
void quickPopRRT(opSuffix size);
void quickPopReg(char* type, int registerNumber);
void quickMoveRBPToRSL();
void quickMoveRSLToRBP();
void quickCheckTruthValue();
void quickJumpIfFalse(labelKind k, char* labelName);
void quickUnconditionalJmp(labelKind k, char* labelString);
void quickArithmeticINS(opKind k, opSuffix size);
void quickCompareINS(opKind k, opSuffix size);
void quickBooleanINS(opKind k);
void quickPushReg(int regNumber,opSuffix size);
void quickCallFun(char* funLabel);
void quickPushRSP();
void quickMoveRBPToRSP();
void quickPopRBP();
void quickPushRBP();
void quickIncrementScopeOneLevel();
void quickPushRRT(opSuffix suffix);
void quickPushDoubleLabel(char* label);


//Other
char* labelGenerator(labelKind kind);
char* doubleLabelGenerator(double val);
opSuffix getSuffixOfType(char* typeName);
int getIntFromSuffix(opSuffix size);
int getSizeOfParameters(FPARAMETERNODE* fpn);
opKind translateCMPtoCMPSD(opKind kind);




#endif

