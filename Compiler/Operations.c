#ifndef __Operations_c
#define __Operations_c
#include "TypeChecking.h"
#include <stdlib.h>
#include <string.h>

SUBTYPE BOOL, CHAR, INT, DOUBLE;

SUBTYPE BOOL = {"BOOLEAN",NULL,NULL};
SUBTYPE CHAR = {"CHAR",NULL,NULL};
SUBTYPE INT = {"INT",&DOUBLE,NULL};
SUBTYPE DOUBLE = {"DOUBLE",NULL,&INT};

TYPESYSTEM ts = {{&BOOL,&CHAR,&DOUBLE}};

OPERATION op0 = { "+", 2, "INT",{"INT","INT"}};
OPERATION op1 = { "+", 2, "DOUBLE",{"DOUBLE","DOUBLE"}};
OPERATION op2 = { "-", 2, "INT",{"INT","INT"}};
OPERATION op3 = { "-", 2, "DOUBLE",{"DOUBLE","DOUBLE"}};
OPERATION op4 = { "*", 2, "INT",{"INT","INT"}};
OPERATION op5 = { "*", 2, "DOUBLE",{"DOUBLE","DOUBLE"}};
OPERATION op6 = { "/", 2, "INT",{"INT","INT"}};
OPERATION op7 = { "/", 2, "DOUBLE",{"DOUBLE","DOUBLE"}};

OPERATION op8 = { "L", 2, "BOOLEAN",{"INT","INT"}};
OPERATION op9 = { "L", 2, "BOOLEAN",{"DOUBLE","DOUBLE"}};
OPERATION op10 = { "G", 2, "BOOLEAN",{"INT","INT"}};
OPERATION op11 = { "G", 2, "BOOLEAN",{"DOUBLE","DOUBLE"}};
OPERATION op12 = { "LEQ", 2, "BOOLEAN",{"INT","INT"}};
OPERATION op13 = { "LEQ", 2, "BOOLEAN",{"DOUBLE","DOUBLE"}};
OPERATION op14 = { "GEQ", 2, "BOOLEAN",{"INT","INT"}};
OPERATION op15 = { "GEQ", 2, "BOOLEAN",{"DOUBLE","DOUBLE"}};
OPERATION op16 = { "EQ", 2, "BOOLEAN",{"INT","INT"}};
OPERATION op17 = { "EQ", 2, "BOOLEAN",{"DOUBLE","DOUBLE"}};
OPERATION op18 = { "EQ", 2, "BOOLEAN",{"CHAR","CHAR"}};
OPERATION op19 = { "EQ", 2, "BOOLEAN",{"BOOLEAN","BOOLEAN"}};
OPERATION op20 = { "NEQ", 2, "BOOLEAN",{"INT","INT"}};
OPERATION op21 = { "NEQ", 2, "BOOLEAN",{"DOUBLE","DOUBLE"}};
OPERATION op22 = { "EQ", 2, "BOOLEAN",{"CHAR","CHAR"}};
OPERATION op23 = { "EQ", 2, "BOOLEAN",{"BOOLEAN","BOOLEAN"}};

OPERATION op24 = { "AND", 2, "BOOLEAN",{"BOOLEAN","BOOLEAN"}};
OPERATION op25 = { "OR", 2, "BOOLEAN",{"BOOLEAN","BOOLEAN"}};

OPERATION op26 = { "+", 2, "CHAR",{"CHAR","INT"}};


OPERATION* ALL_OPS[] = { &op0, &op1, &op2, &op3, &op4, &op5, &op6, &op7, &op8, &op9, &op10, &op11, &op12, &op13,
                         &op14, &op15, &op16, &op17, &op18, &op19, &op20, &op21, &op22, &op23, &op24, &op25};

const int ops = sizeof(ALL_OPS) / sizeof(OPERATION*);

SUBTYPE* getSubtype(char* type)
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

OPERATION* coerceRight(char* typeLeft, char* typeRight, OPERATION* op)
{
    if(strcmp(op->argTypes[0], typeLeft) == 0 && strcmp(op->argTypes[1], typeRight) == 0)
        return op;
    SUBTYPE* parent = getSubtype(typeRight)->up;
    if(parent == NULL)
        return NULL;
    return coerceRight(typeLeft, parent->type, op);
}

OPERATION* coerceLeft(char* typeLeft, char* typeRight, OPERATION* op)
{
    if(strcmp(op->argTypes[0], typeLeft) == 0 && strcmp(op->argTypes[1], typeRight) == 0)
        return op;
    if(strcmp(op->argTypes[0], typeLeft) != 0) //Leftside argument is wrong
    {
        SUBTYPE* parent = getSubtype(typeLeft)->up;
        if(parent != NULL)
            return coerceLeft(parent->type,typeRight,op);
    } else
    {
        return coerceRight(typeLeft,typeRight,op);
    }
}

OPERATION* searchOperations(char* op, char* typeLeft, char* typeRight)
{
    for(int i = 0; i < ops; i++)
    {
        if(strcmp(ALL_OPS[i]->operator, op) == 0)
        {
            if(coerceLeft(typeLeft, typeRight, ALL_OPS[i]) != NULL)
                return ALL_OPS[i];
        }
    }
    return NULL;
}



#endif