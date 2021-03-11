#include <stdio.h>
#include <stdlib.h>
#include "TypeChecking.h"
#include "Operations.c"
#include "Tree.h"
#include <string.h>

SUBTYPE BOOL,CHAR,INT,DOUBLE;

SUBTYPE BOOL = {"BOOLEAN",NULL,NULL};
SUBTYPE CHAR = {"CHAR",NULL,NULL};
SUBTYPE INT = {"INT",&DOUBLE,NULL};
SUBTYPE DOUBLE = {"DOUBLE",NULL,&INT};

TYPESYSTEM ts = {{&BOOL,&CHAR,&DOUBLE}};

SYMBOLTABLE* currentScope;
FUNCTION* currentFunction;

void TypeChecking(PROGRAM* p)
{


}

void tcTraversePROGRAM(PROGRAM* prog)
{
    currentScope = prog->symbolTable;
    tcTraverseSTMTCOMP(prog->body);
    tcTraverseFUNCTIONNODE(prog->fn);
}

void tcTraverseSTMTCOMP(STMTCOMP* sc)
{
    currentScope = sc->symbolTable;
    tcTraverseSTMTNODE(sc->stmtnode);
    currentScope = currentScope->par;
}


void tcTraverseSTMTNODE(STMTNODE* sn)
{
    if(sn == NULL)
        return;
    tcTraverseSTMT(sn->stmt);
    tcTraverseSTMTNODE(sn->next);
}

void tcTraverseSTMT(STMT* s)
{
    switch(s->kind)
    {
        case whileK:
            tcTraverseEXP(s->val.whileS.guard); //Must have type boolean
            if(strcmp(s->val.whileS.guard->type, "BOOLEAN") != 0)
            {
                printf("ERROR: Incompatible type, expected BOOLEAN, got %s at line: %d.\n",s->val.whileS.guard->type,s->lineno);
                exit(0);
            }
            tcTraverseSTMTCOMP(s->val.whileS.body);
            break;
        case assignK:
            tcTraverseEXP(s->val.assignS.val);
            SYMBOL* symbol = lookupSymbol(s->val.assignS.name,currentScope);
            if(symbol == NULL)
            {
                printf("ERROR: Variable not declared: %s on line: %d\n",s->val.assignS.name,s->lineno);
                exit(0);
            }
            if(strcmp(symbol->type,s->val.assignS.val->type) != 0)
            {
                printf("ERROR: Incompatible type, expected %s, got %s on line: %d\n",symbol->type,s->val.assignS.val->type,s->lineno);
                exit(0);
            }
            break;
        case ifElseK:
            tcTraverseEXP(s->val.ifElseS.cond);
            if(strcmp(s->val.ifElseS.cond->type, "BOOLEAN") != 0)
            {
                printf("ERROR: Incompatible type, expected BOOLEAN, got %s at line: %d.\n",s->val.ifElseS.cond->type,s->val.ifElseS.cond->lineno);
                exit(0);
            }
            tcTraverseSTMTCOMP(s->val.ifElseS.ifbody);
            tcTraverseSTMTCOMP(s->val.ifElseS.elsebody);
            break;
        case returnK:
            tcTraverseEXP(s->val.returnS);
            if(strcmp(s->val.returnS->type,currentFunction->returnType) != 0)
            {
                printf("ERROR: Incompatible type, expected %s, got %s at line: %d.\n",currentFunction->returnType,s->val.returnS->type,s->lineno);
                exit(0);
            }
            break;
        case printK:
            tcTraverseEXP(s->val.printS);
            break;
        case declK:
            if(s->val.declS.value != NULL)
            {
                tcTraverseEXP(s->val.declS.value);
                if(strcmp(s->val.declS.type, s->val.declS.value->type) != 0)
                {
                    printf("ERROR: Incompatible type, expected %s, got %s at line: %d.\n",s->val.declS.type,s->val.declS.value->type,s->lineno);
                    exit(0);
                }
            }
            break;
        case expK:
            tcTraverseEXP(s->val.expS);
            if(s->val.expS->kind != funK)
            {
                printf("ERROR: Expected function at line: %d.\n",s->lineno);
                exit(0);
            }
            break;
    }
}

void tcTraverseEXP(EXP* e)
{
    switch(e->kind)
    {
        case idK:
            {
                SYMBOL* symbol = lookupSymbol(e->val.idE,currentScope);
                if(symbol == NULL)
                {
                    printf("ERROR: Variable not declared: %s on line: %d\n",e->val.idE,e->lineno);
                    exit(0);
                }
                e->type = symbol->type;
            }
            break;
        case charK:
            e->type = "CHAR";
            break;
        case intK:
            e->type = "INT";
            break;
        case doubleK:
            e->type = "DOUBLE";
            break;
        case boolK:
            e->type = "BOOLEAN";
            break;
        case binopK:
            tcTraverseEXP(e->val.binopE.left);
            tcTraverseEXP(e->val.binopE.right);
            break;
        case funK:
            tcTraverseAPARAMETERNODE(e->val.funE.aparameternode);

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
    tcTraverseFUNCTION(fn->current);
    tcTraverseFUNCTIONNODE(fn->next);
}

void tcTraverseFUNCTION(FUNCTION* f)
{
    currentFunction = f;
    tcTraverseFPARAMETERNODE(f->args);
    tcTraverseSTMTCOMP(f->body);
    currentFunction = NULL;

}

void tcTraverseFPARAMETERNODE(FPARAMETERNODE* fpn)
{
    if(fpn == NULL)
        return;
    tcTraverseFPARAMETERNODE(fpn->next);
}

