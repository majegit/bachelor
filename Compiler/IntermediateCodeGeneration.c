#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"
#include "IntermediateCodeGeneration.h"

SYMBOLTABLE* currentScope;


LL* code;

LL* icgTraversePROGRAM(PROGRAM* prog)
{
    code = (LL*)malloc(sizeof(LL));
    code->first = NULL;

    quickAddMeta(PROGRAM_PROLOGUE);
    icgTraverseSTMTCOMP(prog->body);
    quickAddMeta(PROGRAM_EPILOGUE);
    icgTraverseFUNCTIONNODE(prog->fn);
    return code;
}

void icgTraverseSTMTCOMP(STMTCOMP* sc)
{
    currentScope = sc->symbolTable;
    quickAddMeta(ALLOCATE_STACK_SPACE); //When entering new scope, rbp is pushed and local variables are given space on the stack
    code->last->ins->op->metaInformation = sc->symbolTable->nextLabel; //How much space is allocated is specified here
    icgTraverseSTMTNODE(sc->stmtnode);
    currentScope = sc->symbolTable->par;
}


void icgTraverseSTMTNODE(STMTNODE* sn)
{
    if(sn == NULL)
        return;
    icgTraverseSTMT(sn->stmt);
    icgTraverseSTMTNODE(sn->next);
}

void icgTraverseSTMT(STMT* s)
{
    printf("stmt kind: %d\n",s->kind);
    switch(s->kind)
    {
        case whileK:
            {
                int labelNumber = labelGenerator(while_label);     //Generate int X
                quickAddLabel(while_label, labelNumber);           //while_X:
                icgTraverseEXP(s->val.whileS.guard);                    //Guard
                quickAddPopRRT();                                       //Move boolean to rrt
                quickAddCheckTruthValue();                              //cmp rrt, $1
                quickAddJumpIfFalse(endwhile_label,labelNumber);     //jne endwhile_X
                icgTraverseSTMTCOMP(s->val.whileS.body);                //generate the code for the body of the whileloop
                quickAddLabel(endwhile_label, labelNumber);        //endwhile_X:
            }
            break;
        case assignK:
            {
                icgTraverseEXP(s->val.assignS.val);
                quickAddPopRRT();
                quickAddMoveRBPToRSL();
                int* staticLinkJumpsAndOffset = staticLinkCount(s->val.assignS.name,currentScope);
                for(int i=0; i < staticLinkJumpsAndOffset[0]; i++)
                    quickAddMeta(FOLLOW_STATIC_LINK);
                Mode* modeDIR = makeMode(dir,0);
                Mode* modeIRL = makeMode(irl,staticLinkJumpsAndOffset[1]);

                Target* from = makeTarget(rrt,0,0);
                Target* to = makeTarget(rsl,0,0);

                ARG* argFrom = makeARG(from,modeDIR);
                ARG* argTo = makeARG(to,modeIRL);
                ARG* args[2] = {argFrom, argTo};

                OP* op = makeOP(move,0,getSizeOfId(s->val.assignS.name));
                INS* ins = makeINS(op,args);
                quickAddIns(ins);

                free(staticLinkJumpsAndOffset);
                free(staticLinkJumpsAndOffset+1);
            }
            break;
        case ifElseK:
            {
                int labelNumber = labelGenerator(if_label);        //Generate int X

                quickAddLabel(if_label, labelNumber);              //if_X:
                icgTraverseEXP(s->val.ifElseS.cond);                    //Guard
                quickAddPopRRT();                                       //Move boolean to rrt
                quickAddCheckTruthValue();                              //cmp rrt, $1
                quickAddJumpIfFalse(endif_label,labelNumber);        //jne endif_X
                icgTraverseSTMTCOMP(s->val.ifElseS.ifbody);             //if-body
                quickAddUnconditionalJmp(endelse_label,labelNumber); //jmp endelse_X
                quickAddLabel(endif_label, labelNumber);           //endif_X:
                icgTraverseSTMTCOMP(s->val.ifElseS.elsebody);           //else-body
                quickAddLabel(endelse_label,labelNumber);          //endelse_X:
            }
            break;
        case returnK:
            icgTraverseEXP(s->val.returnS);
            quickAddPopRRT();
            quickAddMeta(CALLEE_RESTORE);
            quickAddMeta(CALLEE_EPILOGUE);
            break;
        case printK:
            icgTraverseEXP(s->val.printS);  //TODO: IMPLEMENT
            break;
        case declK:
            {
                if(s->val.declS.value == NULL)
                    break;
                icgTraverseEXP(s->val.declS.value);
                quickAddPopRRT();
                int* staticLinkJumpsAndOffset = staticLinkCount(s->val.declS.name,currentScope);
                for(int i=0; i < staticLinkJumpsAndOffset[0]; i++)
                    quickAddMeta(FOLLOW_STATIC_LINK);

                Mode* modeDIR = makeMode(dir,0);
                Mode* modeIRL = makeMode(irl,staticLinkJumpsAndOffset[1]);

                Target* from = makeTarget(rrt,0,0);
                Target* to = makeTarget(rsl,0,0);

                ARG* argFrom = makeARG(from,modeDIR);
                ARG* argTo = makeARG(to,modeIRL);
                ARG* args[2] = {argFrom, argTo};

                OP* op = makeOP(move,0,getSizeOfId(s->val.declS.name));
                INS* ins = makeINS(op,args);
                quickAddIns(ins);

                free(staticLinkJumpsAndOffset);
                free(staticLinkJumpsAndOffset+1);
            }
            break;
        case expK:
            icgTraverseEXP(s->val.expS);
            break;
    }
}

void icgTraverseEXP(EXP* e)
{
    switch(e->kind)
    {
        case idK:
            quickAddPushId(e->val.idE);
            break;
        case intK:
            {
                OP* op = makeOP(push,0,0);
                Target* target = makeTarget(imi,0,e->val.intE);
                ARG* arg = makeARG(target,makeMode(dir,0));
                ARG* args[2] = {arg, NULL};
                quickAddIns(makeINS(op, args));
            }
            break;
        case doubleK:
            //Generate double constant
            break;
        case boolK:
            {
                OP* op = makeOP(push, 0, 0);
                Target* target = makeTarget(imi, 0, e->val.boolE);
                ARG* arg = makeARG(target, makeMode(dir, 0));
                ARG* args[2] = {arg, NULL};
                quickAddIns(makeINS(op, args));
            }
            break;
        case charK:
            {
                OP* op = makeOP(push, 0, 0);
                Target* target = makeTarget(imi, 0, e->val.charE);
                ARG* arg = makeARG(target, makeMode(dir, 0));
                ARG* args[2] = {arg, NULL};
                quickAddIns(makeINS(op, args));
            }
            break;
        case binopK:
            icgTraverseEXP(e->val.binopE.left);
            icgTraverseEXP(e->val.binopE.right);
            char* op = e->val.binopE.operator;
            if(strcmp(op,"-") == 0)
                quickAddArithmeticINS(sub,getSizeOfType(e->type));
            else if (strcmp(op,"+") == 0)
                quickAddArithmeticINS(add,getSizeOfType(e->type));
            else if (strcmp(op,"*") == 0)
                quickAddArithmeticINS(mul,getSizeOfType(e->type));
            else if (strcmp(op,"/") == 0)
                quickAddArithmeticINS(divi,getSizeOfType(e->type));
            else if (strcmp(op,"L") == 0)
                quickAddCompareINS("L");
            else if (strcmp(op,"G") == 0)
                quickAddCompareINS("G");
            else if (strcmp(op,"LEQ") == 0)
                quickAddCompareINS("LEQ");
            else if (strcmp(op,"GEQ") == 0)
                quickAddCompareINS("GEQ");
            else if (strcmp(op,"EQ") == 0)
                quickAddCompareINS("EQ");
            else if (strcmp(op,"NEQ") == 0)
                quickAddCompareINS("NEQ");
            else if (strcmp(op,"AND") == 0)
                quickAddBooleanINS("AND");
            else if (strcmp(op,"OR") == 0)
                quickAddBooleanINS("OR");
            quickAddPushReg(1);
            break;
        case funK:
            //TODO: Generate the code for each parameter and throw it on the stack
            icgTraverseAPARAMETERNODE(e->val.funE.aparameternode);
            break;
    }
    if(e->coerceTo != NULL)
    {
        //TODO: pop into reg 1, do the coercion, and push back onto stack
    }
}

void icgTraverseAPARAMETERNODE(APARAMETERNODE* apn)
{
    if(apn == NULL)
        return;
    icgTraverseEXP(apn->current->exp);
    icgTraverseAPARAMETERNODE(apn->next);
}

void icgTraverseFUNCTIONNODE(FUNCTIONNODE* fn)
{
    if(fn == NULL)
        return;
    icgTraverseFUNCTION(fn->current);
    icgTraverseFUNCTIONNODE(fn->next);
}

void icgTraverseFUNCTION(FUNCTION* f)
{
    icgTraverseFPARAMETERNODE(f->args);
    icgTraverseSTMTCOMP(f->body);
}

void icgTraverseFPARAMETERNODE(FPARAMETERNODE* fpn)
{
    if(fpn == NULL)
        return;
    icgTraverseFPARAMETERNODE(fpn->next);
}

void addToLL(LLN* newCode)
{
    if(code->first == NULL) //First time we insert something
    {
        code->first = newCode;
        code->last = newCode;
    }
    else
    {
        code->last->next = newCode;
        code->last = newCode;
    }
}


Mode* makeMode(addressingMode addressingMode, int offset) {
    Mode* mode = (Mode*)malloc(sizeof(Mode));
    mode->mode = addressingMode;
    mode->offset = offset;
    return mode;
}

Target* makeTarget(targetKind targetK, labelKind labelK, int regNumber)
{
    Target* target = (Target*)malloc(sizeof(Target));
    target->targetK = targetK;
    target->labelK = labelK;
    target->additionalInfo = regNumber;
    return target;
}

OP* makeOP(opKind opK, metaKind metaK, opSize size)
{
    OP* op = (OP*)malloc(sizeof(OP));
    op->opK = opK;
    op->metaK = metaK;
    op->size = size;
    return op;
}

ARG* makeARG(Target* target, Mode* mode)
{
    ARG* arg = (ARG*)malloc(sizeof(ARG));
    arg->target = target;
    arg->mode = mode;
    return arg;
}

INS* makeINS(OP* op, ARG** args)
{
    INS* ins = (INS*)malloc(sizeof(INS));
    ins->op = op;
    ins->args[0] = args[0];
    ins->args[1] = args[1];
    return ins;
}

LLN* makeLLN(INS* ins)
{
    LLN* node = (LLN*)malloc(sizeof(LLN));
    node->ins = ins;
    node->next = NULL;
    return node;
}

void quickAddIns(INS* ins)
{
    LLN* node = makeLLN(ins);
    addToLL(node);
}

void quickAddMeta(metaKind metaK) {
    static int quickAddMeta = 0;
    OP* op = makeOP(meta,metaK,0);
    ARG* args[2] = {NULL,NULL};
    INS* ins = makeINS(op,args);
    quickAddIns(ins);
};

void quickAddLabel(labelKind kind, int labelNumber)
{
    Target* target = makeTarget(mem,kind,labelNumber);
    Mode* mode = makeMode(dir,0);
    ARG* arg = makeARG(target, mode);
    OP* op = makeOP(label,0,0);
    ARG* args[2] = {arg, NULL};
    quickAddIns(makeINS(op,args));
};

void quickAddPush(Mode* mode, Target* target)
{
    OP* op = makeOP(push,0,0);
    ARG* arg = makeARG(target, mode);
    ARG* args[2];
    args[0] = arg;
    INS* ins = makeINS(op, args);
    quickAddIns(ins);
}

void quickAddPop(Mode* mode, Target* target)
{
    OP* op = makeOP(pop,0,0);
    ARG* arg = makeARG(target, mode);
    ARG* args[2];
    args[0] = arg;
    INS* ins = makeINS(op, args);
    quickAddIns(ins);
}

//Pushes a variable (identifier) on the stack
void quickAddPushId(char* name)
{
    quickAddMoveRBPToRSL();

    int* staticLinkJumpsAndOffset = staticLinkCount(name,currentScope);
    for(int i=0; i < staticLinkJumpsAndOffset[0]; i++)
        quickAddMeta(FOLLOW_STATIC_LINK);

    Mode* modeVar = makeMode(irl,staticLinkJumpsAndOffset[1]);
    Target* targetVar = makeTarget(rsl,0,0);
    quickAddPush(modeVar, targetVar);

    free(staticLinkJumpsAndOffset);
    free(staticLinkJumpsAndOffset+1);
}

void quickAddPopRRT()
{
    Mode* dirMode = makeMode(dir,0);
    Target* rrtTarget = makeTarget(rrt,0,0);
    ARG* rrtARG = makeARG(rrtTarget,dirMode);
    OP* op = makeOP(pop,0,bits_64);
    ARG* args[2] = {rrtARG,NULL};
    quickAddIns(makeINS(op,args));
}

void quickAddPopReg(int registerNumber)
{
    OP* op = makeOP(pop,0,bits_64);
    Mode* dirMode = makeMode(dir,0);
    Target* t = makeTarget(reg,0,registerNumber);
    ARG* arg = makeARG(t,dirMode);
    ARG* args[2] = {arg,NULL};
    quickAddIns(makeINS(op,args));
}

void quickAddPushReg(int regNumber)
{
    Mode* direct = makeMode(dir,0);
    Target* targetRegister = makeTarget(reg,0,regNumber);
    quickAddPush(direct, targetRegister);
}

void quickAddMoveRBPToRSL()
{
    Mode* dirMode = makeMode(dir,0);

    Target* rbpTarget = makeTarget(rbp,0,0);
    ARG* rbpARG = makeARG(rbpTarget,dirMode);

    Target* rslTarget = makeTarget(rsl,0,0);
    ARG* rslARG = makeARG(rslTarget,dirMode);

    OP* op = makeOP(move,0,bits_64);
    ARG* args[2] = {rbpARG, rslARG};
    INS* ins = makeINS(op,args);
    quickAddIns(ins);
}

void quickAddCheckTruthValue()
{
    OP* op = makeOP(cmp,0,bits_64);
    Mode* dirMode = makeMode(dir,0);

    ARG* from = makeARG(makeTarget(rrt,0,0),dirMode);
    ARG* to = makeARG(makeTarget(imi,0,1),dirMode);
    ARG* args[2] = {from,to};

    INS* ins = makeINS(op,args);
    quickAddIns(ins);
}

void quickAddJumpIfFalse(labelKind k, int labelNumber)
{
    OP* op = makeOP(jne,0,0);
    Mode* dirMode = makeMode(dir,0);
    ARG* label = makeARG(makeTarget(mem,k,labelNumber),dirMode);
    ARG* args[2] = {label,NULL};
    quickAddIns(makeINS(op,args));
}

void quickAddUnconditionalJmp(labelKind k, int labelNumber)
{
    OP* op = makeOP(jmp,0,0);
    Mode* dirMode = makeMode(dir,0);
    ARG* label = makeARG(makeTarget(mem,k,labelNumber),dirMode);
    ARG* args[2] = {label,NULL};
    quickAddIns(makeINS(op,args));
}

void quickAddArithmeticINS(opKind k, opSize size)
{
    quickAddPopReg(2); //Right side of binop
    quickAddPopReg(1); //Left side of binop

    Mode* direct = makeMode(dir,0);
    Target* left = makeTarget(reg,0,2);
    Target* right = makeTarget(reg,0,1);
    ARG* argLeft = makeARG(left, direct);
    ARG* argRight = makeARG(right, direct);
    ARG* args[2] = {argLeft,argRight};
    OP* op = makeOP(k,0,size);
    quickAddIns(makeINS(op,args));
}

void quickAddCompareINS(char* op)
{

}

void quickAddBooleanINS(char* op)
{

}

int whileLabelNumber = 0;
int ifLabelNumber = 0;
int labelGenerator(labelKind kind) {
    if(kind == while_label)
        return whileLabelNumber++;
    if(kind == if_label)
        return ifLabelNumber++;
    return 0;
}

opSize getSizeOfType(char* typeName)
{
    if (strcmp(typeName, "BOOLEAN") == 0)
        return bits_8;
    if (strcmp(typeName, "INT") == 0)
        return bits_32;
    if (strcmp(typeName, "DOUBLE") == 0)
        return bits_64;
    if (strcmp(typeName, "CHAR") == 0)
        return bits_8;
    return 0;
}

opSize getSizeOfId(char* idName)
{
    SYMBOL* id = lookupSymbolVar(idName,currentScope);
    return getSizeOfType(id->name);
}

