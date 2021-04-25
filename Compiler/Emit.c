#include <stdio.h>
#include "IntermediateCodeGeneration.h"
#include "Emit.h"

const char* raxVariants[] = {"%al","%eax","%rax"};
const char* rbpVariants[] = {"%bpl","%ebp","%rbp"};
const char* rdiVariants[] = {"%dil","%edi","%rdi"};

const char* sizeModifier[] = {"b","l","q"};

const char* program_prologue = ".section .data\n.section .text\n.global _start\n_start:\n";
const char* program_epilogue = "";
const char* main_callee_save = "";
const char* main_callee_restore = "";
const char* callee_prologue = "";
const char* callee_save = "";
const char* callee_restore = "";
const char* callee_epilogue = "ret\n";


char* asmCode = "";

void emit(LL* code, const char* outputFileName)
{
    LLN* node = code->first;
    while(node != NULL)
    {
        char* newAsmCode = convertInsToAsm(node->ins);
        asmCode = concatStr(asmCode,newAsmCode);
        node = node->next;
    }

    printf("\n---ASMCODE BELOW---\n\n%s",asmCode);

    //Print the asmcode to a file
    FILE* fp = fopen(outputFileName,"w");
    fputs(asmCode,fp);
    fclose(fp);
}

char* convertInsToAsm(INS* ins)
{
    char* res;
    switch(ins->op->opK)
    {
        case move:
        {
            res = "mov";
            res = concatStr(res,sizeModifier[ins->op->size]);
            res = concatStr(res," ");
            res = concatStr(res, convertTarget(ins->args[0]->target,ins->op->size));
            res = concatStr(res, ", ");
            res = concatStr(res, convertTarget(ins->args[1]->target,ins->op->size));
            res = concatStr(res, "\n");
            break;
        }
        case push:
        {
            res = "push ";
            res = concatStr(res,convertTarget(ins->args[0]->target,ins->op->size));
            res = concatStr(res,"\n");
            break;
        }
        case pop:
        {
            res = "pop ";
            res = concatStr(res,convertTarget(ins->args[0]->target,ins->op->size));
            res = concatStr(res,"\n");
            break;
        }
        case add:
        {
            res = "add";
            res = concatStr(res,sizeModifier[ins->op->size]);
            res = concatStr(res," ");
            res = concatStr(res, convertTarget(ins->args[0]->target,ins->op->size));
            res = concatStr(res, ", ");
            res = concatStr(res, convertTarget(ins->args[1]->target,ins->op->size));
            res = concatStr(res, "\n");
            break;
        }
        case sub:
        case mul:
        case divi:
            res = "debugDIVI\n";
            break;
        case call:
        {
            res = "call ";
            res = concatStr(res,ins->args[0]->target->labelName);
            res = concatStr(res,"\n");
            break;
        }
        case meta:
        {
            res = convertMetaIns(ins);
            break;
        }
        case label:
        {
            res = concatStr(ins->args[0]->target->labelName,":\n");
            break;
        }
        default:
            res = "debugINS\n";
            break;
    }
    return res;
}

char* convertMetaIns(INS* ins)
{
    char* res;
    if(ins->op->metaK == PROGRAM_PROLOGUE)
        return program_prologue;
    if(ins->op->metaK == PROGRAM_EPILOGUE)
        return program_epilogue;
    if(ins->op->metaK == MAIN_CALLEE_SAVE)
        return main_callee_save;
    if(ins->op->metaK == MAIN_CALLEE_RESTORE)
        return main_callee_restore;
    if(ins->op->metaK == FUNCTION_DECLARATION)
        return meta_function_declaration(ins);
    if(ins->op->metaK == ALLOCATE_STACK_SPACE)
    {
        char intAsString[20];
        sprintf(intAsString,"%d",ins->op->metaInformation);
        res = "push %rbp\naddq $";
        res = concatStr(res,intAsString);
        res = concatStr(res,", %rsp\n");
        return res;
    }
    if(ins->op->metaK == DEALLOCATE_STACK_SPACE)
    {
        char intAsString[20];
        sprintf(intAsString,"%d",ins->op->metaInformation);
        res = "subq $";
        res = concatStr(res,intAsString);
        res = concatStr(res,"\npop %rbp\n");
        return res;
    }
    if(ins->op->metaK == CALLEE_PROLOGUE)
        return callee_prologue;
    if(ins->op->metaK == CALLEE_SAVE)
        return callee_save;
    if(ins->op->metaK == CALLEE_RESTORE)
        return callee_restore;
    if(ins->op->metaK == CALLEE_EPILOGUE)
        return callee_epilogue;
    printf("debugMETA: %d\n",ins->op->metaK);
    return "debugMETA\n";
}

char* meta_function_declaration(INS* ins)
{
    char* res;
    res = "\n.type ";
    res = concatStr(res,deepCopy(ins->op->metaString));
    res = concatStr(res,", @function\n");
    return res;
}

char* convertTarget(Target* t, opSize modifier)
{
    char* res;
    switch(t->targetK)
    {
        case imi:
        {
            res = "$";
            char intAsString[20];
            sprintf(intAsString,"%d",t->additionalInfo);
            res = concatStr(res,intAsString);
            break;
        }
        case mem:
        {
            res = t->labelName;
            break;
        }
        case rbp:
        {
            res = rbpVariants[modifier];
            break;
        }
        case rsp:
        {
            res = "%rsp";
            break;
        }
        case rrt:
        {
            res = raxVariants[modifier];
            break;
        }
        case rsl:
        {
            res = rdiVariants[modifier];
            break;
        }
        case reg:
        {
            if(t->additionalInfo == 1)
                res = "%rbx";
            else if(t->additionalInfo == 2)
                res = "%rcx";
            else
                res = "NOT_A_REG";
        }
    }
    return res;
}