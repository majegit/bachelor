#include <stdio.h>
#include "TypeChecking.h"

typedef struct some {
    char* type
    char** children;
} some;

TypeNode* ROOT = (TypeNode*)malloc(sizeof(TypeNode));

TypeNode* DOUBLE = (TypeNode*)malloc(sizeof(TypeNode));
DOUBLE->parent = ROOT;

TypeNode* INT = (TypeNode*)malloc(sizeof(TypeNode));
INT->parent = DOUBLE;

TypeNode* CHAR = (TypeNode*)malloc(sizeof(TypeNode));
CHAR->parent = INT;

TypeNode* BOOL = (TypeNode*)malloc(sizeof(TypeNode));
BOOL->parent = INT;

char* mostGeneralType(char* type1 , char* type2)
{
    if(strcmp(type1,type2) == 0)
        return type1;
    if(type1.hasParent())


    return
}

['+',[],[]]




void TypeChecking(PROGRAM* p)
{


}

