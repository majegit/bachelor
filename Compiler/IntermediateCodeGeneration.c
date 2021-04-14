#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"
#include "IntermediateCodeGeneration.h"

LL* code;
LL* icgTraversePROGRAM(PROGRAM* prog)
{
    code = (LL*)malloc(sizeof(LL));
    quickAddNode("init");
    icgTraverseSTMTCOMP(prog->body);
    quickAddNode("exit");
    icgTraverseFUNCTIONNODE(prog->fn);
    return code;
}

void icgTraverseSTMTCOMP(STMTCOMP* sc)
{
    quickAddNode("setBase"); //When entering new scope, rbp is pushed and local variables are given space on the stack.
    int i = 0;
    while(i<sc->symbolTable->symbolCount)
    {

    }

    icgTraverseSTMTNODE(sc->stmtnode);

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
            icgTraverseEXP(s->val.whileS.guard);
            icgTraverseSTMTCOMP(s->val.whileS.body);
            break;
        case assignK:
            icgTraverseEXP(s->val.assignS.val);
            break;
        case ifElseK:
            icgTraverseEXP(s->val.ifElseS.cond);
            icgTraverseSTMTCOMP(s->val.ifElseS.ifbody);
            icgTraverseSTMTCOMP(s->val.ifElseS.elsebody);
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
        case idK;
            break;
        case intK;
            break;
        case doubleK;
            break;
        case boolK;
            break;
        case binopK;
            icgTraverseEXP(e->binopE.left);
            icgTraverseEXP(e->binopE.right);
            break;
        case funK;
            icgTraverseAPARAMETERNODE(e->funE.aparameternode);
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
    icgTraverseFUNCTION(sc->stmtnode);
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

void addToLL(LL* currentCode, LLN* newCode)
{
    if(currentCode->first == NULL) //First time we insert something
    {
        currentCode->first = newCode;
        currentCode->last = newCode;
    }
    currentCode->last->next = newCode;
    currentCode->last = newCode;
}

void quickAddNode(const char* kind)
{
    LLN* node = (LLN*)malloc(sizeof(LLN));
    switch(kind) {
        case "ins":
            node->kind = insK;
            break;
        case "label":
            node->kind = labelK;
            break;
        case "funCall":
            node->kind = funCallK;
            break;
        case "setBase":
            node->kind = setBaseK;
            break;
        case "exit":
            node->kind = exitK;
            break;
        case "init":
            node->kind = initK;
            break;
        default:
    }
    addToLL(code,node);
}

