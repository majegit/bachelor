#include <stdlib.h>
#include <stdio.h>
#include "Error.h"

void throwError(char* errorMsg)
{
    printf("Error: %s\n",errorMsg);
    exit(0);
}

void throwErrorLine(char* errorMsg, int lineno)
{
    printf("Error: %s on line: %d\n",errorMsg,lineno);
    exit(0);
}