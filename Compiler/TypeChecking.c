#include <stdio.h>
#include <stdlib.h>
#include "TypeChecking.h"
#include "Operations.c"
#include "Tree.h"
#include <string.h>

SUBTYPE BOOL, CHAR, INT, DOUBLE;

SUBTYPE BOOL = {"BOOLEAN",NULL,NULL};
SUBTYPE CHAR = {"CHAR",NULL,NULL};
SUBTYPE INT = {"INT",&DOUBLE,NULL};
SUBTYPE DOUBLE = {"DOUBLE",NULL,&INT};

TYPESYSTEM ts = {{&BOOL,&CHAR,&DOUBLE}};

SYMBOLTABLE* currentScope;
FUNCTION* currentFunction;

void typeChecking(PROGRAM* p)
{
    tcTraversePROGRAM(p);
}

void tcTraversePROGRAM(PROGRAM* prog)
{
    printf("DEBUG: TRAVERSING PROGRAM\n");
    currentScope = prog->symbolTable;
    tcTraverseSTMTCOMP(prog->body);
    tcTraverseFUNCTIONNODE(prog->fn);
}

void tcTraverseSTMTCOMP(STMTCOMP* sc)
{
    printf("DEBUG: TRAVERSING STMTCOMP\n");
    currentScope = sc->symbolTable;
    tcTraverseSTMTNODE(sc->stmtnode);
    currentScope = currentScope->par;
}


void tcTraverseSTMTNODE(STMTNODE* sn)
{
    printf("DEBUG: TRAVERSING STMTNODE\n");
    if(sn == NULL)
        return;
    tcTraverseSTMT(sn->stmt);
    tcTraverseSTMTNODE(sn->next);
}

void tcTraverseSTMT(STMT* s)
{
    printf("DEBUG: TRAVERSING STMT\n");
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
            SYMBOL* symbol = lookupSymbolVar(s->val.assignS.name, currentScope);
            printf("At assign statement\n");
            if(symbol == NULL)
            {
                printf("ERROR: Variable not declared: %s on line: %d\n",s->val.assignS.name,s->lineno);
                exit(0);
            }
            printf("At assign statement2\n");
            if(s->val.assignS.val == NULL)
            {
                printf("EXPRESSION IS NULL\n");
            }
            printf("At assign statement3\n");
            if(symbol->type == NULL)
                printf("it is null\n");
            if(s->val.assignS.val->type == NULL)
                printf("the type is null\n");
            printf("%s\n",symbol->type);
            printf("%s\n",s->val.assignS.val->type);
            if(strcmp(symbol->type,s->val.assignS.val->type) != 0)
            {
                printf("yes");
                printf("ERROR: Incompatible type, expected %s, got %s on line: %d\n",symbol->type,s->val.assignS.val->type,s->lineno);
                exit(0);
            }
            printf("End of assign\n");
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
    printf("DEBUG: TRAVERSING EXP\n");
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
            OPERATION* op = searchOperations(e->val.binopE.operator, e->val.binopE.left->type, e->val.binopE.right->type);
            if(op == NULL)
            {
                printf("ERROR: Operator '%s' not defined for %s %s: %d on line: %d\n",e->val.binopE.operator,e->val.binopE.left->type,e->val.binopE.right->type,e->lineno);
                exit(0);
            }
            e->type = op->returnType;
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
    printf("DEBUG: TRAVERSING APARAMNODE\n");
    if(apn == NULL && fpn == NULL)
        return;
    if(apn == NULL && fpn != NULL || apn != NULL && fpn == NULL)
    {
        printf("ERROR: Mismatched arguments for function call on line:\n");
        exit(0);
    }
    tcTraverseEXP(apn->current->exp);
    if(strcmp(apn->current->exp->type, fpn->current->type) != 0)
    {
        printf("ERROR: Mismatched arguments for function call on line: %d\n");
        exit(0);
    }
    tcTraverseAPARAMETERNODE(apn->next, fpn->next);
}

void tcTraverseFUNCTIONNODE(FUNCTIONNODE* fn)
{
    printf("DEBUG: TRAVERSING FUNCTIONNODE\n");
    if(fn == NULL)
        return;
    tcTraverseFUNCTION(fn->current);
    tcTraverseFUNCTIONNODE(fn->next);
}

void tcTraverseFUNCTION(FUNCTION* f)
{
    printf("DEBUG: TRAVERSING FUNCTION\n");
    currentFunction = f;
    tcTraverseSTMTCOMP(f->body);
    currentFunction = NULL;
}


