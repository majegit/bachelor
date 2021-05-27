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
int pattern4(LLN* previous, LLN** current);
int pattern5(LLN* previous, LLN** current);
int pattern6(LLN* previous, LLN** current);

int equalModes(Mode* m0, Mode* m1);
int equalTargets(Target* t0, Target* t1);
int equalArgs(ARG* arg0, ARG* arg1);
int memRefs(ARG* src, ARG* dest);

#endif