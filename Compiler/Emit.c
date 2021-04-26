#include <stdio.h>
#include <stdlib.h>
#include "IntermediateCodeGeneration.h"
#include "Emit.h"


const char* indentation = "    ";

const char* raxVariants[] = {"%al","%eax","%rax"};
const char* rbxVariants[] = {"%bl","%ebl","%rbx"};
const char* rcxVariants[] = {"%cl","%ecl","%rcx"};
const char* rbpVariants[] = {"%bpl","%ebp","%rbp"};
const char* rdiVariants[] = {"%dil","%edi","%rdi"};
const char* rspVariants[] = {"%sl", "%esl","%rsp"};

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
    int i = 0;
    while(node != NULL)
    {
        char* newAsmCode = convertInsToAsm(node->ins);
        asmCode = concatStrFreeFree(asmCode,newAsmCode);
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
    char* res = "";
    switch(ins->op->opK)
    {
        case move:
        {
            res = concatStr(res,indentation);
            res = concatStrFree(res,"mov");
            res = concatStrFree(res,sizeModifier[ins->op->size]);
            res = concatStrFree(res," ");
            res = concatStrFreeFree(res, convertTarget(ins->args[0]->target,ins->args[0]->mode));
            res = concatStrFree(res, ", ");
            res = concatStrFreeFree(res, convertTarget(ins->args[1]->target,ins->args[1]->mode));
            res = concatStrFree(res, "\n");
            break;
        }
        case push:
        {
            res = concatStr(res,indentation);
            res = concatStrFree(res,"push ");
            res = concatStrFreeFree(res,convertTarget(ins->args[0]->target,ins->args[0]->mode));
            res = concatStrFree(res,"\n");
            break;
        }
        case pop:
        {
            res = concatStr(res,indentation);
            res = concatStrFree(res,"pop ");
            res = concatStrFreeFree(res,convertTarget(ins->args[0]->target,ins->args[0]->mode));
            res = concatStrFree(res,"\n");
            break;
        }
        case add:
        {
            res = concatStr(res,indentation);
            res = concatStrFree(res,"add");
            res = concatStrFree(res,sizeModifier[ins->op->size]);
            res = concatStrFree(res," ");
            res = concatStrFreeFree(res, convertTarget(ins->args[0]->target,ins->args[0]->mode));
            res = concatStrFree(res, ", ");
            res = concatStrFreeFree(res, convertTarget(ins->args[1]->target,ins->args[1]->mode));
            res = concatStrFree(res, "\n");
            break;
        }
        case sub:
        case mul:
        case divi:
            res = "debugDIVI\n";
            break;
        case call:
        {
            res = concatStr(res,indentation);
            res = concatStrFree(res,"call ");
            res = concatStrFree(res,ins->args[0]->target->labelName);
            res = concatStrFree(res,"\n");
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
        return deepCopy(program_prologue);
    if(ins->op->metaK == PROGRAM_EPILOGUE)
        return deepCopy(program_epilogue);
    if(ins->op->metaK == MAIN_CALLEE_SAVE)
        return deepCopy(main_callee_save);
    if(ins->op->metaK == MAIN_CALLEE_RESTORE)
        return deepCopy(main_callee_restore);
    if(ins->op->metaK == FUNCTION_DECLARATION)
        return meta_function_declaration(ins);
    if(ins->op->metaK == ALLOCATE_STACK_SPACE)
    {
        char stackSpace[20];
        sprintf(stackSpace,"%d",ins->op->metaInformation);
        res = concatStr(indentation,"push %rbp\n");
        char* aux = concatStr(indentation,"addq $");
        res = concatStrFree(res,aux);
        free(aux);
        res = concatStrFree(res,stackSpace);
        res = concatStrFree(res,", %rsp\n");
        return res;
    }
    if(ins->op->metaK == DEALLOCATE_STACK_SPACE)
    {
        char stackSpace[20];
        sprintf(stackSpace,"%d",ins->op->metaInformation);
        res = concatStr(indentation,"subq $");
        res = concatStrFree(res,stackSpace);
        res = concatStrFree(res, ", %rsp");
        res = concatStrFree(res,"\n");
        char* aux = concatStr(indentation,"pop %rbp\n");
        res = concatStrFree(res,aux);
        free(aux);
        return res;
    }
    if(ins->op->metaK == CALLEE_PROLOGUE)
        return deepCopy(callee_prologue);
    if(ins->op->metaK == CALLEE_SAVE)
        return deepCopy(callee_save);
    if(ins->op->metaK == CALLEE_RESTORE)
        return deepCopy(callee_restore);
    if(ins->op->metaK == CALLEE_EPILOGUE)
        return concatStr(indentation,callee_epilogue);
    printf("debugMETA: %d\n",ins->op->metaK);
    return deepCopy("debugMETA\n");
}

char* meta_function_declaration(INS* ins)
{
    char* res = "\n.type ";
    res = concatStrFree(res,ins->op->metaString);
    res = concatStrFree(res,", @function\n");
    return res;
}

char* convertTarget(Target* t, Mode* m)
{
    char* res = "";
    opSize modifier = t->size;
    switch(t->targetK)
    {
        case imi:
        {
            char intString[20];
            sprintf(intString,"%d",t->additionalInfo);
            res = "$";
            res = concatStr(res,intString);
            break;
        }
        case mem:
        {
            res = deepCopy(t->labelName);
            break;
        }
        case rbp:
        {
            printf("In here with mod: %d\n",modifier);
            res = deepCopy(rbpVariants[modifier]);
            break;
        }
        case rsp:
        {
            res = deepCopy(rspVariants[modifier]);
            break;
        }
        case rrt:
        {
            res = deepCopy(raxVariants[modifier]);
            break;
        }
        case rsl:
        {
            res = deepCopy(rdiVariants[modifier]);
            break;
        }
        case reg:
        {
            if(t->additionalInfo == 1)
                res = deepCopy("%rbx");
            else if(t->additionalInfo == 2)
                res = deepCopy("%rcx");
            else
                res = deepCopy("NOT_A_REG");
        }
    }
    if(m->mode == dir)
        return res;
    if(m->mode == ind)
    {
        res = concatStrFreeFree("(",res);
        res = concatStrFree(res,")");
        return res;
    }
    if(m->mode == irl)
    {
        char offset[20];
        sprintf(offset,"%d",m->offset);
        res = concatStrFree("(",res);
        res = concatStrFree(res,")");
        char* aux = concatStr(offset,res);
        free(res);
        res = aux;
        return res;
    }
    return deepCopy("debug!!\n");
}