#include "Peephole.h"

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
            current = current->next;
        }
    }
}

//TEMPLATE:
//PUSH <OP0>
//POP <OP1>
//
//RESULT:
//MOVE <OP0> <OP1>
int pattern0(LLN* previous, LLN** current)
{
    LLN* c = *current;
    if(c->ins->op->opK == push && c->next != NULL && c->next->ins->op->opK == pop)
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
//MOVQ %RBP, %RSL
//MOV<suffix> <offset>(%RSL), <TARGET1>
//
//RESULT:
//MOV<suffix> <offset>(%RBP), <TARGET1>
int pattern1(LLN* previous, LLN** current)
{
    return 0;
}



//TEMPLATE:
//ADDQ $0, <OP0>
//
//RESULT:
//
int pattern2(LLN* previous, LLN** current)
{
    INS* ins = (*current)->ins;
    if(ins->op != NULL && ins->op->opK == add && ins->args[0] != NULL && ins->args[0]->target->targetK == imi && ins->args[0]->target->additionalInfo == 0)
    {
        printf("In pattern2\n");
        previous->next = (*current)->next;
        current = NULL;
        return 1;
    }
    return 0;
}

/* DESCRIPTION:
 * When calling the meta operation DEALLOCATE_ARGUMENTS on functions
 * with no arguments, then it results in addq $0, %rsp. This useless
 * instruction can be removed.
 */
int pattern3(LLN* previous, LLN** current)
{
    INS* ins = (*current)->ins;
    if(ins->op->metaK == DEALLOCATE_ARGUMENTS && ins->op->metaInt == 0)
    {
        previous->next = (*current)->next;
        current = NULL;
        return 1;
    }
    return 0;
}
