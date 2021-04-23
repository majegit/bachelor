#include <stdio.h>
#include <string.h>
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
    scTraverseSTMTNODE(prog->sn, prog->globalScope);
    if(!mainFound)
        throwError("no main function found!");
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
        default:
            break;
    }
}

void scTraverseFUNCTION(FUNCTION* f, SYMBOLTABLE* st)
{
    //Add function name and returnType to current table
    if(strcmp(f->name,"main\n") == 0)
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