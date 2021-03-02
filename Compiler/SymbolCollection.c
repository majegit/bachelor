#include <stdio.h>
#include "Tree.h"
#include "SCTraversal.h"



void symbolCollection(PROGRAM* p)
{
    scTraversePROGRAM(p);
}

void scTraversePROGRAM(PROGRAM* prog)
{
    prog->symbolTable = makeSYMBOLTABLE(NULL);
    scTraverseSTMTCOMP(prog->body, prog->symbolTable);
    scTraverseFUNCTIONNODE(prog->fn, prog->symbolTable);
}

void scTraverseSTMTCOMP(STMTCOMP* sc, SYMBOLTABLE* st)
{
    scTraverseSTMTNODE(sc->stmtnode, st);
}


void scTraverseSTMTNODE(STMTNODE* sn, SYMBOLTABLE* st)
{
    if(sn == NULL)
        return;
    scTraverseSTMT(sn->stmt, st);
    scTraverseSTMTNODE(sn->next, st);
}

void scTraverseSTMT(STMT* s, SYMBOLTABLE* st)
{

    switch(s->kind)
    {
        case whileK:
        {
            SYMBOLTABLE* newTable = makeSYMBOLTABLE(st);
            scTraverseSTMTCOMP(s->val.whileS.body, newTable);
            break;
        }
        case assignK:
            break;
        case ifElseK:
        {
            SYMBOLTABLE* newTable = makeSYMBOLTABLE(st);
            scTraverseSTMTCOMP(s->val.ifElseS.ifbody, newTable);
            SYMBOLTABLE* newTable2 = makeSYMBOLTABLE(st);
            scTraverseSTMTCOMP(s->val.ifElseS.elsebody, newTable2);
            break;
        }
        case returnK:
            break;
        case printK:
            break;
        case declK:
        {
            SYMBOL* newSymbol = makeSYMBOLvariable(s->val.declS.name,s->val.declS.type);
            addSymbol(newSymbol,st);
            break;
        }
        case expK:
            break;
    }
}

void scTraverseFUNCTIONNODE(FUNCTIONNODE* fn, SYMBOLTABLE* st)
{
    if(fn == NULL)
        return;
    scTraverseFUNCTION(fn->current, st);
    scTraverseFUNCTIONNODE(fn->next, st);
}

void scTraverseFUNCTION(FUNCTION* f, SYMBOLTABLE* st)
{
    SYMBOL* funSymbol = makeSYMBOLfunction(f->name, f->returnType);
    addSymbol(funSymbol,st);
    SYMBOLTABLE* newTable
    scTraverseFPARAMETERNODE(f->args, st);
    scTraverseSTMTCOMP(f->body, st);
}

void scTraverseFPARAMETERNODE(FPARAMETERNODE* fpn, SYMBOLTABLE* st)
{
    if(fpn == NULL)
        return;
    SYMBOL* newSymbol = makeSYMBOLvariable(fpn->current->name, fpn->current->type)
    scTraverseFPARAMETERNODE(fpn->next, st);
}