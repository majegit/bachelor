#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IntermediateCodeGeneration.h"
#include "Emit.h"

char* program_prologue = ".section .data\n.section .text\n.global _start\n";
char* program_epilogue = "movq $60, %rax\nmovq $0, %rdi\nsyscall\n";

char* asmCode = "";

void emit(LL* code, const char* outputFileName)
{
    while(code->first != NULL)
    {
        char* newAsmCode = convertInsToAsm(code->first->ins);
        appendCode(newAsmCode);
        code->first = code->first->next;
    }
    printf("here\n");
    printf("%s\n",asmCode);
    FILE* fp = fopen(outputFileName,"w");
    fputs(asmCode,fp);
    fclose(fp);
    printf("Done\n");
}

void appendCode(char* newAsmCode)
{
    size_t newStringSize = strlen(asmCode)+strlen(newAsmCode)+1;
    char* s = (char*)malloc(newStringSize);

    memcpy(s,asmCode,strlen(asmCode));
    memcpy(s+strlen(asmCode),newAsmCode,strlen(newAsmCode));
    s[newStringSize-1] = '\0';
    free(newAsmCode);
    free(asmCode);
    asmCode = s;
}

char* convertInsToAsm(INS* ins)
{
    if(ins->op->opK == meta)
        return convertMetaIns(ins);
    printf("Did not match INS\n");
    return "debug";
}

char* convertMetaIns(INS* ins)
{
    if(ins->op->metaK == PROGRAM_PROLOGUE)
        return program_prologue;
    if(ins->op->metaK == ALLOCATE_STACK_SPACE)
        return "YO";//strcat("push %rbp\nsubq $" + ins->op->metaInformation+"%rsp");
    return "debug";
}
