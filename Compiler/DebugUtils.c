#include <stdio.h>
#include "DebugUtils.h"

void printEXP(EXP* exp)
{
    switch(exp->kind)
    {
        case idK:
            printf("id: %s\n",exp->val.idE);
            break;
        case intK:
            printf("int: %d\n",exp->val.intE);
            break;
        case doubleK:
            printf("double: %f\n",exp->val.doubleE);
            break;
        case charK:
            printf("char: %c\n",exp->val.charE);
            break;
        case boolK:
            printf("bool: %d\n",exp->val.boolE);
            break;
        case binopK:
            printf("binop: %s\n",exp->val.binopE.operator);
            printf("left:  ");
            printEXP(exp->val.binopE.left);
            printf("right: ");
            printEXP(exp->val.binopE.right);
            break;
        case funK:
            printf("fun: %s\n",exp->val.funE.id);
            break;
    }
}

void printSYMBOLTABLE(SYMBOLTABLE* st)
{
    SYMBOLNODE* currentNode = st->symbols;
    while(currentNode != NULL)
    {
        printf("VARIABLE IN TABLE: %s\n",currentNode->current->name);
        currentNode = currentNode->next;
    }
}

void printIC(LL* iCode)
{
    LLN* node = iCode->first;
    while(node != NULL)
    {
        printOP(node->ins->op);
        node = node->next;
    }
}

void printOP(OP* op)
{
    printf("opKind: %d   ",op->opK);
    if(op->opK==meta)
        printf("META: %d",op->metaK);
    printf("\n");
}

void printTarget(Target* t)
{
    printf("TARGETK: %d\n",t->targetK);
}

void printARG(ARG* arg)
{
    if(arg->mode->mode == ind)
        printf("IND\n");
    if(arg->mode->mode == irl)
        printf("IRL\n");
    printTarget(arg->target);
    printf("\n");
}

void printINS(INS* ins)
{
    printf("OPKIND: %d\n",ins->op->opK);
    printf("OPSIZE: %d\n",ins->op->size);
    if(ins->args[0])
    {
        printf("ARG0: \n");
        printARG(ins->args[0]);
    }
    if(ins->args[1])
    {
        printf("ARG1: \n");
        printARG(ins->args[1]);
    }
}