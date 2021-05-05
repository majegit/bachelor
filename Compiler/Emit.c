#include <stdio.h>
#include <stdlib.h>
#include "IntermediateCodeGeneration.h"
#include "Emit.h"

const char* indentation = "    ";

const char* raxVariants[] = {"%al","%eax","%rax"};
const char* rbxVariants[] = {"%bl","%ebx","%rbx"};
const char* rcxVariants[] = {"%cl","%ecx","%rcx"};
const char* rbpVariants[] = {"%bpl","%ebp","%rbp"};
const char* rdiVariants[] = {"%dil","%edi","%rdi"};
const char* rspVariants[] = {"%sl", "%esl","%rsp"};

const char* sizeModifier[]  = {"b","l","q"};
const char* sizeModifier2[] = {"1","4","8"};

const char* program_prologue = ".section .data\n.section .text\n.global _start\n_start:\n";
const char* program_epilogue = "    movq %rax, %rdi\n    movq $60, %rax\n    syscall\n\n";
const char* main_callee_save = "";
const char* main_callee_restore = "";
const char* callee_prologue = "";
const char* callee_save = "";
const char* callee_restore = "";
const char* callee_epilogue = "ret\n";
const char* follow_static_link = "movq (%rdi), %rdi\n";


char* asmCode = "";

void emit(LL* code, const char* outputFileName)
{
    //Print the asmcode to a file
    FILE* fp = fopen(outputFileName,"w");

    LLN* node = code->first;
    int i = 0;
    while(node != NULL)
    {
        char* newAsmCode = convertInsToAsm(node->ins);
        asmCode = concatStrFreeFree(asmCode,newAsmCode);
        //printf("CURRENT ASMCODE:\n%s\n",asmCode);
        node = node->next;
    }
    if(code->pFlagBOOLEAN)
        asmCode = concatStrFree(asmCode,printBOOLEAN);
    if(code->pFlagCHAR)
        asmCode = concatStrFree(asmCode,printCHAR);
    if(code->pFlagINT)
        asmCode = concatStrFree(asmCode,printINT);
    if(code->pFlagDOUBLE)
        asmCode = concatStrFree(asmCode,"DOUBLE PRINT DEBUG\n");

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
            res = concatStr(indentation, res);
            if(ins->op->size == bits_64)
            {
                res = concatStrFree(res,"push ");
                res = concatStrFreeFree(res,convertTarget(ins->args[0]->target,ins->args[0]->mode));
                res = concatStrFree(res,"\n");
            }
            else
            {
                res = concatStrFree(res, "subq $");
                res = concatStrFree(res, sizeModifier2[ins->op->size]);
                res = concatStrFree(res, ", %rsp\n");
                res = concatStrFree(res, indentation);
                res = concatStrFree(res, "mov");
                res = concatStrFree(res, sizeModifier[ins->op->size]);
                res = concatStrFree(res, " ");
                res = concatStrFreeFree(res, convertTarget(ins->args[0]->target, ins->args[0]->mode));
                res = concatStrFree(res, ", ");
                res = concatStrFree(res,raxVariants[ins->op->size]);
                res = concatStrFree(res, "\n");
                res = concatStrFree(res, indentation);
                res = concatStrFree(res,"mov");
                res = concatStrFree(res,sizeModifier[ins->op->size]);
                res = concatStrFree(res, " ");
                res = concatStrFree(res,raxVariants[ins->op->size]);
                res = concatStrFree(res, ", (%rsp)\n");
            }
            break;
        }
        case pop:
        {
            res = concatStr(indentation, res);
            if(ins->op->size == bits_64)
            {
                res = concatStrFree(res,"pop ");
                res = concatStrFreeFree(res,convertTarget(ins->args[0]->target,ins->args[0]->mode));
                res = concatStrFree(res,"\n");
            }
            else
            {
                res = concatStrFree(res,"mov");
                res = concatStrFree(res, sizeModifier[ins->op->size]);
                res = concatStrFree(res, " (%rsp), ");
                res = concatStrFreeFree(res, convertTarget(ins->args[0]->target, ins->args[0]->mode));
                res = concatStrFree(res, "\n");
                res = concatStrFree(res, indentation);
                res = concatStrFree(res, "addq $");
                res = concatStrFree(res, sizeModifier2[ins->op->size]);
                res = concatStrFree(res, ", %rsp\n");
            }
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
        {
            res = concatStr(res,indentation);
            res = concatStrFree(res,"sub");
            res = concatStrFree(res,sizeModifier[ins->op->size]);
            res = concatStrFree(res," ");
            res = concatStrFreeFree(res, convertTarget(ins->args[0]->target,ins->args[0]->mode));
            res = concatStrFree(res, ", ");
            res = concatStrFreeFree(res, convertTarget(ins->args[1]->target,ins->args[1]->mode));
            res = concatStrFree(res, "\n");
            break;
        }
        case mul:
        {
            res = concatStr(indentation,res);
            res = concatStrFree(res,"imul ");
            res = concatStrFreeFree(res, convertTarget(ins->args[0]->target,ins->args[0]->mode));
            res = concatStrFree(res, ", ");
            res = concatStrFreeFree(res, convertTarget(ins->args[1]->target,ins->args[1]->mode));
            res = concatStrFree(res, "\n");
            break;
        }
        case divi:
            res = concatStr(res,indentation);
            res = concatStrFree(res,"mov");
            res = concatStrFree(res,sizeModifier[ins->args[1]->target->size]);
            res = concatStrFree(res," ");
            res = concatStrFree(res,convertTarget(ins->args[1]->target,ins->args[1]->mode));
            res = concatStrFree(res,", ");
            res = concatStrFree(res,raxVariants[ins->args[0]->target->size]);
            res = concatStrFree(res,"\n");
            if(ins->args[0]->target->size == bits_32) //Convert long (32bits) to quad (64bits)
            {
                res = concatStrFree(res, indentation);
                res = concatStrFree(res,"cltq\n");
                res = concatStrFree(res,indentation);
                res = concatStrFree(res,"movq %rax, %rdx\n");
                res = concatStrFree(res,indentation);
                res = concatStrFree(res,"shr $32, %rdx\n");
            }
            else
            {
                res = concatStrFree(res,indentation);
                res = concatStrFree(res,"cqto\n");
            }
            res = concatStrFree(res, indentation);
            res = concatStrFree(res,"idiv ");
            res = concatStrFree(res,convertTarget(ins->args[0]->target,ins->args[0]->mode));
            res = concatStrFree(res,"\n");
            res = concatStrFree(res, indentation);
            res = concatStrFree(res, "movq %rax, %rbx\n");
            break;
        case call:
        {
            res = concatStr(indentation,"call ");
            res = concatStrFree(res,ins->args[0]->target->labelName);
            res = concatStrFree(res,"\n");
            break;
        }
        case cmp:
        {
            res = concatStr(indentation,"cmp ");
            res = concatStrFree(res,convertTarget(ins->args[0]->target,ins->args[0]->mode));
            res = concatStrFree(res,", ");
            res = concatStrFree(res,convertTarget(ins->args[1]->target,ins->args[1]->mode));
            res = concatStrFree(res,"\n");
            break;
        }
        case jmp:
        {
            res = concatStr(indentation,"jmp ");
            res = concatStrFree(res,ins->args[0]->target->labelName);
            res = concatStrFree(res,"\n");
            break;
        }
        case jne:
        {
            res = concatStr(indentation,"jne ");
            res = concatStrFree(res,ins->args[0]->target->labelName);
            res = concatStrFree(res,"\n");
            break;
        }
        case sete:
        {
            res = concatStr(indentation,res);
            res = concatStrFree(res, "sete ");
            res = concatStrFree(res,convertTarget(ins->args[0]->target,ins->args[0]->mode));
            res = concatStrFree(res,"\n");
            break;
        }
        case setne:
        {
            res = concatStr(indentation,res);
            res = concatStrFree(res, "setne ");
            res = concatStrFree(res,convertTarget(ins->args[0]->target,ins->args[0]->mode));
            res = concatStrFree(res,"\n");
            break;
        }
        case setg:
        {
            res = concatStr(indentation,res);
            res = concatStrFree(res, "setg ");
            res = concatStrFree(res,convertTarget(ins->args[0]->target,ins->args[0]->mode));
            res = concatStrFree(res,"\n");
            break;
        }
        case setge:
        {
            res = concatStr(indentation,res);
            res = concatStrFree(res, "setge ");
            res = concatStrFree(res,convertTarget(ins->args[0]->target,ins->args[0]->mode));
            res = concatStrFree(res,"\n");
            break;
        }
        case setl:
        {
            res = concatStr(indentation,res);
            res = concatStrFree(res, "setl ");
            res = concatStrFree(res,convertTarget(ins->args[0]->target,ins->args[0]->mode));
            res = concatStrFree(res,"\n");
            break;
        }
        case setle:
        {
            res = concatStr(indentation,res);
            res = concatStrFree(res, "setle ");
            res = concatStrFree(res,convertTarget(ins->args[0]->target,ins->args[0]->mode));
            res = concatStrFree(res,"\n");
            break;
        }
        case and:
        {
            res = concatStr(indentation,res);
            res = concatStrFree(res, "and ");
            res = concatStrFree(res,convertTarget(ins->args[0]->target,ins->args[0]->mode));
            res = concatStrFree(res,", ");
            res = concatStrFree(res,convertTarget(ins->args[1]->target,ins->args[1]->mode));
            res = concatStrFree(res,"\n");
            break;
        }
        case or:
        {
            res = concatStr(indentation,res);
            res = concatStrFree(res, "or ");
            res = concatStrFree(res,convertTarget(ins->args[0]->target,ins->args[0]->mode));
            res = concatStrFree(res,", ");
            res = concatStrFree(res,convertTarget(ins->args[1]->target,ins->args[1]->mode));
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
            printf("DEBUG OPKIND: %d",ins->op->opK);
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
        res = concatStr(indentation,"push %rbp\t #ALLOCATE STACK SPACE\n");
        res = concatStrFree(res,indentation);
        res = concatStr(res,"movq %rsp, %rbp\n");
        res = concatStrFree(res,indentation);
        res = concatStrFree(res,"addq $");
        res = concatStrFree(res,stackSpace);
        res = concatStrFree(res,", %rsp\n");
        return res;
    }
    if(ins->op->metaK == DEALLOCATE_STACK_SPACE)
    {
        char stackSpace[20];
        sprintf(stackSpace,"%d",ins->op->metaInformation);
        res = concatStr(indentation,"addq $");
        res = concatStrFree(res,stackSpace);
        res = concatStrFree(res, ", %rsp");
        res = concatStrFree(res,"\n");
        res = concatStrFree(res,indentation);
        res = concatStrFree(res,"pop %rbp\n");
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
    if(ins->op->metaK == DEALLOCATE_ARGUMENTS)
    {
        char stackSpace[20];
        sprintf(stackSpace,"%d",ins->op->metaInformation);
        res = concatStr(indentation,"addq $");
        res = concatStrFree(res,stackSpace);
        res = concatStrFree(res, ", %rsp\n");
        return res;
    }
    if(ins->op->metaK == FOLLOW_STATIC_LINK)
        return concatStr(indentation,follow_static_link);
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
                res = deepCopy(rbxVariants[modifier]);
            else if(t->additionalInfo == 2)
                res = deepCopy(rcxVariants[modifier]);
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

const char* printCHAR = "\n.type printCHAR, @function\n"
                        "printCHAR:\n"
                        "    movq $1, %rax\n"
                        "    movq $1, %rdi\n"
                        "    movq $1, %rdx\n"
                        "    push 8(%rsp)\n"
                        "    movq %rsp, %rsi\n"
                        "    syscall\n"
                        "    addq $8, %rsp\n"
                        "    push $10\n"
                        "    movq %rsp, %rsi\n"
                        "    syscall\n"
                        "    addq $8, %rsp\n"
                        "    ret\n";

const char* printBOOLEAN = "\n.type printBOOLEAN, @function\n"
                           "printBOOLEAN:\n"
                           "    movq $1, %rax\n"
                           "    movq $1, %rdi\n"
                           "    cmpb $1, 8(%rsp)\n"
                           "    je printBOOLEANtrue\n"
                           "    movq $0x00000a65736c6166, %rbx\n"
                           "    push %rbx\n"
                           "    movq $6, %rdx\n"
                           "    jmp printBOOLEANend\n"
                           "printBOOLEANtrue:\n"
                           "    movq $0x0000000a65757274, %rbx\n"
                           "    push %rbx\n"
                           "    movq $5, %rdx\n"
                           "printBOOLEANend:\n"
                           "    movq %rsp, %rsi\n"
                           "    syscall\n"
                           "    addq $8, %rsp\n"
                           "    ret\n";

const char* printINT = "\n.type printINT, @function\n"
                       "printINT:\n"
                       "    xor %rax, %rax\n"
                       "    xor %rdx, %rdx\n"
                       "    movq $1, %r10 #Always print newline\n"
                       "    xor %r11, %r11\n"
                       "    movq $10, %r12\n"
                       "    movl 8(%rsp), %eax\n"
                       "    push $10 #newline\n"
                       "    cmpl $0, %eax\n"
                       "    jg printINTpushDecimals\n"
                       "    je printINTzero\n"
                       "    movq $1, %r11\n"
                       "    cltq\n"
                       "    neg %rax\n"
                       "    jmp printINTpushDecimals\n"
                       "printINTzero:\n"
                       "    push $48\n"
                       "    inc %r10\n"
                       "    jmp printINTprint\n"
                       "printINTpushDecimals:\n"
                       "    cmpl $0, %eax\n"
                       "    je printINTmaybeNeg\n"
                       "    idivl %r12d\n"
                       "    addq $48, %rdx\n"
                       "    push %rdx\n"
                       "    movq $0, %rdx\n"
                       "    inc %r10\n"
                       "    jmp printINTpushDecimals\n"
                       "printINTmaybeNeg:\n"
                       "    cmp $1, %r11\n"
                       "    jne printINTprint\n"
                       "    push $45\n"
                       "    inc %r10\n"
                       "printINTprint:\n"
                       "    cmp $0, %r10\n"
                       "    je printINTend\n"
                       "    movq $1, %rax\n"
                       "    movq $1, %rdi\n"
                       "    movq %rsp, %rsi\n"
                       "    movq $1, %rdx\n"
                       "    syscall\n"
                       "    dec %r10\n"
                       "    addq $8, %rsp\n"
                       "    jmp printINTprint\n"
                       "printINTend:\n"
                       "    ret\n";

