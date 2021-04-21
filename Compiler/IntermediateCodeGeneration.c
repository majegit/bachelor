#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"
#include "IntermediateCodeGeneration.h"

SYMBOLTABLE* currentScope;

LL* icgTraversePROGRAM(PROGRAM* prog)
{
    code = (LL*)malloc(sizeof(LL));
    quickAddMeta(PROGRAM_PROLOGUE);
    printf("ic main\n");
    icgTraverseSTMTCOMP(prog->body);

    quickAddMeta(PROGRAM_EPILOGUE);
    icgTraverseFUNCTIONNODE(prog->fn);
    return code;
}

void icgTraverseSTMTCOMP(STMTCOMP* sc)
{
    currentScope = sc->symbolTable;

    quickAddMeta(ALLOCATE_STACK_SPACE); //When entering new scope, rbp is pushed and local variables are given space on the stack
    printf("added meta");
    code->last->ins->op->size = sc->symbolTable->nextLabel; //How much space is allocated is specified here
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
    switch(s->kind)
    {
        case whileK:
            {
                int labelNumber = labelGenerator(while_label);     //X
                quickAddLabel(while_label, labelNumber);           //WhileX:
                icgTraverseEXP(s->val.whileS.guard);               //GuardX

                //cmp $1, reg1
                //jne quickAddLabel(endWhile_label, labelNumber);   endwhile_X

                icgTraverseSTMTCOMP(s->val.whileS.body);


                quickAddLabel(endwhile_label, labelNumber);    //endwhile_X:
            }
            break;
        case assignK:
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
            break;
        case ifElseK:
            {
                icgTraverseEXP(s->val.ifElseS.cond);
                icgTraverseSTMTCOMP(s->val.ifElseS.ifbody);
                icgTraverseSTMTCOMP(s->val.ifElseS.elsebody);
            }
            break;
        case returnK:
            icgTraverseEXP(s->val.returnS);
            break;
        case printK:
            icgTraverseEXP(s->val.printS);
            break;
        case declK:
            icgTraverseEXP(s->val.declS.value);
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
                Mode* mode = makeMode(dir,0);
                ARG* arg = makeARG(target,mode);
                ARG* args[2];
                args[0] = arg;
                INS* ins = makeINS(op,args);
                LLN* node = makeLLN(ins);
                addToLL(node);
            }
            break;
        case doubleK:
            //Generate double constant
            break;
        case boolK:
            {
                OP* op = makeOP(push, 0, 0);
                Target* target = makeTarget(imi, 0, e->val.boolE);
                Mode* mode = makeMode(dir, 0);
                ARG* arg = makeARG(target, mode);
                ARG* args[2];
                args[0] = arg;
                INS* ins = makeINS(op, args);
                LLN* node = makeLLN(ins);
                addToLL(node);
            }
            break;
        case charK:
            break;
        case binopK:
            //First do left
            icgTraverseEXP(e->val.binopE.left);

            //Then do right
            icgTraverseEXP(e->val.binopE.right);
            break;
        case funK:
            //Generate the code for each parameter and throw it on the stack
            icgTraverseAPARAMETERNODE(e->val.funE.aparameternode);
            break;
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
    printf("mkaing op");
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
    return node;
}

void quickAddIns(INS* ins)
{
    LLN* node = makeLLN(ins);
    addToLL(node);
}

void quickAddMeta(metaKind metaK) {
    OP* op = makeOP(meta,metaK,0);
    printf("made meta?");
    ARG* args[2] = {NULL, NULL};
    INS* ins = makeINS(op,args);
    quickAddIns(ins);
};

void quickAddLabel(labelKind kind, int labelNumber)
{
    Target* target = makeTarget(mem,kind,labelNumber);
    Mode* mode = makeMode(dir,0);
    ARG* arg = makeARG(target, mode);
    OP* op = makeOP(label,0,0);
    ARG* args[2];
    args[0] = arg;
    INS* ins = makeINS(op,args);
    quickAddIns(ins);
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
    ARG* args[2];
    args[0] = rrtARG;
    INS* ins = makeINS(op,args);
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

