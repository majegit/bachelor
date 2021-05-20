#ifndef __PEEPHOLE_H
#define __PEEPHOLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"
#include "IntermediateCodeGeneration.h"

void peepholeOptimize(LL* code);

int pattern0(LLN* previous, LLN** current);
int pattern1(LLN* previous, LLN** current);
int pattern2(LLN* previous, LLN** current);
int pattern3(LLN* previous, LLN** current);

#endif