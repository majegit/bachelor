#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tree.h"
#include "SymbolCollection.h"

void symbolCollection(PROGRAM* p)
{
    scTraversePROGRAM(p);
}

void scTraversePROGRAM(PROGRAM* prog) {
    scTraverseSTMTCOMP(prog->sc, prog->globalScope);
}

void scTraverseSTMTCOMP(STMTCOMP* sc, SYMBOLTABLE* st)
{
    sc->symbolTable = st;
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
            scTraverseEXP(s->val.whileS.guard,st);
            SYMBOLTABLE* newTable = makeSYMBOLTABLE(st);
            scTraverseSTMTCOMP(s->val.whileS.body, newTable);
            break;
        }
        case ifElseK:
        {
            scTraverseEXP(s->val.ifElseS.cond,st);
            SYMBOLTABLE* newTable = makeSYMBOLTABLE(st);
            scTraverseSTMTCOMP(s->val.ifElseS.ifbody, newTable);

            if(s->val.ifElseS.elsebody != NULL)
            {
                SYMBOLTABLE* newTable2 = makeSYMBOLTABLE(st);
                scTraverseSTMTCOMP(s->val.ifElseS.elsebody, newTable2);
            }
            break;
        }
        case varDeclK:
        {
            SYMBOL* newSymbol = makeSYMBOLvariable(s->val.varDeclS.name,s->val.varDeclS.type);
            addSymbol(newSymbol,st);
            break;
        }
        case funDeclK:
        {
            SYMBOL* newSymbol = makeSYMBOLfunction(s->val.funDeclS->name,s->val.funDeclS->returnType,s->val.funDeclS->args);
            addSymbol(newSymbol,st);
            scTraverseFUNCTION(s->val.funDeclS,st);
            break;
        }
        case assignK:
        {
            if(lookupSymbolVar(s->val.assignS.name, st) == NULL)
            {
                printf("ERROR: Variable not declared: %s on line: %d\n",s->val.assignS.name,s->lineno);
                exit(0);
            }
            scTraverseEXP(s->val.assignS.val,st);
            break;
        }
        case printK:
            scTraverseEXP(s->val.printS,st);
            break;
        case returnK:
            scTraverseEXP(s->val.returnS,st);
            break;
        default:
            break;
    }
}

void scTraverseEXP(EXP* e, SYMBOLTABLE* st)
{
    switch(e->kind)
    {
        case idK:
        {
            SYMBOL* symbol = lookupSymbolVar(e->val.idE, st);
            if(symbol == NULL)
            {
                printf("ERROR: Variable not declared: %s on line: %d\n",e->val.idE,e->lineno);
                exit(0);
            }
            break;
        }
        case binopK:
            scTraverseEXP(e->val.binopE.left, st);
            scTraverseEXP(e->val.binopE.right, st);
            break;
        default:
            break;
    }
}

void scTraverseFUNCTION(FUNCTION* f, SYMBOLTABLE* st)
{
    SYMBOLTABLE* newScope = makeSYMBOLTABLE(st);
    scTraverseFPARAMETERNODE(f->args, newScope);
    scTraverseSTMTCOMP(f->body, newScope);

    //Check if all branches of computation ends with a return stmt
    if(allBranchesReturn(f->body->stmtnode) == 0)
    {
        printf("ERROR: not all branches of function \"%s\" have a return statement on line: %d",f->name,f->lineno);
        exit(0);
    }
}

void scTraverseFPARAMETERNODE(FPARAMETERNODE* fpn, SYMBOLTABLE* st)
{
    if(fpn == NULL)
        return;
    SYMBOL* newSymbol = makeSYMBOLformalParameter(fpn->current->name, fpn->current->type);
    addSymbol(newSymbol, st);
    scTraverseFPARAMETERNODE(fpn->next, st);
}

int allBranchesReturn(STMTNODE* sn)
{
    int alwaysReturn = 0;
    while(sn != NULL && alwaysReturn == 0)
    {
        STMT* this = sn->stmt;
        if(this->kind == returnK)
            alwaysReturn = 1;
        else if(this->kind == ifElseK && this->val.ifElseS.elsebody != NULL)
            alwaysReturn = allBranchesReturn(this->val.ifElseS.ifbody->stmtnode) & allBranchesReturn(this->val.ifElseS.elsebody->stmtnode);
        sn = sn->next;
    }
    return alwaysReturn;
}

