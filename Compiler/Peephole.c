#include "Peephole.h"
#include "Emit.h"
#include <stdio.h>

const int pattern_count = 7;
int (*patterns[7])(LLN*,LLN**) = {pattern0,pattern1,pattern2,pattern3,pattern4,pattern5,pattern6};


void peepholeOptimize(LL* code)
{
    LLN* previous;
    LLN* current;
    int change = 1;
    while(change)
    {
        change = 0;
        previous = NULL;
        current = code->first;
        while(current != NULL)
        {
            for(int i = 4; i<pattern_count; ++i)
            {
                change |= (*patterns[i])(previous,&current);
                if(current == NULL)
                    break; //Break out of for loop
            }
            previous = current;
            if(current)
                current = current->next;
        }
    }
}

//TEMPLATE:
//PUSH<suffix> <OP0>
//POP<suffix> <OP1>
//
//RESULT:
//MOV<suffix> <OP0> <OP1>
int pattern0(LLN* previous, LLN** current)
{
    LLN* c = *current;
    if(c->ins->op->opK == push && c->next != NULL && c->next->ins->op->opK == pop &&
    c->ins->op->size == c->next->ins->op->size &&
    memRefs(c->ins->args[0],c->next->ins->args[0]) <= 1)
    {
        INS* ins0 = c->ins;
        INS* ins1 = c->next->ins;
        OP* op = makeOP(move, ins0->op->size);
        ARG* a0 = ins0->args[0];
        ARG* a1 = ins1->args[0];
        ARG* args[2] = {a0,a1};
        INS* newINS = makeINS(op,args);
        LLN* newLLN = makeLLN(newINS);
        newLLN->next = (*current)->next->next;
        *current = newLLN;
        previous->next = newLLN;
        return 1;
    }
    return 0;
}

//TEMPLATE:
//MOVQ RBP, RSL
//MOV<suffix> <offset>(RSL), <TARGET1>
//
//RESULT:
//MOV<suffix> <offset>(RBP), <TARGET1>
int pattern1(LLN* previous, LLN** current)
{
    LLN* c = *current;
    if(!c->next)
        return 0;
    INS* ins0 = c->ins;
    INS* ins1 = c->next->ins;

    if (ins0->op->opK == move &&
        ins0->op->size == bits_64 &&
        ins0->args[0] != NULL &&
        ins0->args[0]->target->targetK == rbp &&
        ins0->args[0]->mode->mode == dir &&
        ins0->args[1] != NULL &&
        ins0->args[1]->target->targetK == rsl &&
        ins0->args[1]->mode->mode == dir &&
        ins1->op->opK == move &&
        ins1->args[0] != NULL &&
        ins1->args[0]->target->targetK == rsl &&
        ins1->args[0]->mode->mode == irl &&
        ins1->args[1] != NULL &&
        ins1->args[1]->mode->mode == dir)
    {
        printf("1\n");
        OP* op = makeOP(move, ins1->op->size);
        Target* src = makeTarget(rbp);
        ARG* srcA = makeARG(src,makeModeIRL(ins1->args[0]->mode->offset));
        Target* dest = makeTarget(ins1->args[1]->target->targetK);
        dest->additionalInfo = ins1->args[1]->target->additionalInfo;
        ARG* destA = makeARG(dest,makeMode(dir));
        ARG* args[2] = {srcA,destA};
        INS* newINS = makeINS(op,args);
        LLN* newLLN = makeLLN(newINS);
        previous->next = newLLN;
        newLLN->next = (*current)->next->next;
        *current = newLLN;
        return 1;
    }
    return 0;
}

//TEMPLATE:
//MOVQ RBP, RSL
//MOV<suffix> <TARGET1>, <offset>(RSL)
//
//RESULT:
//MOV<suffix> <TARGET1>, <offset>(RBP)
int pattern2(LLN* previous, LLN** current)
{
    LLN* c = *current;
    if(!c->next)
        return 0;
    INS* ins0 = c->ins;
    INS* ins1 = c->next->ins;
    if (ins0->op->opK == move &&
        ins0->op->size == bits_64 &&
        ins0->args[0] != NULL &&
        ins0->args[0]->target->targetK == rbp &&
        ins0->args[0]->mode->mode == dir &&
        ins0->args[1] != NULL &&
        ins0->args[1]->target->targetK == rsl &&
        ins0->args[1]->mode->mode == dir &&
        ins1->op->opK == move &&
        ins1->args[0] != NULL &&
        ins1->args[1] != NULL &&
        ins1->args[1]->target->targetK == rsl &&
        ins1->args[1]->mode->mode == irl)
    {
        OP* op = makeOP(move, ins1->op->size);
        Target* src = makeTarget(ins1->args[0]->target->targetK);
        src->additionalInfo = ins1->args[0]->target->additionalInfo;
        ARG* srcA = makeARG(src,ins1->args[0]->mode);
        Target* dest = makeTarget(rbp);
        ARG* destA = makeARG(dest,makeModeIRL(ins1->args[1]->mode->offset));
        ARG* args[2] = {srcA,destA};
        INS* newINS = makeINS(op,args);
        LLN* newLLN = makeLLN(newINS);
        previous->next = newLLN;
        newLLN->next = (*current)->next->next;
        *current = newLLN;
        return 1;
    }
    return 0;
}

//TEMPLATE:
//ADDQ $0, <OP0>
//
//RESULT:
//
int pattern3(LLN* previous, LLN** current)
{
    INS* ins = (*current)->ins;
    if(ins->op->opK == add && ins->args[0] != NULL && ins->args[0]->target->targetK == imi && ins->args[0]->target->additionalInfo == 0)
    {
        previous->next = (*current)->next;
        *current = NULL;
        return 1;
    }
    return 0;
}

//TEMPLATE:
//MOVQ RBP, RSL
//MOV<suffix> <ARG0>, <offset>(RSL)
//
//RESULT:
//MOV<suffix> <ARG0>, <offset>(RBP)
int pattern4(LLN* previous, LLN** current)
{
    INS* ins = (*current)->ins;
    if((*current)->next == NULL)
        return 0;
    INS* next = (*current)->next->ins;
    if(ins->op->opK == move &&
    ins->op->size == bits_64 &&
    ins->args[0] != NULL &&
    ins->args[0]->target->targetK == rbp &&
    ins->args[0]->mode->mode == dir &&
    ins->args[1] != NULL &&
    ins->args[1]->target->targetK == rsl &&
    ins->args[1]->mode->mode == dir &&
    next->args[0] != NULL &&
    next->args[1] != NULL &&
    next->args[1]->target->targetK == rsl &&
    next->args[1]->mode->mode == irl)
    {

        OP* op = next->op;
        ARG* srcA = next->args[0];

        Target* dest = makeTarget(rbp);
        ARG* destA = makeARG(dest,next->args[1]->mode);

        ARG* args[2] = {srcA,destA};
        LLN* newNode = makeLLN(makeINS(op,args));
        newNode->next = (*current)->next->next;
        previous->next = newNode;
        *current = newNode;
        return 1;
    }
    return 0;
}

//TEMPLATE:
//MOVQ RBP, RSL
//MOV<suffix> <offset>(RSL), <ARG0>
//
//RESULT:
//MOV<suffix> <offset>(RBP), <ARG0>
int pattern5(LLN* previous, LLN** current)
{
    INS* ins = (*current)->ins;
    if((*current)->next == NULL)
        return 0;

    INS* next = (*current)->next->ins;

    if(ins->op->opK == move &&
       ins->op->size == bits_64 &&
       ins->args[0] != NULL &&
       ins->args[0]->target->targetK == rbp &&
       ins->args[0]->mode->mode == dir &&
       ins->args[1] != NULL &&
       ins->args[1]->target->targetK == rsl &&
       ins->args[1]->mode->mode == dir &&
       next->args[0] != NULL &&
       next->args[1] != NULL &&
       next->args[0]->target->targetK == rsl &&
       next->args[0]->mode->mode == irl)
    {

        OP* op = next->op;

        Target* src = makeTarget(rbp);
        ARG* srcA = makeARG(src,next->args[0]->mode);

        ARG* destA = next->args[1];

        ARG* args[2] = {srcA,destA};
        LLN* newNode = makeLLN(makeINS(op,args));
        newNode->next = (*current)->next->next;
        previous->next = newNode;
        *current = newNode;
        return 1;
    }
    return 0;
}


//TEMPLATE:
//MOV<suffix> <REG0> <REG0>
//
//RESULT:
//
int pattern6(LLN* previous, LLN** current)
{
    INS* ins = (*current)->ins;
    if(ins->op->opK == move &&
    equalArgs(ins->args[0],ins->args[1]))
    {
        previous->next = previous->next->next;
        (*current) = NULL;
        return 1;
    }
    return 0;
}

int equalModes(Mode* m0, Mode* m1)
{
    if(m0->mode == m1->mode)
    {
        if(m0->mode == irl && m0->offset != m1->offset)
            return 0;
        return 1;
    }

    return 0;
}

int equalLabels(char* str0, char* str1)
{
    if(str0 == NULL && str1 == NULL)
        return 1;
    if(str0 == NULL || str1 == NULL)
        return 0;
    if(strcmp(str0,str1) == 0)
        return 1;
    return 0;
}

int equalTargets(Target* t0, Target* t1)
{
    if(t0 == NULL && t1 == NULL)
        return 1;
    if(t0 == NULL || t1 == NULL)
        return 0;
    if(t0->targetK == t1->targetK
        && t0->additionalInfo == t1->additionalInfo
        && equalLabels(t0->labelName,t1->labelName)
        && t0->labelK == t1->labelK)
        return 1;
    return 0;
}

int equalArgs(ARG* arg0, ARG* arg1)
{
    if(arg0 == NULL && arg1 == NULL)
        return 1;
    if(arg0 == NULL || arg1 == NULL)
        return 0;
    if(equalTargets(arg0->target,arg1->target) && equalModes(arg0->mode,arg1->mode))
        return 1;
    return 0;
}

int memRefs(ARG* src, ARG* dest)
{
    int references = 0;
    if(src != NULL)
        if(src->target->targetK == mem || src->mode->mode == ind || src->mode->mode == irl)
            references++;
    if(dest != NULL)
        if(dest->target->targetK == mem || dest->mode->mode == ind || dest->mode->mode == irl)
            references++;
    return references;
}
