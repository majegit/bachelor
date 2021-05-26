#include "Peephole.h"
#include "DebugUtils.h"

const int pattern_count = 4;
int (*patterns[4])(LLN*,LLN**) = {pattern0,pattern1,pattern2,pattern3};

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
            for(int i = 0; i<pattern_count; ++i)
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
    if(c->ins->op->opK == push && c->next != NULL && c->next->ins->op->opK == pop)
    {
        printf("0\n");
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
        printf("2\n");
        OP* op = makeOP(move, ins1->op->size);
        Target* src = makeTarget(ins1->args[0]->target->targetK);
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
    if(ins->op != NULL && ins->op->opK == add && ins->args[0] != NULL && ins->args[0]->target->targetK == imi && ins->args[0]->target->additionalInfo == 0)
    {
        printf("3\n");
        previous->next = (*current)->next;
        *current = NULL;
        return 1;
    }
    return 0;
}

int equalModes(Mode* m0, Mode* m1)
{
    if(m0->mode == m1->mode && m0->offset == m1->offset)
        return 1;
    return 0;
}

int equalTargets(Target* t0, Target* t1)
{
    if(t0->targetK == t1->targetK
        && t0->additionalInfo == t1->additionalInfo
        && strcmp(t0->labelName,t1->labelName) == 0
        && t0->labelK == t1->labelK)
        return 1;
    return 0;
}

int equalArgs(ARG* arg0, ARG* arg1)
{
    if(equalTargets(arg0->target,arg1->target) && equalModes(arg0->mode,arg1->mode))
        return 1;
    return 0;
}
