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
    scTraverseSTMTCOMP2(prog->sc, prog->globalScope);
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
            SYMBOL* symbol = lookupSymbolVarName(s->val.assignS.name, st);
            if(symbol == NULL)
            {
                printf("ERROR: Variable not declared: %s on line: %d\n",s->val.assignS.name,s->lineno);
                exit(0);
            }
            s->val.assignS.symbol = symbol;
            scTraverseEXP(s->val.assignS.val,st);
            break;
        }
        case printK:
            scTraverseEXP(s->val.printS,st);
            break;
        case returnK:
            scTraverseEXP(s->val.returnS,st);
            break;
        case expK:
            scTraverseEXP(s->val.expS, st);
            break;
    }
}

void scTraverseEXP(EXP* e, SYMBOLTABLE* st)
{
    switch(e->kind)
    {
        case idK:
        {
            SYMBOL* symbol = lookupSymbolVarName(e->val.idE.id, st);
            if(symbol == NULL)
            {
                printf("ERROR: Variable not declared: %s on line: %d\n",e->val.idE.id,e->lineno);
                exit(0);
            }
            e->val.idE.symbol = symbol;
            break;
        }
        case binopK:
            scTraverseEXP(e->val.binopE.left, st);
            scTraverseEXP(e->val.binopE.right, st);
            break;
        case funK:
            scTraverseAPARAMETERNODE(e->val.funE.aparameternode, st);
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
}

void scTraverseFPARAMETERNODE(FPARAMETERNODE* fpn, SYMBOLTABLE* st)
{
    if(fpn == NULL)
        return;
    SYMBOL* newSymbol = makeSYMBOLformalParameter(fpn->current->name, fpn->current->type);
    addSymbol(newSymbol, st);
    scTraverseFPARAMETERNODE(fpn->next, st);
}

void scTraverseAPARAMETERNODE(APARAMETERNODE* apn, SYMBOLTABLE* st)
{
    if(apn == NULL)
        return;
    scTraverseEXP(apn->current->exp, st);
    scTraverseAPARAMETERNODE(apn->next, st);
}

///SECOND TRAVERSAL

void scTraverseSTMTCOMP2(STMTCOMP* sc, SYMBOLTABLE* st)
{
    scTraverseSTMTNODE2(sc->stmtnode, st);
}

void scTraverseSTMTNODE2(STMTNODE* sn, SYMBOLTABLE* st)
{
    if(sn == NULL)
        return;
    scTraverseSTMT2(sn->stmt, st);
    scTraverseSTMTNODE2(sn->next, st);
}

void scTraverseSTMT2(STMT* s, SYMBOLTABLE* st)
{
    switch(s->kind)
    {
        case whileK:
            scTraverseEXP2(s->val.whileS.guard,st);
            scTraverseSTMTCOMP2(s->val.whileS.body, s->val.whileS.body->symbolTable);
            break;
        case ifElseK:
            scTraverseEXP2(s->val.ifElseS.cond,st);
            scTraverseSTMTCOMP2(s->val.ifElseS.ifbody, s->val.ifElseS.ifbody->symbolTable);
            if(s->val.ifElseS.elsebody != NULL)
                scTraverseSTMTCOMP2(s->val.ifElseS.elsebody, s->val.ifElseS.elsebody->symbolTable);
            break;
        case varDeclK:
            break;
        case funDeclK:
            scTraverseFUNCTION2(s->val.funDeclS,st);
            break;
        case assignK:
            scTraverseEXP2(s->val.assignS.val,st);
            break;
        case printK:
            scTraverseEXP2(s->val.printS,st);
            break;
        case returnK:
            scTraverseEXP2(s->val.returnS,st);
            break;
        case expK:
            scTraverseEXP2(s->val.expS, st);
            break;
    }
}

void scTraverseFUNCTION2(FUNCTION* f, SYMBOLTABLE* st)
{
    scTraverseSTMTCOMP2(f->body, f->body->symbolTable);
}

void scTraverseEXP2(EXP* e, SYMBOLTABLE* st)
{
    switch(e->kind)
    {
        case binopK:
            scTraverseEXP2(e->val.binopE.left, st);
            scTraverseEXP2(e->val.binopE.right, st);
            break;
        case funK:
        {
            SYMBOL* funSymbol = lookupSymbolFunName(e->val.funE.id, st);
            if(funSymbol == NULL)
            {
                printf("ERROR: Function does not exist: %s on line: %d\n", e->val.funE.id, e->lineno);
                exit(0);
            }
            e->val.funE.symbol = funSymbol;
            scTraverseAPARAMETERNODE2(e->val.funE.aparameternode, st);
            break;
        }
        default:
            break;
    }
}

void scTraverseAPARAMETERNODE2(APARAMETERNODE* apn, SYMBOLTABLE* st)
{
    if(apn == NULL)
        return;
    scTraverseEXP2(apn->current->exp, st);
    scTraverseAPARAMETERNODE2(apn->next, st);
}

