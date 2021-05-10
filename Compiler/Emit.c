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

const char* sizeModifier[]  = {"b","l","q","sd"};
const char* sizeModifier2[] = {"1","4","8","8"};

const char* program_prologue = ".section .data\n.section .text\n.global _start\n_start:\n";
const char* program_epilogue = "    movq %rax, %rdi\n    movq $60, %rax\n    syscall\n\n";
const char* main_callee_save = "";
const char* main_callee_restore = "";
const char* callee_prologue = "";
const char* callee_save = "";
const char* callee_restore = "";
const char* callee_epilogue = "ret\n";
const char* follow_static_link = "movq (%rdi), %rdi\n";


FILE* fp;
char* aux;


void emit(LL* code, const char* outputFileName)
{
    //Print the asmcode to a file
    fp = fopen(outputFileName,"w");
    
    LLN* node = code->first;
    while(node != NULL)
    {
        convertInsToAsm(node->ins);
        node = node->next;
    }
    if(code->pFlagBOOLEAN)
        fputs(printBOOLEAN,fp);
    if(code->pFlagCHAR)
        fputs(printCHAR,fp);
    if(code->pFlagINT)
        fputs(printINT,fp);
    if(code->pFlagDOUBLE)
        fputs("DOUBLE DEBUG\n",fp);

    printf("closing file\n");
    fclose(fp);
}

char* convertInsToAsm(INS* ins)
{
    char* res = "";
    switch(ins->op->opK)
    {
        case move:
        {
            fputs(indentation,fp);
            fputs("mov",fp);
            fputs(sizeModifier[ins->op->size],fp);
            fputs(" ",fp);
            aux = convertTarget(ins->args[0]->target,ins->args[0]->mode);
            fputs(aux,fp);
            free(aux);
            fputs(", ",fp);
            aux = convertTarget(ins->args[1]->target,ins->args[1]->mode);
            fputs(aux,fp);
            free(aux);
            fputs("\n",fp);
            break;
        }
        case push:
        {
            fputs(indentation,fp);
            if(ins->op->size == bits_64)
            {
                fputs("push ",fp);
                aux = convertTarget(ins->args[0]->target,ins->args[0]->mode);
                fputs(aux,fp);
                free(aux);
                fputs("\n",fp);
            }
            else
            {
                fputs("subq $",fp);
                fputs(sizeModifier2[ins->op->size],fp);
                fputs(", %rsp\n",fp);
                fputs(indentation,fp);
                fputs("mov",fp);
                fputs(sizeModifier[ins->op->size],fp);
                fputs(" ",fp);
                aux = convertTarget(ins->args[0]->target, ins->args[0]->mode);
                fputs(aux, fp);
                free(aux);
                fputs(", ",fp);
                fputs(raxVariants[ins->op->size],fp);
                fputs("\n",fp);
                fputs(indentation,fp);
                fputs("mov",fp);
                fputs(sizeModifier[ins->op->size],fp);
                fputs(" ",fp);
                fputs(raxVariants[ins->op->size],fp);
                fputs(", (%rsp)\n",fp);
            }
            break;
        }
        case pop:
        {
            fputs(indentation,fp);
            if(ins->op->size == bits_64)
            {
                fputs("pop ",fp);
                aux = convertTarget(ins->args[0]->target,ins->args[0]->mode);
                fputs(aux,fp);
                free(aux);
                fputs("\n",fp);
            }
            else
            {
                fputs("mov",fp);
                fputs(sizeModifier[ins->op->size],fp);
                fputs(" (%rsp), ",fp);
                aux = convertTarget(ins->args[0]->target, ins->args[0]->mode);
                fputs(aux,fp);
                free(aux);
                fputs("\n",fp);
                fputs(indentation,fp);
                fputs("addq $",fp);
                fputs(sizeModifier2[ins->op->size],fp);
                fputs(", %rsp\n",fp);
            }
            break;
        }
        case add:
        {
            fputs(indentation,fp);
            fputs("add",fp);
            fputs(sizeModifier[ins->op->size],fp);
            fputs(" ",fp);
            aux = convertTarget(ins->args[0]->target,ins->args[0]->mode);
            fputs(aux,fp);
            free(aux);
            fputs(", ",fp);
            aux = convertTarget(ins->args[1]->target,ins->args[1]->mode);
            fputs(aux,fp);
            free(aux);
            fputs("\n",fp);
            break;
        }
        case sub:
        {
            fputs(indentation,fp);
            fputs("sub",fp);
            fputs(sizeModifier[ins->op->size],fp);
            fputs(" ",fp);
            aux = convertTarget(ins->args[0]->target,ins->args[0]->mode);
            fputs(aux,fp);
            free(aux);
            fputs(", ",fp);
            aux = convertTarget(ins->args[1]->target,ins->args[1]->mode);
            fputs(aux,fp);
            fputs("\n",fp);
            break;
        }
        case mul:
        {
            fputs(indentation,fp);
            fputs("imul ",fp);
            aux = convertTarget(ins->args[0]->target,ins->args[0]->mode);
            fputs(aux,fp);
            free(aux);
            fputs(", ",fp);
            aux = convertTarget(ins->args[1]->target,ins->args[1]->mode);
            fputs(aux, fp);
            free(aux);
            fputs("\n",fp);
            break;
        }
        case divi:
            fputs(indentation,fp);
            fputs("mov",fp);
            fputs(sizeModifier[ins->args[1]->target->size],fp);
            fputs(" ",fp);
            aux = convertTarget(ins->args[1]->target,ins->args[1]->mode);
            fputs(aux,fp);
            free(aux);
            fputs(", ",fp);
            fputs(raxVariants[ins->args[0]->target->size],fp);
            fputs("\n",fp);
            if(ins->args[0]->target->size == bits_32) //Convert long (32bits) to quad (64bits)
            {
                fputs(indentation,fp);
                fputs("cltq\n",fp);
                fputs(indentation,fp);
                fputs("movq %rax, %rdx\n",fp);
                fputs(indentation,fp);
                fputs("shr $32, %rdx\n",fp);
            }
            else
            {
                fputs(indentation,fp);
                fputs("cqto\n",fp);
            }
            fputs(indentation,fp);
            fputs("idiv ",fp);
            aux = convertTarget(ins->args[0]->target,ins->args[0]->mode);
            fputs(aux,fp);
            fputs("\n",fp);
            fputs(indentation,fp);
            fputs("movq %rax, %rbx\n",fp);
            break;
        case call:
        {
            fputs(indentation,fp);
            fputs("call ",fp);
            fputs(ins->args[0]->target->labelName,fp);
            fputs("\n",fp);
            break;
        }
        case cmp:
        {
            fputs(indentation,fp);
            fputs("cmp ",fp);
            aux = convertTarget(ins->args[0]->target,ins->args[0]->mode);
            fputs(aux,fp);
            free(aux);
            fputs(", ",fp);
            aux = convertTarget(ins->args[1]->target,ins->args[1]->mode);
            fputs(aux,fp);
            free(aux);
            fputs("\n",fp);
            break;
        }
        case jmp:
        {
            fputs(indentation,fp);
            fputs("jmp ",fp);
            fputs(ins->args[0]->target->labelName,fp);
            fputs("\n",fp);
            break;
        }
        case jne:
        {
            fputs(indentation,fp);
            fputs("jne ",fp);
            fputs(ins->args[0]->target->labelName,fp);
            fputs("\n",fp);
            break;
        }
        case sete:
        {
            fputs(indentation,fp);
            fputs( "sete ",fp);
            aux = convertTarget(ins->args[0]->target,ins->args[0]->mode);
            fputs(aux,fp);
            free(aux);
            fputs("\n",fp);
            break;
        }
        case setne:
        {
            fputs(indentation,fp);
            fputs( "setne ",fp);
            aux = convertTarget(ins->args[0]->target,ins->args[0]->mode);
            fputs(aux,fp);
            free(aux);
            fputs("\n",fp);
            break;
        }
        case setg:
        {
            fputs(indentation,fp);
            fputs( "setg ",fp);
            aux = convertTarget(ins->args[0]->target,ins->args[0]->mode);
            fputs(aux,fp);
            free(aux);
            fputs("\n",fp);
            break;
        }
        case setge:
        {
            fputs(indentation,fp);
            fputs( "setge ",fp);
            aux = convertTarget(ins->args[0]->target,ins->args[0]->mode);
            fputs(aux,fp);
            free(aux);
            fputs("\n",fp);
            break;
        }
        case setl:
        {
            fputs(indentation,fp);
            fputs( "setl ",fp);
            aux = convertTarget(ins->args[0]->target,ins->args[0]->mode);
            fputs(aux,fp);
            free(aux);
            fputs("\n",fp);
            break;
        }
        case setle:
        {
            fputs(indentation,fp);
            fputs( "setle ",fp);
            aux = convertTarget(ins->args[0]->target,ins->args[0]->mode);
            fputs(aux,fp);
            free(aux);
            fputs("\n",fp);
            break;
        }
        case and:
        {
            fputs(indentation,fp);
            fputs("and ",fp);
            aux = convertTarget(ins->args[0]->target,ins->args[0]->mode);
            fputs(aux,fp);
            free(aux);
            fputs(", ",fp);
            aux = convertTarget(ins->args[1]->target,ins->args[1]->mode);
            fputs(aux,fp);
            free(aux);
            fputs("\n",fp);
            break;
        }
        case or:
        {
            fputs(indentation,fp);
            fputs( "or ",fp);
            aux = convertTarget(ins->args[0]->target,ins->args[0]->mode);
            fputs(aux,fp);
            free(aux);
            fputs(", ",fp);
            aux = convertTarget(ins->args[1]->target,ins->args[1]->mode);
            fputs(aux, fp);
            fputs("\n",fp);
            break;
        }
        case meta:
        {
            aux = convertMetaIns(ins);
            fputs(aux,fp);
            free(aux);
            break;
        }
        case label:
        {
            fputs(ins->args[0]->target->labelName,fp);
            fputs(":\n",fp);
            break;
        }
        default:

            printf("DEBUG OPKIND: %d",ins->op->opK);
            fputs("debugINS\n",fp);
            break;
    }
    return res;
}

char* convertMetaIns(INS* ins)
{
    char* res = "";
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
        sprintf(stackSpace,"%d",ins->op->metaInt);
        res = concatStr(indentation,"push %rbp\t #ALLOCATE STACK SPACE\n");
        res = concatStrFree(res,indentation);
        res = concatStrFree(res,"movq %rsp, %rbp\n");
        if(ins->op->metaInt != 0)
        {
            res = concatStrFree(res,indentation);
            res = concatStrFree(res,"addq $");
            res = concatStrFree(res,stackSpace);
            res = concatStrFree(res,", %rsp\n");
        }
        return res;
    }
    if(ins->op->metaK == DEALLOCATE_STACK_SPACE)
    {
        char stackSpace[20];
        sprintf(stackSpace,"%d",ins->op->metaInt);
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
        sprintf(stackSpace,"%d",ins->op->metaInt);
        res = concatStr(indentation,"addq $");
        res = concatStrFree(res,stackSpace);
        res = concatStrFree(res, ", %rsp\n");
        return res;
    }
    if(ins->op->metaK == FOLLOW_STATIC_LINK)
        return concatStr(indentation,follow_static_link);
    if(ins->op->metaK == DOUBLE_DECLARATION)
    {
        res = concatStr(res,ins->op->metaString);
        res = concatStrFree(res,":\n");
        res = concatStrFreeFree(res,getLongsFromDouble(ins->op->metaDouble));
        return res;
    }
    printf("debugMETA: %d\n",ins->op->metaK);
    return deepCopy("debugMETA\n");
}

char* meta_function_declaration(INS* ins)
{
    char* res = "\n.type ";
    res = concatStr(res,ins->op->metaString);
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
            res = concatStrFree(res,intString);
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

char* getLongsFromDouble(double val)
{
    char intAsString[20];
    char* res = "";
    res = concatStr(res,indentation);
    res = concatStrFree(res,".long ");
    sprintf(intAsString,"%u",*(unsigned int*)&val);
    res = concatStrFree(res,intAsString);
    res = concatStrFree(res,"\n");
    res = concatStrFree(res,indentation);
    res = concatStrFree(res,".long ");
    if(val < 0)
    {
        res = concatStrFree(res,"-");
        val *= -1;
    }
    sprintf(intAsString,"%u",*(((unsigned int*)&val) + 1));
    res = concatStrFree(res,intAsString);
    res = concatStrFree(res,"\n");
    return res;
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

