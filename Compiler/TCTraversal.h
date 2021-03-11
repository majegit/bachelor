#include <stdio.h>
#include "Tree.h"

void tcTraversePROGRAM(PROGRAM* prog)
{
    tcTraverseSTMTCOMP(prog->body);
    tcTraverseFUNCTIONNODE(prog->fn);
}

void tcTraverseSTMTCOMP(STMTCOMP* sc)
{
    tcTraverseSTMTNODE(sc->stmtnode);
}


void tcTraverseSTMTNODE(STMTNODE* sn)
{
    if(sn == NULL)
        return;
    tcTraverseSTMT(sn->current);
    tcTraverseSTMTNODE(sn->next);
}

void tcTraverseSTMT(STMT* s)
{
    switch(s->kind)
    {
        case whileK:
            tcTraverseEXP(s->val.whileS.guard); //Must have type boolean
            if(strcmp(s->val.whileS.guard->type, "BOOLEAN") != 0)
                printf("The fuck is this type of the guard?");
            tcTraverseSTMTCOMP(s->val.whileS.body);
            break;
        case assignK:
            tcTraverseEXP(s->val.assignS.val);
            break;
        case ifElseK:
            tcTraverseEXP(s->val.ifElseS.cond);
            tcTraverseSTMTCOMP(s->val.ifElseS.ifbody);
            tcTraverseSTMTCOMP(s->val.ifElseS.elsebody);
            break;
        case returnK:
            tcTraverseEXP(s->val.returnS);
            break;
        case printK:
            tcTraverseEXP(s->val.printS);
            break;
        case declK:
            tcTraverseEXP(s->val.declS.value);
            break;
        case expK:
            tcTraverseEXP(s->val.expS);
            break;
    }
}

void tcTraverseEXP(EXP* e)
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
            tcTraverseEXP(e->binopE.left);
            tcTraverseEXP(e->binopE.right);
            break;
        case funK;
            tcTraverseAPARAMETERNODE(e->funE.aparameternode);
            break;
    }
}
void tcTraverseAPARAMETERNODE(APARAMETERNODE* apn)
{
    if(apn == NULL)
        return;
    tcTraverseEXP(apn->current->exp);
    tcTraverseAPARAMETERNODE(apn->next);
}

void tcTraverseFUNCTIONNODE(FUNCTIONNODE* fn)
{
    if(fn == NULL)
        return;
    tcTraverseFUNCTION(sc->stmtnode);
    tcTraverseFUNCTIONNODE(fn->next);
}

void tcTraverseFUNCTION(FUNCTION* f)
{
    tcTraverseFPARAMETERNODE(f->args);
    tcTraverseSTMTCOMP(f->body);
}

void tcTraverseFPARAMETERNODE(FPARAMETERNODE* fpn)
{
    if(fpn == NULL)
        return;
    tcTraverseFPARAMETERNODE(fpn->next);
}

