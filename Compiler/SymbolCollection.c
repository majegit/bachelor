#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tree.h"
#include "SymbolCollection.h"
#include "Error.h"

int mainFound = 0;

void symbolCollection(PROGRAM* p)
{
    scTraversePROGRAM(p);
}

void scTraversePROGRAM(PROGRAM* prog)
{
    scTraverseGlobalSTMTNODE(prog->sc->stmtnode);
    scTraverseSTMTCOMP(prog->sc, prog->globalScope);
    if(!mainFound)
        throwError("no main function found!");
}

//The global scope can only contain declarations
void scTraverseGlobalSTMTNODE(STMTNODE* sn)
{
    if(sn == NULL)
        return;
    if(sn->stmt->kind != funDeclK && sn->stmt->kind != varDeclK)
    {
        printf("ERROR: the global scope can only contain declarations on line: %d",sn->stmt->lineno);
        exit(0);
    }
    scTraverseGlobalSTMTNODE(sn->next);
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
            SYMBOLTABLE* newTable = makeSYMBOLTABLE(st);
            scTraverseSTMTCOMP(s->val.whileS.body, newTable);
            break;
        }
        case ifElseK:
        {
            SYMBOLTABLE* newTable = makeSYMBOLTABLE(st);
            scTraverseSTMTCOMP(s->val.ifElseS.ifbody, newTable);

            SYMBOLTABLE* newTable2 = makeSYMBOLTABLE(st);
            scTraverseSTMTCOMP(s->val.ifElseS.elsebody, newTable2);
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
            if(lookupSymbolVar(s->val.assignS.name, st) == NULL)
            {
                printf("ERROR: Variable not declared: %s on line: %d\n",s->val.assignS.name,s->lineno);
                exit(0);
            }
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
    //Add function name and returnType to current table
    if(strcmp(f->name,"main") == 0)
    {
        mainFound = 1;
        if(strcmp(f->returnType,"INT") != 0 || f->args != NULL)
            throwError("declare main as: \"int main()\"");
        if(st->par != NULL)
            throwError("the main function must be in the global scope!");
    }

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