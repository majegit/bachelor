#include <stdio.h>
#include <stdlib.h>
#include "TypeChecking.h"
#include "Operations.c"
#include <string.h>

SYMBOLTABLE* currentScope;
FUNCTION* currentFunction;

void typeChecking(PROGRAM* p)
{
    tcTraversePROGRAM(p);
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
            tcTraverseEXP(s->val.whileS.guard);
            if(strcmp(s->val.whileS.guard->type, "BOOLEAN") != 0)
            {
                printf("ERROR: Incompatible type, expected BOOLEAN, got %s at line: %d.\n",s->val.whileS.guard->type,s->lineno);
                exit(0);
            }
            tcTraverseSTMTCOMP(s->val.whileS.body);
            break;
        case assignK:
            tcTraverseEXP(s->val.assignS.val);
            SYMBOL* symbol = lookupSymbolVar(s->val.assignS.name, currentScope);
            if(symbol == NULL)
            {
                printf("ERROR: Variable not declared: %s on line: %d\n",s->val.assignS.name,s->lineno);
                exit(0);
            }
            if(!isSubtype(stringToType(s->val.assignS.val->type),stringToType(symbol->type)))
            {
                printf("ERROR: Incompatible type, expected %s, got %s on line: %d\n",symbol->type,s->val.assignS.val->type,s->lineno);
                exit(0);
            }
            if(strcmp(s->val.assignS.val->type,symbol->type) != 0)
                s->val.assignS.val->coerceTo = symbol->type;
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
            if(!isSubtype(stringToType(s->val.returnS->type),stringToType(currentFunction->returnType)))
            {
                printf("ERROR: Incompatible type, expected %s, got %s at line: %d.\n",currentFunction->returnType,s->val.returnS->type,s->lineno);
                exit(0);
            }
            if(strcmp(s->val.returnS->type,currentFunction->returnType) != 0)
                s->val.returnS->coerceTo = currentFunction->returnType;
            break;
        case printK:
            tcTraverseEXP(s->val.printS);
            break;
        case declK:
            if(s->val.declS.value != NULL)
            {
                tcTraverseEXP(s->val.declS.value);
                if(!isSubtype(stringToType(s->val.declS.value->type),stringToType(s->val.declS.type)))
                {
                    printf("ERROR: Incompatible type, expected %s, got %s at line: %d.\n",s->val.declS.type,s->val.declS.value->type,s->lineno);
                    exit(0);
                }
                if(strcmp(s->val.declS.value->type,s->val.declS.type) != 0)
                    s->val.declS.value->coerceTo = s->val.declS.type;
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
                SYMBOL* symbol = lookupSymbolVar(e->val.idE, currentScope);
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
            OPERATION_WRAPPER* operationWrapper = searchOperations(e->val.binopE.operator, e->val.binopE.left->type, e->val.binopE.right->type);
            if(operationWrapper->opCount == 0)
            {
                printf("ERROR: Operator '%s' not defined for %s %s on line: %d\n",e->val.binopE.operator,e->val.binopE.left->type,e->val.binopE.right->type,e->lineno);
                exit(0);
            }
            if(operationWrapper->opCount > 1)
            {
                printf("ERROR: multiple resolutions for %s '%s' %s, on lineno: %d\n",e->val.binopE.left->type,e->val.binopE.operator,e->val.binopE.right->type,e->lineno);
                exit(0);
            }
            if(strcmp(operationWrapper->op->argTypes[0]->type, e->val.binopE.left->type) != 0) //Flag coercion for the left argument
                e->val.binopE.left->coerceTo = operationWrapper->op->argTypes[0]->type;
            if(strcmp(operationWrapper->op->argTypes[1]->type, e->val.binopE.right->type) != 0) //Flag coercion for the right argument
                e->val.binopE.right->coerceTo = operationWrapper->op->argTypes[1]->type;
            e->type = operationWrapper->op->returnType->type;
            break;
        case funK:
            {
                SYMBOL* functionSymbol = lookupSymbolFun(e->val.funE.id, currentScope);
                if(functionSymbol == NULL)
                {
                    printf("ERROR: Function does not exist: %s on line: %d\n",e->val.funE.id,e->lineno);
                    exit(0);
                }
                tcTraverseAPARAMETERNODE(e->val.funE.aparameternode, functionSymbol->fpn);
                e->type = functionSymbol->type;
            }
            break;
    }
}

void tcTraverseAPARAMETERNODE(APARAMETERNODE* apn, FPARAMETERNODE* fpn)
{
    if(apn == NULL && fpn == NULL)
        return;
    if(apn == NULL && fpn != NULL || apn != NULL && fpn == NULL)
    {
        printf("ERROR: Mismatched arguments for function call on line:\n");
        exit(0);
    }
    tcTraverseEXP(apn->current->exp);
    if(!isSubtype(stringToType(apn->current->exp->type), stringToType(fpn->current->type)))
    {
        printf("ERROR: Mismatched arguments for function call on line: %d\n", apn->current->exp->lineno);
        exit(0);
    }
    if(strcmp(apn->current->exp->type,fpn->current->type) != 0)
        apn->current->exp->coerceTo = fpn->current->type;
    tcTraverseAPARAMETERNODE(apn->next, fpn->next);
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
    tcTraverseSTMTCOMP(f->body);
    currentFunction = NULL;
}


