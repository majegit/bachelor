#ifndef __Operations_c
#define __Operations_c
#include "TypeChecking.h"
#include <stdlib.h>
#include <string.h>
extern int lineno;

TYPE BOOL, CHAR, INT, DOUBLE;

TYPE BOOL = {"BOOLEAN",NULL,NULL};
TYPE CHAR = {"CHAR",NULL,NULL};
TYPE INT = {"INT",&DOUBLE,NULL};
TYPE DOUBLE = {"DOUBLE",NULL,&INT};

//Arithmetic operatorions
OPERATION op0 = { "+", 2, &INT,{&INT,&INT}};
OPERATION op1 = { "+", 2, &DOUBLE,{&DOUBLE,&DOUBLE}};
OPERATION op2 = { "-", 2, &INT,{&INT,&INT}};
OPERATION op3 = { "-", 2, &DOUBLE,{&DOUBLE,&DOUBLE}};
OPERATION op4 = { "*", 2, &INT,{&INT,&INT}};
OPERATION op5 = { "*", 2, &DOUBLE,{&DOUBLE,&DOUBLE}};
OPERATION op6 = { "/", 2, &INT,{&INT,&INT}};
OPERATION op7 = { "/", 2, &DOUBLE,{&DOUBLE,&DOUBLE}};

//Compare operations
OPERATION op8 = { "L", 2, &BOOL,{&INT,&INT}};
OPERATION op9 = { "L", 2, &BOOL,{&DOUBLE,&DOUBLE}};
OPERATION op10 = { "G", 2, &BOOL,{&INT,&INT}};
OPERATION op11 = { "G", 2, &BOOL,{&DOUBLE,&DOUBLE}};
OPERATION op12 = { "LEQ", 2, &BOOL,{&INT,&INT}};
OPERATION op13 = { "LEQ", 2, &BOOL,{&DOUBLE,&DOUBLE}};
OPERATION op14 = { "GEQ", 2, &BOOL,{&INT,&INT}};
OPERATION op15 = { "GEQ", 2, &BOOL,{&DOUBLE,&DOUBLE}};
OPERATION op16 = { "EQ", 2, &BOOL,{&INT,&INT}};
OPERATION op17 = { "EQ", 2, &BOOL,{&DOUBLE,&DOUBLE}};
OPERATION op18 = { "EQ", 2, &BOOL,{&CHAR,&CHAR}};
OPERATION op19 = { "EQ", 2, &BOOL,{&BOOL,&BOOL}};
OPERATION op20 = { "NEQ", 2, &BOOL,{&INT,&INT}};
OPERATION op21 = { "NEQ", 2, &BOOL,{&DOUBLE,&DOUBLE}};
OPERATION op22 = { "EQ", 2, &BOOL,{&CHAR,&CHAR}};
OPERATION op23 = { "EQ", 2, &BOOL,{&BOOL,&BOOL}};

//Boolean operations
OPERATION op24 = { "AND", 2, &BOOL,{&BOOL,&BOOL}};
OPERATION op25 = { "OR", 2, &BOOL,{&BOOL,&BOOL}};

OPERATION* ALL_OPS[] = { &op0, &op1, &op2, &op3, &op4, &op5, &op6, &op7, &op8, &op9, &op10, &op11, &op12, &op13,
                         &op14, &op15, &op16, &op17, &op18, &op19, &op20, &op21, &op22, &op23, &op24, &op25};

const int operations = sizeof(ALL_OPS)/sizeof(OPERATION*);

TYPE* stringToType(char* type)
{
    if(strcmp(type,"INT") == 0)
        return &INT;
    if(strcmp(type,"DOUBLE") == 0 )
        return &DOUBLE;
    if(strcmp(type,"BOOLEAN") == 0)
        return &BOOL;
    if(strcmp(type,"CHAR") == 0)
        return &CHAR;
    return NULL;
}

int coercionCount(TYPE* child, TYPE* parent)
{
    int coercionCount = 0;
    while(child != NULL)
    {
        if(child == parent)
            return coercionCount;
        coercionCount++;
        child = child->up;
    }
    return -1;
}

int isSubtype(TYPE* child, TYPE* parent)
{
    if(coercionCount(child, parent) >= 0)
        return 1;
    return 0;
}

int perfectMatch(OPERATION* operation, char* op, TYPE* left, TYPE* right)
{
    return strcmp(operation->operator,op) == 0 && left == operation->argTypes[0] && right == operation->argTypes[1];
}

int coercionMatch(OPERATION* operation, char* op, TYPE* left, TYPE* right)
{
    if(strcmp(operation->operator,op) != 0)
        return -1;
    int coercionCountLeft = coercionCount(left,operation->argTypes[0]);
    int coercionCountRight = coercionCount(right,operation->argTypes[1]);
    if(coercionCountLeft < 0 || coercionCountRight < 0)
        return -1;
    return coercionCountLeft + coercionCountRight;
}


OPERATION_WRAPPER* searchOperations(char* op, char* typeLeft, char* typeRight)
{
    TYPE* left = stringToType(typeLeft);
    TYPE* right = stringToType(typeRight);
    OPERATION* operation = NULL;
    OPERATION_WRAPPER* operationWrapper = (OPERATION_WRAPPER*)malloc(sizeof(OPERATION_WRAPPER));
    operationWrapper->opCount = 0;
    operationWrapper->op = NULL;

    int opCounter = 0;
    int leastCoercion = -1;
    for(int i = 0; i < operations; i++)
    {
        if(perfectMatch(ALL_OPS[i], op, left, right)) //Perfect match, no coercion required
        {
            operationWrapper->opCount = 1;
            operationWrapper->op = ALL_OPS[i];
            return operationWrapper;
        }
        int coercionCount = coercionMatch(ALL_OPS[i], op, left, right);
        if(coercionCount != -1)
        {
            if(coercionCount == leastCoercion)
                opCounter++;
            else if(coercionCount < leastCoercion || leastCoercion == -1)
            {
                operation = ALL_OPS[i];
                leastCoercion = coercionCount;
                opCounter = 1;
            }
        }
    }
    operationWrapper->opCount = opCounter;
    operationWrapper->op = operation;
    return operationWrapper;
}



#endif