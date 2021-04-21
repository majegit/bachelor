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

void printIC(LL* iCode)
{
    while(iCode->first->next != NULL)
    {
        printOP(iCode->first->ins->op);
        iCode->first = iCode->first->next;
    }
}

void printOP(OP* op)
{
    if(op->opK==meta)
    {
        printf("META: %d\n",op->metaK);
    }
    else
    {
        printf("%d\n",op->opK);
    }
}