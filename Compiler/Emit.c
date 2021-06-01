#include <stdio.h>
#include "IntermediateCodeGeneration.h"
#include "Emit.h"

const char* indentation = "    ";

const char* raxVariants[] = {"%al","%eax","%rax","%rax"};

const char* rbxVariants[] = {"%bl","%ebx","%rbx","%rbx"};
const char* rcxVariants[] = {"%cl","%ecx","%rcx","%rcx"};
const char** registers[] = {rbxVariants,rcxVariants};

const char* sseVariants[] = {"%xmm0","%xmm1"};

const char* rbpVariants[] = {"%bpl","%ebp","%rbp","%rbp"};
const char* rdiVariants[] = {"%dil","%edi","%rdi","%rdi"};
const char* rspVariants[] = {"%sl", "%esp","%rsp","%rsp"};

const char* suffixModifier[]  = {"b","l","q","sd"};
const char* suffixModifier2[] = {"1","4","8","8"};

const char* program_prologue = ".section .data\n.section .text\n.global _start\n_start:\n";
const char* program_epilogue = "    movq %rax, %rdi\n    movq $60, %rax\n    syscall\n\n";
const char* main_callee_save = "";
const char* main_callee_restore = "";
//There is a function handling FUNCTION_DECLARATION metakind
const char* callee_save = "";
const char* callee_restore = "";
const char* callee_epilogue = "ret\n";
const char* caller_save = "";
const char* caller_restore = "";
const char* follow_static_link = "movq (%rdi), %rdi\n";
//There is a function handling DOUBLE_DECLARATION metakind

FILE* fp;

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
        fputs(printDOUBLE,fp);
    if(code->pFlagBOOLEAN || code->pFlagCHAR || code->pFlagINT || code->pFlagDOUBLE)
        fputs(printNewline,fp);
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
            if(ins->op->size == bits_64_d)
            {
                fputs("movq ",fp);
                fputARG(ins->args[0],ins->op->size);
                fputs(", %rax\n",fp);

                fputs(indentation,fp);
                fputs("movq %rax, ",fp);
                fputARG(ins->args[1],ins->op->size);
                fputs("\n",fp);
            }
            else
            {
                fputs("mov",fp);
                fputs(suffixModifier[ins->op->size],fp);
                fputs(" ",fp);
                fputARG(ins->args[0],ins->op->size);
                fputs(", ",fp);
                fputARG(ins->args[1],ins->op->size);
                fputs("\n",fp);
            }
            break;
        }
        case push:
        {
            fputs(indentation,fp);
            if(ins->op->size == bits_64_d)
            {
                fputs("movq ",fp);
                fputARG(ins->args[0],ins->op->size);
                fputs(", %rax\n",fp);
                fputs(indentation,fp);
                fputs("push %rax\n",fp);
            }
            else if(ins->op->size == bits_64)
            {
                fputs("push ",fp);
                fputARG(ins->args[0],ins->op->size);
                fputs("\n",fp);
            }
            else
            {
                fputs("subq $",fp);
                fputs(suffixModifier2[ins->op->size],fp);
                fputs(", %rsp\n",fp);
                fputs(indentation,fp);
                fputs("mov",fp);
                fputs(suffixModifier[ins->op->size],fp);
                fputs(" ",fp);
                fputARG(ins->args[0],ins->op->size);
                fputs(", ",fp);
                fputs(raxVariants[ins->op->size],fp);
                fputs("\n",fp);
                fputs(indentation,fp);
                fputs("mov",fp);
                fputs(suffixModifier[ins->op->size],fp);
                fputs(" ",fp);
                fputs(raxVariants[ins->op->size],fp);
                fputs(", (%rsp)\n",fp);
            }
            break;
        }
        case pop:
        {
            fputs(indentation,fp);
            if(ins->op->size == bits_64_d)
            {
                fputs("pop %rax\n",fp);
                fputs(indentation,fp);
                fputs("movq %rax, ",fp);
                fputARG(ins->args[0],ins->op->size);
                fputs("\n",fp);
            }
            else if(ins->op->size == bits_64)
            {
                fputs("pop ",fp);
                fputARG(ins->args[0],ins->op->size);
                fputs("\n",fp);
            }
            else
            {
                fputs("mov",fp);
                fputs(suffixModifier[ins->op->size],fp);
                fputs(" (%rsp), ",fp);
                fputARG(ins->args[0],ins->op->size);
                fputs("\n",fp);
                fputs(indentation,fp);
                fputs("addq $",fp);
                fputs(suffixModifier2[ins->op->size],fp);
                fputs(", %rsp\n",fp);
            }
            break;
        }
        case add:
        {
            fputs(indentation,fp);
            fputs("add",fp);
            fputs(suffixModifier[ins->op->size],fp);
            fputs(" ",fp);
            fputARG(ins->args[0],ins->op->size);
            fputs(", ",fp);
            fputARG(ins->args[1],ins->op->size);
            fputs("\n",fp);
            break;
        }
        case sub:
        {
            fputs(indentation,fp);
            fputs("sub",fp);
            fputs(suffixModifier[ins->op->size],fp);
            fputs(" ",fp);
            fputARG(ins->args[0],ins->op->size);
            fputs(", ",fp);
            fputARG(ins->args[1],ins->op->size);
            fputs("\n",fp);
            break;
        }
        case mul:
        {
            fputs(indentation,fp);
            if(ins->op->size == bits_64_d)
                fputs("mulsd ",fp);
            else
                fputs("imul ",fp);
            fputARG(ins->args[0],ins->op->size);
            fputs(", ",fp);
            fputARG(ins->args[1],ins->op->size);
            fputs("\n",fp);
            break;
        }
        case divi:
            fputs(indentation,fp);
            if(ins->op->size == bits_64_d)
            {
                fputs("divsd ",fp);
                fputARG(ins->args[0],ins->op->size);
                fputs(", ",fp);
                fputARG(ins->args[1],ins->op->size);
                fputs("\n",fp);
            }
            else
            {
                fputs("mov",fp);
                fputs(suffixModifier[ins->op->size],fp);
                fputs(" ",fp);
                fputARG(ins->args[1],ins->op->size);
                fputs(", ",fp);
                fputs(raxVariants[ins->op->size],fp);
                fputs("\n",fp);
                if(ins->op->size == bits_32) //Convert long (32bits) to quad (64bits)
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
                fputARG(ins->args[0],ins->op->size);
                fputs("\n",fp);
                fputs(indentation,fp);
                fputs("movq %rax, %rbx\n",fp);
            }
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
            if(ins->op->size == bits_64_d)
            {
                fputs("comisd ",fp);
                //if(ins->op->opK == )
            }
            else
                fputs("cmp ",fp);
            fputARG(ins->args[0],ins->op->size);
            fputs(", ",fp);
            fputARG(ins->args[1],ins->op->size);
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
            fputARG(ins->args[0],ins->op->size);
            fputs("\n",fp);
            break;
        }
        case setne:
        {
            fputs(indentation,fp);
            fputs( "setne ",fp);
            fputARG(ins->args[0],ins->op->size);
            fputs("\n",fp);
            break;
        }
        case setg:
        {
            fputs(indentation,fp);
            fputs( "setg ",fp);
            fputARG(ins->args[0],ins->op->size);
            fputs("\n",fp);
            break;
        }
        case setge:
        {
            fputs(indentation,fp);
            fputs( "setge ",fp);
            fputARG(ins->args[0],ins->op->size);
            fputs("\n",fp);
            break;
        }
        case setl:
        {
            fputs(indentation,fp);
            fputs( "setl ",fp);
            fputARG(ins->args[0],ins->op->size);
            fputs("\n",fp);
            break;
        }
        case setle:
        {
            fputs(indentation,fp);
            fputs( "setle ",fp);
            fputARG(ins->args[0],ins->op->size);
            fputs("\n",fp);
            break;
        }
        case setb:
        {
            fputs(indentation,fp);
            fputs( "setb ",fp);
            fputARG(ins->args[0],ins->op->size);
            fputs("\n",fp);
            break;
        }
        case setbe:
        {
            fputs(indentation,fp);
            fputs( "setbe ",fp);
            fputARG(ins->args[0],ins->op->size);
            fputs("\n",fp);
            break;
        }
        case and:
        {
            fputs(indentation,fp);
            fputs("and ",fp);
            fputARG(ins->args[0],ins->op->size);
            fputs(", ",fp);
            fputARG(ins->args[1],ins->op->size);
            fputs("\n",fp);
            break;
        }
        case or:
        {
            fputs(indentation,fp);
            fputs( "or ",fp);
            fputARG(ins->args[0],ins->op->size);
            fputs(", ",fp);
            fputARG(ins->args[1],ins->op->size);
            fputs("\n",fp);
            break;
        }
        case meta:
        {
            fputMeta(ins);
            break;
        }
        case label:
        {
            fputs(ins->args[0]->target->labelName,fp);
            fputs(":\n",fp);
            break;
        }
        case cvtsi2sd:
        {
            fputs(indentation,fp);
            fputs("cvtsi2sd ",fp);
            fputARG(ins->args[0],ins->op->size);
            fputs(", ",fp);
            fputARG(ins->args[1],ins->op->size);
            fputs("\n",fp);
            break;
        }
        default:
            printf("DEBUG OPKIND: %d\n",ins->op->opK);
            fputs("DEBUG INSTRUCTION\n",fp);
            break;
    }
    return res;
}

void fputMeta(INS* ins) {
    switch (ins->op->metaK) {
        case PROGRAM_PROLOGUE: {
            fputs(program_prologue, fp);
            break;
        }
        case PROGRAM_EPILOGUE: {
            fputs(program_epilogue, fp);
            break;
        }
        case MAIN_CALLEE_SAVE: {
            fputs(main_callee_save, fp);
            break;
        }
        case MAIN_CALLEE_RESTORE: {
            fputs(main_callee_restore, fp);
            break;
        }
        case FUNCTION_DECLARATION: {
            fputs("\n.type ", fp);
            fputs(ins->op->metaString, fp);
            fputs(", @function\n", fp);
            break;
        }
        case CALLEE_SAVE: {
            fputs(callee_save, fp);
            break;
        }
        case CALLEE_RESTORE: {
            fputs(callee_restore, fp);
            break;
        }
        case CALLEE_EPILOGUE: {
            fputs(callee_epilogue, fp);
            break;
        }
        case CALLER_SAVE: {
            fputs(caller_save, fp);
            break;
        }
        case CALLER_RESTORE: {
            fputs(caller_restore, fp);
            break;
        }
        case ALLOCATE_STACK_SPACE: {
            char stackSpace[20];
            fputs(indentation, fp);
            fputs("push %rbp\t #ALLOCATE STACK SPACE\n", fp);

            fputs(indentation, fp);
            fputs("movq %rsp, %rbp\n", fp);

            sprintf(stackSpace, "%d", ins->op->metaInt);
            fputs(indentation, fp);
            fputs("addq $", fp);
            fputs(stackSpace, fp);
            fputs(", %rsp\n", fp);
            break;
        }
        case DEALLOCATE_STACK_SPACE: {
            char stackSpace[20];
            sprintf(stackSpace, "%d", ins->op->metaInt);
            fputs(indentation, fp);
            fputs("addq $", fp);
            fputs(stackSpace, fp);
            fputs(", %rsp\n", fp);

            fputs(indentation, fp);
            fputs("pop %rbp\n", fp);
            break;
        }
        case FOLLOW_STATIC_LINK: {
            fputs(indentation, fp);
            fputs(follow_static_link, fp);
            break;
        }
        case DOUBLE_DECLARATION: {
            fputs(ins->op->metaString, fp);
            fputs(":\n", fp);
            putLongsFromDouble(ins->op->metaDouble);
            break;
        }
    }
}

void fputARG(ARG* a, opSuffix suffix)
{
    if(a->mode->mode == dir)
        fputTarget(a->target, suffix);
    else if(a->mode->mode == ind)
    {
        fputs("(",fp);
        fputTarget(a->target, bits_64);
        fputs(")",fp);
    }
    else
    {
        char intString[20];
        sprintf(intString,"%d",a->mode->offset);
        fputs(intString,fp);
        fputs("(",fp);
        fputTarget(a->target, bits_64);
        fputs(")",fp);
    }
}

void fputTarget(Target* t, opSuffix suffix)
{
    switch(t->targetK)
    {
        case imi:
        {
            char intString[20];
            sprintf(intString,"%d",t->additionalInfo);
            fputs("$",fp);
            fputs(intString,fp);
            break;
        }
        case mem:
        {
            fputs(t->labelName,fp);
            break;
        }
        case rbp:
        {
            fputs(rbpVariants[suffix],fp);
            break;
        }
        case rsp:
        {
            fputs(rspVariants[suffix],fp);
            break;
        }
        case rrt:
        {
            fputs(raxVariants[suffix],fp);
            break;
        }
        case rsl:
        {
            fputs(rdiVariants[suffix],fp);
            break;
        }
        case reg:
        {
            if(t->additionalInfo >= 4)
                printf("not good: %d\n",t->additionalInfo);
            if(suffix == bits_64_d)
                fputs(sseVariants[t->additionalInfo],fp);
            else
                fputs(registers[t->additionalInfo][suffix],fp);
            break;
        }
    }
}

void putLongsFromDouble(double val)
{
    char intAsString[20];
    fputs(indentation,fp);
    fputs(".long ",fp);
    sprintf(intAsString,"%u",*(unsigned int*)&val);
    fputs(intAsString,fp);
    fputs("\n",fp);
    fputs(indentation,fp);
    fputs(".long ",fp);
    if(val < 0)
    {
        fputs("-",fp);
        val *= -1;
    }
    sprintf(intAsString,"%u",*(((unsigned int*)&val) + 1));
    fputs(intAsString,fp);
    fputs("\n",fp);
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
                        "    ret\n";

const char* printBOOLEAN = "\n.type printBOOLEAN, @function\n"
                           "printBOOLEAN:\n"
                           "    movq $1, %rax\n"
                           "    movq $1, %rdi\n"
                           "    cmpb $1, 8(%rsp)\n"
                           "    je printBOOLEANtrue\n"
                           "    movq $0x00000065736c6166, %rbx\n"
                           "    push %rbx\n"
                           "    movq $5, %rdx\n"
                           "    jmp printBOOLEANend\n"
                           "printBOOLEANtrue:\n"
                           "    push $0x65757274\n"
                           "    movq $4, %rdx\n"
                           "printBOOLEANend:\n"
                           "    movq %rsp, %rsi\n"
                           "    syscall\n"
                           "    addq $8, %rsp\n"
                           "    ret\n";

const char* printINT = "\n.type printINT, @function\n"
                       "printINT:\n"
                       "    xor %rdx, %rdx\n"
                       "    xor %r10, %r10   #counter\n"
                       "    movq $10, %r12  #divisor\n"
                       "    movl 8(%rsp), %eax  #int stored here\n"
                       "    cmpl $0, %eax\n"
                       "    jg printINTpushDecimals\n"
                       "    je printINTzero\n"
                       "    push %rax   #Save int\n"
                       "    push $45    #Push '-'\n"
                       "    movq $1, %rax\n"
                       "    movq $1, %rdi\n"
                       "    movq %rsp, %rsi\n"
                       "    movq $1, %rdx\n"
                       "    syscall     #Print '-'\n"
                       "    addq $8, %rsp\n"
                       "    pop %rax    #Restore int\n"
                       "    cltq\n"
                       "    neg %rax\n"
                       "    jmp printINTpushDecimals\n"
                       "printINTzero:\n"
                       "    push $48    #Push '0'\n"
                       "    movq $1, %rax\n"
                       "    movq $1, %rdi\n"
                       "    movq %rsp, %rsi\n"
                       "    movq $1, %rdx\n"
                       "    syscall     #Print '0'\n"
                       "    addq $8, %rsp\n"
                       "    jmp printINTend\n"
                       "printINTpushDecimals:\n"
                       "    cmpl $0, %eax\n"
                       "    je printINTprint\n"
                       "    movl $0, %edx   #Positive sign extension\n"
                       "    idivl %r12d\n"
                       "    addq $48, %rdx\n"
                       "    push %rdx\n"
                       "    inc %r10\n"
                       "    jmp printINTpushDecimals\n"
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

const char* printDOUBLE = "\n.type printDOUBLE, @function\n"
                          "printDOUBLE:\n"
                          "    movq 8(%rsp), %rbx  #Double stored here\n"
                          "    cmp $0, %rbx        #If double is 0, just print 0\n"
                          "    jg printDOUBLEpos\n"
                          "    je printDOUBLEzero\n"
                          "    push $45            #Push '-'\n"
                          "    movq $1, %rax\n"
                          "    movq $1, %rdi\n"
                          "    movq %rsp, %rsi\n"
                          "    movq $1, %rdx\n"
                          "    syscall             #Print '-'\n"
                          "    addq $8, %rsp\n"
                          "    jmp printDOUBLEpos\n"
                          "printDOUBLEzero:\n"
                          "    push $48            #Push '0'\n"
                          "    movq $1, %rax\n"
                          "    movq $1, %rdi\n"
                          "    movq %rsp, %rsi\n"
                          "    movq $1, %rdx\n"
                          "    syscall             #Print '0'\n"
                          "    addq $8, %rsp\n"
                          "    ret\n"
                          "printDOUBLEpos:\n"
                          "    push $0x5e3228      #Push \"(2^\"\n"
                          "    movq $1, %rax\n"
                          "    movq $1, %rdi\n"
                          "    movq %rsp, %rsi\n"
                          "    movq $3, %rdx\n"
                          "    syscall             #Print \"(2^\"\n"
                          "    addq $8, %rsp\n"
                          "    shr $52, %rbx       #Push out mantissa\n"
                          "    and $0x7ff, %rbx    #Set sign bit to 0,\n"
                          "                        #Now the biased exponent is in lower 11 bits of rbx\n"
                          "    subl $1023, %ebx    #Subtract bias from exponent\n"
                          "    subq $4, %rsp       #Push the unbiased exponent on stack and print it\n"
                          "    movl %ebx, (%rsp)\n"
                          "    call printINT\n"
                          "    addq $4, %rsp\n"
                          "\n"
                          "    push $0x29          #Print ')'\n"
                          "    movq $1, %rax\n"
                          "    movq $1, %rdi\n"
                          "    movq %rsp, %rsi\n"
                          "    movq $1, %rdx\n"
                          "    syscall             #Print ')'\n"
                          "    addq $8, %rsp\n"
                          "\n"
                          "    movq 8(%rsp), %rbx  #Double stored in RBX again\n"
                          "    and _dc_getMantissa, %rbx   #Only mantissa is left in rbx\n"
                          "    cmp $0, %rbx        #If mantissa = 0\n"
                          "    je printDOUBLEend   #Then dont print fractional part\n"
                          "    push $0x2e312a      #Push \"*1.\"\n"
                          "    movq $1, %rax\n"
                          "    movq $1, %rdi\n"
                          "    movq %rsp, %rsi\n"
                          "    movq $3, %rdx\n"
                          "    syscall             #Print \"*1.\"\n"
                          "    addq $8, %rsp\n"
                          "\n"
                          "    or _dc_exp1023, %rbx        #set the exponent to 1023\n"
                          "    movq %rbx, %xmm0\n"
                          "    addsd _dc_neg1, %xmm0       #add -1 to xmm0\n"
                          "    movq $10, %rbx              #Counter = 10\n"
                          "printDOUBLEloop:\n"
                          "    comisd _dc_0, %xmm0\n"
                          "    je printDOUBLEend\n"
                          "    mulsd _dc_10, %xmm0         #multiply fraction by 10\n"
                          "    comisd _dc_1, %xmm0         #Check if fraction < 1\n"
                          "    jb printDOUBLEpushZero      #Print zero\n"
                          "    cvttsd2si %xmm0, %rax       #Get the integer part\n"
                          "    cvtsi2sd %rax, %xmm1\n"
                          "    subsd %xmm1, %xmm0\n"
                          "    addq $48, %rax\n"
                          "    push %rax\n"
                          "    jmp printDOUBLEprint\n"
                          "printDOUBLEpushZero:\n"
                          "    push $48\n"
                          "printDOUBLEprint:\n"
                          "    movq $1, %rax\n"
                          "    movq $1, %rdi\n"
                          "    movq %rsp, %rsi\n"
                          "    movq $1, %rdx\n"
                          "    syscall\n"
                          "    addq $8, %rsp\n"
                          "    dec %rbx\n"
                          "    cmp $0, %rbx\n"
                          "    jne printDOUBLEloop\n"
                          "printDOUBLEend:\n"
                          "    ret\n"
                          "\n"
                          "_dc_0:\n"
                          "    .long 0x00000000\n"
                          "    .long 0x00000000\n"
                          "\n"
                          "_dc_1:\n"
                          "    .long 0x00000000\n"
                          "    .long 0x3ff00000\n"
                          "\n"
                          "_dc_getMantissa:\n"
                          "    .long 0xffffffff\n"
                          "    .long 0x000fffff\n"
                          "\n"
                          "_dc_exp1023:\n"
                          "    .long 0x00000000\n"
                          "    .long 0x3ff00000\n"
                          "\n"
                          "_dc_neg1:\n"
                          "    .long 0x00000000\n"
                          "    .long 0xbff00000\n"
                          "\n"
                          "_dc_10:\n"
                          "    .long 0x00000000\n"
                          "    .long 0x40240000\n";

const char* printNewline = "\n.type printNewline, @function\n"
                           "printNewline:\n"
                           "    push $10\n"
                           "    movq $1, %rax\n"
                           "    movq $1, %rdi\n"
                           "    movq %rsp, %rsi\n"
                           "    movq $1, %rdx\n"
                           "    syscall\n"
                           "    addq $8, %rsp\n"
                           "    ret\n";

