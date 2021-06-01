#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TypeChecking.h"
#include "Operations.c"

SYMBOLTABLE* currentScope = NULL;
FUNCTION* currentFunction = NULL;

void typeChecking(PROGRAM* p)
{
    tcTraversePROGRAM(p);
}

void tcTraversePROGRAM(PROGRAM* prog)
{
    currentScope = prog->globalScope;
    tcTraverseSTMTCOMP(prog->sc);
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
            SYMBOL* var = lookupSymbolVarName(s->val.assignS.name, currentScope);
            if(!isSubtype(stringToType(s->val.assignS.val->type),stringToType(var->type)))
            {
                printf("ERROR: Incompatible type, expected %s, got %s on line: %d\n",var->type,s->val.assignS.val->type,s->lineno);
                exit(0);
            }
            if(strcmp(s->val.assignS.val->type,var->type) != 0)
            {
                EXP* e = makeEXPcoerce(var->type,s->val.assignS.val);
                s->val.assignS.val = e;
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
            if(s->val.ifElseS.elsebody != NULL)
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
            {
                EXP* e = makeEXPcoerce(currentFunction->returnType, s->val.returnS);
                s->val.returnS = e;
            }
            break;
        case printK:
            tcTraverseEXP(s->val.printS);
            break;
        case varDeclK:
            break;
        case expK:
            tcTraverseEXP(s->val.expS);
            break;
        case funDeclK:
            tcTraverseFUNCTION(s->val.funDeclS);
            break;
    }
}

void tcTraverseEXP(EXP* e)
{
    switch(e->kind)
    {
        case idK:
        {
            e->type = e->val.idE.symbol->type;
            break;
        }
        case binopK:
        {
            tcTraverseEXP(e->val.binopE.left);
            tcTraverseEXP(e->val.binopE.right);
            OPERATION_WRAPPER *opWrapper = searchOperations(e->val.binopE.operator, e->val.binopE.left->type, e->val.binopE.right->type);
            if (opWrapper->opCount == 0) {
                printf("ERROR: Operator '%s' not defined for %s %s on line: %d\n", e->val.binopE.operator,
                       e->val.binopE.left->type, e->val.binopE.right->type, e->lineno);
                exit(0);
            }
            if (opWrapper->opCount > 1) {
                printf("ERROR: multiple resolutions for %s '%s' %s, on lineno: %d\n", e->val.binopE.left->type,
                       e->val.binopE.operator, e->val.binopE.right->type, e->lineno);
                exit(0);
            }
            if (strcmp(opWrapper->op->argTypes[0]->type, e->val.binopE.left->type) != 0) //Make coercion for the left argument
            {
                EXP *ce = makeEXPcoerce(opWrapper->op->argTypes[0]->type, e->val.binopE.left);
                e->val.binopE.left = ce;
            }
            if (strcmp(opWrapper->op->argTypes[1]->type, e->val.binopE.right->type) != 0) //Make coercion for the right argument
            {
                EXP *ce = makeEXPcoerce(opWrapper->op->argTypes[1]->type, e->val.binopE.right);
                e->val.binopE.right = ce;
            }
            e->type = opWrapper->op->returnType->type;
            break;
        }
        case funK:
        {
            tcTraverseAPARAMETERNODE(e->val.funE.aparameternode, e->val.funE.symbol->fpn);
            e->type = e->val.funE.symbol->type;
            break;
        }
        case coerceK:
            tcTraverseEXP(e->val.coerceE);
            break;
        default:
            break;
    }
}

void tcTraverseAPARAMETERNODE(APARAMETERNODE* apn, FPARAMETERNODE* fpn)
{
    if(apn == NULL && fpn == NULL)
        return;
    if(apn == NULL)
    {
        printf("ERROR1: Mismatched arguments for function call on line: %d\n", fpn->current->lineno);
        exit(0);
    }
    if(fpn == NULL)
    {
        printf("ERROR2: Mismatched arguments for function call on line: %d\n", apn->current->lineno);
        exit(0);
    }
    tcTraverseEXP(apn->current->exp);
    if(!isSubtype(stringToType(apn->current->exp->type), stringToType(fpn->current->type)))
    {
        printf("ERROR3: Mismatched arguments for function call on line: %d\n", apn->current->exp->lineno);
        exit(0);
    }
    if(strcmp(apn->current->exp->type,fpn->current->type) != 0)
    {
        EXP* ce = makeEXPcoerce(fpn->current->type, apn->current->exp);
        apn->current->exp = ce;
    }
    tcTraverseAPARAMETERNODE(apn->next, fpn->next);
}

void tcTraverseFUNCTION(FUNCTION* f)
{
    FUNCTION* oldFun = currentFunction; //Save pointer to the outer function containing f
    currentFunction = f; //Save pointer to the outer function containing f

    tcTraverseSTMTCOMP(f->body);
    currentFunction = oldFun;
}


