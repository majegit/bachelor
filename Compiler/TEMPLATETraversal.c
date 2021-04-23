#include <stdio.h>
#include "Tree.h"

void traversePROGRAM(PROGRAM* prog)
{
    traverseSTMTCOMP(prog->body);
    traverseFUNCTIONNODE(prog->fn);
}

void traverseSTMTCOMP(STMTCOMP* sc)
{
    traverseSTMTNODE(sc->stmtnode);
}


void traverseSTMTNODE(STMTNODE* sn)
{
    if(sn == NULL)
        return;
    traverseSTMT(sn->stmt);
    traverseSTMTNODE(sn->next);
}

void traverseSTMT(STMT* s)
{
    switch(s->kind)
    {
        case whileK:
            traverseEXP(s->val.whileS.guard);
            traverseSTMTCOMP(s->val.whileS.body);
            break;
        case assignK:
            traverseEXP(s->val.assignS.val);
            break;
        case ifElseK:
            traverseEXP(s->val.ifElseS.cond);
            traverseSTMTCOMP(s->val.ifElseS.ifbody);
            traverseSTMTCOMP(s->val.ifElseS.elsebody);
            break;
        case returnK:
            traverseEXP(s->val.returnS);
            break;
        case printK:
            traverseEXP(s->val.printS);
            break;
        case varDeclK:
            traverseEXP(s->val.declS.value);
            break;
        case expK:
            traverseEXP(s->val.expS);
            break;
    }
}

void traverseEXP(EXP* e)
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
            traverseEXP(e->binopE.left);
            traverseEXP(e->binopE.right);
            break;
        case funK;
            traverseAPARAMETERNODE(e->funE.aparameternode);
            break;
    }
}
void traverseAPARAMETERNODE(APARAMETERNODE* apn)
{
    if(apn == NULL)
       return;
    traverseEXP(apn->current->exp);
    traverseAPARAMETERNODE(apn->next);
}

void traverseFUNCTIONNODE(FUNCTIONNODE* fn)
{
    if(fn == NULL)
        return;
    traverseFUNCTION(sc->stmtnode);
    traverseFUNCTIONNODE(fn->next);
}

void traverseFUNCTION(FUNCTION* f)
{
    traverseFPARAMETERNODE(f->args);
    traverseSTMTCOMP(f->body);
}

void traverseFPARAMETERNODE(FPARAMETERNODE* fpn)
{
    if(fpn == NULL)
        return;
    traverseFPARAMETERNODE(fpn->next);
}

