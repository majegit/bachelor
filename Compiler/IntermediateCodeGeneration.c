#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"
#include "IntermediateCodeGeneration.h"

LL* code = &(LL){NULL,NULL,0,0,0,0};
LLFUN* funs = &(LLFUN){NULL,NULL};
LLD* doubles = &(LLD){NULL,NULL};

SYMBOLTABLE* currentScope;
FUNCTION* currentFunction;
int depth = 0;

LL* icgTraversePROGRAM(PROGRAM* prog)
{
    currentScope = prog->sc->symbolTable;                          //Update pointer to global scope
    quickMeta(PROGRAM_PROLOGUE);

    int globalStackSpace = currentScope->nextVariableLabel;              //Stack space needed in global scope
    quickMetaWithInfo(ALLOCATE_STACK_SPACE, globalStackSpace);   //Push rbp and allocate stack space
    icgTraverseSTMTNODE(prog->sc->stmtnode);

    quickMeta(PROGRAM_EPILOGUE);

    LLNFUN* currentNode = funs->first;
    while(currentNode != NULL)
    {
        icgTraverseFUNCTION(currentNode->f);
        currentNode = currentNode->next;
    }

    LLND* cNode = doubles->first;
    while(cNode != NULL)
    {
        OP* op = makeOPMeta(DOUBLE_DECLARATION,0,cNode->val,cNode->label);
        ARG* args[2] = {NULL, NULL};
        quickIns(makeINS(op,args));
        cNode = cNode->next;
    }

    return code;
}

void icgTraverseSTMTNODE(STMTNODE* sn)
{
    if(sn == NULL)
        return;
    icgTraverseSTMT(sn->stmt);
    icgTraverseSTMTNODE(sn->next);
}

void icgTraverseSTMTCOMP(STMTCOMP* sc)
{
    depth++;
    currentScope = sc->symbolTable;

    int compStackSpace = currentScope->nextVariableLabel;  //Stack space needed for local variables
    quickMetaWithInfo(ALLOCATE_STACK_SPACE, compStackSpace);   //Push rbp and allocate stack space
    icgTraverseSTMTNODE(sc->stmtnode);
    quickMetaWithInfo(DEALLOCATE_STACK_SPACE, compStackSpace); //Deallocate stack space and pop rbp

    depth--;
    currentScope = sc->symbolTable->par;                           //Update pointer to current scope
}

void icgTraverseSTMT(STMT* s)
{
    switch(s->kind)
    {
        case whileK:
        {
            char* labelName = labelGenerator(while_label);     //Generate start label
            char* endlabelName = concatStr("end",labelName);    //Make end label

            quickLabelString(while_label, labelName);       //while_X:
            icgTraverseEXP(s->val.whileS.guard);                    //Guard
            quickPopRRT(bits_8);                             //Move boolean to rrt
            quickCheckTruthValue();                              //cmp rrt, $1
            quickJumpIfFalse(endwhile_label,endlabelName);    //jne endwhile_X
            icgTraverseSTMTCOMP(s->val.whileS.body);                //generate the code for the body of the whileloop
            quickLabelString(endwhile_label, endlabelName); //endwhile_X:
            break;
        }
        case assignK:
        {
            OP* op;
            Target* src, *dest;
            ARG* srcA, *destA;
            EXP* e = s->val.assignS.val;

            icgTraverseEXP(e);
            quickPopRRT(getSuffixOfType(e->type));

            int varDepth = getSymbolDepth(s->val.assignS.symbol, currentScope); //Scope depth
            int varOffset = s->val.assignS.symbol->offset; //Offset from base pointer

            quickMoveRBPToRSL();
            for(int i=0; i < varDepth; i++)
                quickMeta(FOLLOW_STATIC_LINK);

            op = makeOP(move,getSuffixOfType(e->type));
            src = makeTarget(rrt);
            srcA = makeARG(src,makeMode(dir));
            dest = makeTarget(rsl);
            destA = makeARG(dest,makeModeIRL(varOffset));

            ARG* args[2] = {srcA, destA};
            quickIns(makeINS(op,args));
            break;
        }
        case ifElseK:
        {
            int elsePart = s->val.ifElseS.elsebody != NULL;           //Check if there is an else part
            char* labelName = labelGenerator(if_label);        //Generate if_X label

            quickLabelString(if_label, labelName);          //if_X:
            icgTraverseEXP(s->val.ifElseS.cond);                    //Guard
            quickPopRRT(bits_8);                             //Move boolean to rrt
            quickCheckTruthValue();                              //cmp $1   , rrt
            labelName = concatStr("end",labelName);             //Generate endif_X label
            quickJumpIfFalse(endif_label,labelName);          //jne endif_X
            icgTraverseSTMTCOMP(s->val.ifElseS.ifbody);             //if-body

            char* endelseLabel;
            if(elsePart)
            {
                endelseLabel = concatStr("endelse",labelName+5);//Generate endelse_X
                quickUnconditionalJmp(endelse_label,endelseLabel); //jmp endelse_X
            }
            quickLabelString(endif_label, labelName);        //endif_X:
            if(elsePart)
            {
                icgTraverseSTMTCOMP(s->val.ifElseS.elsebody);        //else-body
                quickLabelString(endelse_label,endelseLabel);//endelse_X:
            }
            break;
        }
        case returnK:
        {
            icgTraverseEXP(s->val.returnS);

            //This needs to be reimplemented, functions should have a SYMBOL *symbol in their struct,
            //so we dont need to have this crazy lookup, but instead should be able to write:
            //SYMBOL* funSymbol = s->val.returnS.function->symbol;
            SYMBOL* funSymbol = lookupSymbolFunName(currentFunction->name,currentFunction->body->symbolTable->par);

            quickMoveRBPToRSL();
            for (int i = 0; i < depth; i++)
                quickMeta(FOLLOW_STATIC_LINK);
            quickMoveRSLToRBP();

            char *endLabel = concatStr("end", funSymbol->label);
            quickUnconditionalJmp(endfunction_label, endLabel);
            break;
        }
        case printK:
        {
            opSuffix typeSize = getSuffixOfType(s->val.printS->type);
            icgTraverseEXP(s->val.printS);

            char* printFun = concatStr("print",s->val.printS->type);
            if(strcmp(s->val.printS->type,"BOOLEAN") == 0)
                code->pFlagBOOLEAN = 1;
            if(strcmp(s->val.printS->type,"CHAR") == 0)
                code->pFlagCHAR = 1;
            if(strcmp(s->val.printS->type,"INT") == 0)
                code->pFlagINT = 1;
            if(strcmp(s->val.printS->type,"DOUBLE") == 0)
            {
                code->pFlagINT = 1;
                code->pFlagDOUBLE = 1;
            }


            quickCallFun(printFun);

            //Decrement stack pointer (reverse push arguments)
            Target* src = makeTargetIMI(getIntFromSuffix(typeSize));
            ARG* srcA = makeARG(src,makeMode(dir));

            Target* dest = makeTarget(rsp);
            ARG* destA = makeARG(dest,makeMode(dir));

            ARG* args[2] = {srcA,destA};
            OP* op = makeOP(add, bits_64);
            quickIns(makeINS(op,args));

            quickCallFun("printNewline");
            break;
        }
        case varDeclK:
            break;
        case expK:
            icgTraverseEXP(s->val.expS);
            break;
        case funDeclK:
            addToLLFUN(s->val.funDeclS);
            break;
    }
}

void icgTraverseEXP(EXP* e)
{
    switch(e->kind)
    {
        case idK:
        {
            quickPushId(e->val.idE.symbol);
            break;
        }
        case intK:
        case boolK:
        case charK:
        {
            Target* target = makeTargetIMI(e->val.intE); //e->val.intE = e->val.charE = e->val.boolE, they are all single ints in an union
            ARG* arg = makeARG(target, makeMode(dir));
            ARG* args[2] = {arg, NULL};
            opSuffix size = e->kind == intK ? bits_32 : bits_8;
            OP* op = makeOP(push, size);
            quickIns(makeINS(op, args));
            break;
        }
        case doubleK:
        {
            char* dLabel = doubleLabelGenerator(e->val.doubleE);
            quickPushDoubleLabel(dLabel);
            break;
        }
        case binopK:
        {
            icgTraverseEXP(e->val.binopE.left);     //PUSH OP0
            icgTraverseEXP(e->val.binopE.right);    //PUSH OP1
            quickPopReg(e->val.binopE.right->type, 1);   //POP OP1
            quickPopReg(e->val.binopE.left->type, 0);    //POP OP0

            opSuffix size = getSuffixOfType(e->val.binopE.right->type); //Using the fact that for all operations, the operands are same type
            char* op = e->val.binopE.operator;

            if(strcmp(op,"-") == 0)
                quickArithmeticINS(sub,size);
            else if (strcmp(op,"+") == 0)
                quickArithmeticINS(add,size);
            else if (strcmp(op,"*") == 0)
                quickArithmeticINS(mul,size);
            else if (strcmp(op,"/") == 0)
                quickArithmeticINS(divi,size);
            else if (strcmp(op,"L") == 0)
                quickCompareINS(setl,size);
            else if (strcmp(op,"G") == 0)
                quickCompareINS(setg,size);
            else if (strcmp(op,"LEQ") == 0)
                quickCompareINS(setle,size);
            else if (strcmp(op,"GEQ") == 0)
                quickCompareINS(setge,size);
            else if (strcmp(op,"EQ") == 0)
                quickCompareINS(sete,size);
            else if (strcmp(op,"NEQ") == 0)
                quickCompareINS(setne,size);
            else if (strcmp(op,"AND") == 0)
                quickBooleanINS(and);
            else if (strcmp(op,"OR") == 0)
                quickBooleanINS(or);
            break;
        }
        case funK:
        {
            icgTraverseAPARAMETERNODE(e->val.funE.aparameternode);
            SYMBOL* funSymbol = lookupSymbolFunName(e->val.funE.id,currentScope);

            int scopeDepth = getSymbolDepth(funSymbol,currentScope);
            quickPushRBP(); //Save old base pointer
            for(int i = 0; i<scopeDepth; ++i)
                quickIncrementScopeOneLevel(); //Movq (%rbp), %rbp
            quickCallFun(funSymbol->label);
            quickPopRBP();
            int sizeOfParameters = getSizeOfParameters(funSymbol->fpn);

            OP* op = makeOP(add,bits_64);

            Target* src = makeTargetIMI(sizeOfParameters);
            ARG* srcA = makeARG(src,makeMode(dir));

            Target* dest = makeTarget(rsp);
            ARG* destA = makeARG(dest,makeMode(dir));

            ARG* args[2] = {srcA,destA};
            quickIns(makeINS(op,args));

            quickPushRRT(getSuffixOfType(funSymbol->type));
            break;
        }
        case coerceK:
        {
            Target* src, *dest;
            ARG* srcA, *destA;
            ARG* args[2];
            OP* op;
            opKind opK;

            icgTraverseEXP(e->val.coerceE);

            opSuffix suffixPre = getSuffixOfType(e->val.coerceE->type);
            opSuffix suffixPost = getSuffixOfType(e->type);

            if(strcmp(e->type, "DOUBLE") == 0 && strcmp(e->val.coerceE->type, "INT") == 0) //Right now this is the only type of coercion
                opK = cvtsi2sd;
            else
                exit(1); //ERROR, should never happen

            //The expression to be coerced is on the stack, convert it and save result in register 0
            op = makeOP(opK,suffixPost);
            src = makeTarget(rsp);
            srcA = makeARG(src,makeMode(ind));

            dest = makeTargetReg(0);
            destA = makeARG(dest,makeMode(dir));

            args[0] = srcA;
            args[1] = destA;
            quickIns(makeINS(op,args));

            //Remove the top of stack (uncoerced expression)
            op = makeOP(add,bits_64);

            src = makeTargetIMI(getIntFromSuffix(suffixPre));
            srcA = makeARG(src,makeMode(dir));

            dest = makeTarget(rsp);
            destA = makeARG(dest,makeMode(dir));

            args[0] = srcA;
            args[1] = destA;
            quickIns(makeINS(op,args));

            //Push register 0 onto the stack
            op = makeOP(push,suffixPost);

            src = makeTargetReg(0);
            srcA = makeARG(src,makeMode(dir));

            args[0] = srcA;
            args[1] = destA;
            quickIns(makeINS(op,args));
            break;
        }
    }
}

void icgTraverseAPARAMETERNODE(APARAMETERNODE* apn)
{
    if(apn == NULL)
        return;
    icgTraverseEXP(apn->current->exp);
    icgTraverseAPARAMETERNODE(apn->next);
}

void icgTraverseFUNCTION(FUNCTION* f)
{
    depth = 0;
    currentFunction = f;

    char* funLabel = lookupSymbolFunName(f->name,currentScope)->label;//funLabel = funX_<function name>
    quickMetaString(FUNCTION_DECLARATION,funLabel); //.type funX_<function name>, @function
    quickLabelString(function_label,funLabel);       //funX_<function name>
    currentScope = f->body->symbolTable;                     //update currentScope
    int stackSpace = currentScope->nextVariableLabel;

    quickMetaWithInfo(ALLOCATE_STACK_SPACE,stackSpace);
    quickMeta(CALLEE_SAVE);                          //Push callee save registers

    icgTraverseSTMTNODE(f->body->stmtnode);                  //Traverse contents of function

    char* endfunLabel = concatStr("end",funLabel);
    quickLabelString(endfunction_label,endfunLabel); //endfunX_<function name>
    quickPopRRT(getSuffixOfType(f->returnType));
    quickMoveRBPToRSP();
    quickPopRBP();
    quickMeta(CALLEE_RESTORE);                       //Pop callee save registers
    quickMeta(CALLEE_EPILOGUE);                      //ret

    currentFunction = NULL;
    depth = 0;
}

void addToLL(LLN* newCode)
{
    if(code->first == NULL) //First time we insert something
    {
        code->first = newCode;
        code->first->next = NULL;
    }
    else
        code->last->next = newCode;
    code->last = newCode;
}

//MAKE_X
Mode* makeMode(addressingMode addressingMode) {
    Mode* mode = (Mode*)malloc(sizeof(Mode));
    mode->mode = addressingMode;
    return mode;
}

Mode* makeModeIRL(int offset)
{
    Mode* mode = makeMode(irl);
    mode->offset = offset;
    return mode;
}

Target* makeTarget(targetKind k)
{
    Target* t = (Target*)malloc(sizeof(Target));
    t->targetK = k;
    t->labelName = NULL;
    return t;
}

Target* makeTargetLabel(labelKind k, char* name)
{
    Target* t = makeTarget(mem);
    t->labelK = k;
    t->labelName = name;
    return t;
}

Target* makeTargetReg(int regNumber)
{
    Target* t;
    t = makeTarget(reg);
    t->additionalInfo = regNumber;
    return t;
}

Target* makeTargetIMI(int imiValue)
{
    Target* t = makeTarget(imi);
    t->additionalInfo = imiValue;
    return t;
}

Target* makeTargetDouble(double doubleVal)
{
    char* lName = doubleLabelGenerator(doubleVal);
    Target* t = makeTargetLabel(double_label,lName);
    return t;
}

OP* makeOP(opKind opK, opSuffix size)
{
    OP* op = (OP*)malloc(sizeof(OP));
    op->opK = opK;
    op->size = size;
    return op;
}

OP* makeOPMeta(metaKind k, int metaInt, double metaDouble, char* metaLabel)
{
    OP* op = makeOP(meta,bits_64);
    op->opK = meta;
    op->metaK = k;
    op->metaInt = metaInt;
    op->metaDouble = metaDouble;
    op->metaString = metaLabel;
    return op;
}

ARG* makeARG(Target* target, Mode* mode)
{
    ARG* arg = (ARG*)malloc(sizeof(ARG));
    arg->target = target;
    arg->mode = mode;
    return arg;
}

INS* makeINS(OP* op, ARG** args)
{
    INS* ins = (INS*)malloc(sizeof(INS));
    ins->op = op;
    ins->args[0] = args[0];
    ins->args[1] = args[1];
    return ins;
}

LLN* makeLLN(INS* ins)
{
    LLN* node = (LLN*)malloc(sizeof(LLN));
    node->ins = ins;
    node->next = NULL;
    return node;
}

//QUICK ADD X
void quickIns(INS* ins)
{
    LLN* node = makeLLN(ins);
    addToLL(node);
}

void quickMeta(metaKind metaK) {
    OP* op = makeOPMeta(metaK,0,0,NULL);
    ARG* args[2] = {NULL,NULL};
    quickIns(makeINS(op,args));
};

void quickMetaWithInfo(metaKind metaK, int metaInt)
{
    OP* op = makeOPMeta(metaK,metaInt,0,NULL);
    ARG* args[2] = {NULL,NULL};
    quickIns(makeINS(op,args));
}

void quickMetaString(metaKind metaK, char* str)
{
    OP* op = makeOPMeta(metaK,0,0,str);
    ARG* args[2] = {NULL,NULL};
    quickIns(makeINS(op,args));
}

void quickLabelString(labelKind kind, char* name)
{
    Target* t = makeTargetLabel(kind,name);
    ARG* arg = makeARG(t, makeMode(dir));
    ARG* args[2] = {arg, NULL};
    OP* op = makeOP(label,bits_64);
    quickIns(makeINS(op,args));
}

void quickPush(opSuffix size, Target* target, Mode* mode)
{
    ARG* arg = makeARG(target, mode);
    ARG* args[2] = {arg,NULL};
    OP* op = makeOP(push,size);
    quickIns(makeINS(op, args));
}

//Pushes a variable (identifier) on the stack
void quickPushId(SYMBOL* s)
{
    int varDepth = getSymbolDepth(s,currentScope); //Scope depth
    int varOffset = s->offset;

    quickMoveRBPToRSL();
    for(int i=0; i < varDepth; i++)
        quickMeta(FOLLOW_STATIC_LINK);

    Target* t = makeTarget(rsl);
    Mode* m = makeModeIRL(varOffset);

    quickPush(getSuffixOfType(s->type),t,m);
}

void quickPopRRT(opSuffix size)
{
    Target* t = makeTarget(rrt);
    ARG* arg = makeARG(t,makeMode(dir));
    ARG* args[2] = {arg,NULL};
    OP* op = makeOP(pop,size);
    quickIns(makeINS(op,args));
}

//Pop into a register (normal or XMM)
void quickPopReg(char* type, int registerNumber)
{
    Target* t = makeTargetReg(registerNumber);
    ARG* arg = makeARG(t,makeMode(dir));
    ARG* args[2] = {arg,NULL};
    OP* op = makeOP(pop,getSuffixOfType(type));
    quickIns(makeINS(op,args));
}

void quickPushReg(int regNumber, opSuffix size)
{
    Target* t = makeTargetReg(regNumber);
    quickPush(size,t,makeMode(dir));
}

void quickMoveRBPToRSL()
{
    Target* src = makeTarget(rbp);
    ARG* srcA = makeARG(src,makeMode(dir));

    Target* dest = makeTarget(rsl);
    ARG* destA = makeARG(dest,makeMode(dir));

    ARG* args[2] = {srcA, destA};

    OP* op = makeOP(move,bits_64);
    quickIns(makeINS(op,args));
}

void quickMoveRSLToRBP()
{
    Target* src = makeTarget(rsl);
    ARG* srcA = makeARG(src,makeMode(dir));

    Target* dest = makeTarget(rbp);
    ARG* destA = makeARG(dest,makeMode(dir));

    ARG* args[2] = {srcA,destA};

    OP* op = makeOP(move,bits_64);
    quickIns(makeINS(op,args));
}

void quickCheckTruthValue()
{
    Target* src = makeTargetIMI(1);
    ARG* srcA = makeARG(src,makeMode(dir));

    Target* dest = makeTarget(rrt);
    ARG* destA = makeARG(dest,makeMode(dir));

    ARG* args[2] = {srcA,destA};
    OP* op = makeOP(cmp,bits_8);
    quickIns(makeINS(op,args));
}

void quickJumpIfFalse(labelKind k, char* labelName)
{
    Target* t = makeTargetLabel(k,labelName);
    ARG* a = makeARG(t,makeMode(dir));
    ARG* args[2] = {a,NULL};
    OP* op = makeOP(jne,bits_64);
    quickIns(makeINS(op,args));
}

void quickUnconditionalJmp(labelKind k, char* labelName)
{
    Target* t = makeTargetLabel(k,labelName);
    ARG* a = makeARG(t,makeMode(dir));
    ARG* args[2] = {a,NULL};
    OP* op = makeOP(jmp,bits_64);
    quickIns(makeINS(op,args));
}

void quickArithmeticINS(opKind k, opSuffix size)  //L 'OP' R
{
    Target* src = makeTargetReg(1);
    ARG* srcA = makeARG(src, makeMode(dir));

    Target* dest = makeTargetReg(0);
    ARG* destA = makeARG(dest, makeMode(dir));

    ARG* args[2] = {srcA,destA};
    OP* op = makeOP(k,size);
    quickIns(makeINS(op,args));
    quickPushReg(0,size);
}

void quickCompareINS(opKind k, opSuffix size)
{
    Target* src, *dest;
    ARG* srcA, *destA, *args[2];
    OP* op;

    //Compare operands
    src = makeTargetReg(1);
    srcA = makeARG(src, makeMode(dir));

    dest = makeTargetReg(0);
    destA = makeARG(dest, makeMode(dir));

    args[0] = srcA;
    args[1] = destA;

    if(size == bits_64_d)
    {
        if(k == setg) //Flip operands
        {
            k = setl;
            args[0] = destA;
            args[1] = srcA;
        }
        else if(k == setge) //Flip operands
        {
            k = setle;
            args[0] = destA;
            args[1] = srcA;
        }
        k = translateCMPtoCMPSD(k);
    }

    op = makeOP(cmp,size);
    quickIns(makeINS(op,args));

    //Store result in reg0 (example: setle %bl)
    dest = makeTargetReg(0);
    destA = makeARG(dest,makeMode(dir));

    args[0] = destA;
    args[1] = NULL;

    op = makeOP(k,bits_8);
    quickIns(makeINS(op, args));
    quickPushReg(0,bits_8);
}

void quickBooleanINS(opKind k)
{
    Target* src = makeTargetReg(1);
    ARG* srcA = makeARG(src, makeMode(dir));

    Target* dest = makeTargetReg(0);
    ARG* destA = makeARG(dest, makeMode(dir));
    ARG* args[2] = {srcA,destA};

    OP* op = makeOP(k,bits_8);
    quickIns(makeINS(op,args));
    quickPushReg(0,bits_8);
}

void quickCallFun(char* funLabel)
{
    Target* funTarget = makeTargetLabel(function_label,funLabel);
    ARG* funARG = makeARG(funTarget, makeMode(dir));
    ARG* args[2] = {funARG,NULL};

    OP* callOP = makeOP(call,0);
    quickIns(makeINS(callOP,args));
}

void quickPushRSP()
{
    Target* dest = makeTarget(rsp);
    ARG* destA = makeARG(dest,makeMode(dir));
    OP* op = makeOP(push, bits_64);
    ARG* args[2] = {destA,NULL};
    quickIns(makeINS(op,args));
}

void quickMoveRBPToRSP()
{
    OP* op = makeOP(move, bits_64);
    Target* src = makeTarget(rbp);
    ARG* srcA = makeARG(src,makeMode(dir));
    Target* dest = makeTarget(rsp);
    ARG* destA = makeARG(dest,makeMode(dir));
    ARG* args[2] = {srcA, destA};
    quickIns(makeINS(op,args));
}

void quickPopRBP()
{
    OP* op = makeOP(pop, bits_64);
    Target* dest = makeTarget(rbp);
    ARG* destA = makeARG(dest,makeMode(dir));
    ARG* args[2] = {destA, NULL};
    quickIns(makeINS(op,args));
}

void quickPushRBP()
{
    OP* op = makeOP(push, bits_64);
    Target* dest = makeTarget(rbp);
    ARG* destA = makeARG(dest,makeMode(dir));
    ARG* args[2] = {destA, NULL};
    quickIns(makeINS(op,args));
}
void quickIncrementScopeOneLevel()
{
    OP* op = makeOP(move, bits_64);
    Target* src = makeTarget(rbp);
    ARG* srcA = makeARG(src,makeMode(ind));
    Target* dest = makeTarget(rbp);
    ARG* destA = makeARG(dest,makeMode(dir));
    ARG* args[2] = {srcA, destA};
    quickIns(makeINS(op,args));
}
void quickPushRRT(opSuffix suffix)
{
    OP* op = makeOP(push, suffix);
    Target* dest = makeTarget(rrt);
    ARG* destA = makeARG(dest,makeMode(dir));
    ARG* args[2] = {destA, NULL};
    quickIns(makeINS(op,args));
}

void quickPushDoubleLabel(char* label)
{
    Target* t = makeTargetLabel(double_label, label);
    ARG* arg = makeARG(t,makeMode(dir));
    OP* op = makeOP(push, bits_64_d);
    ARG* args[2] = {arg, NULL};
    quickIns(makeINS(op,args));
}

void addToLLFUN(FUNCTION* f)
{
    //Make a node containing f
    LLNFUN* node = (LLNFUN*)malloc(sizeof(LLNFUN));
    node->f = f;
    node->next = NULL;

    //Add node to LL
    if(funs->first == NULL) //First time we insert something
        funs->first = node;
    else
        funs->last->next = node;
    funs->last = node;
}

int whileCounter = 0;
int ifCounter = 0;
char* labelGenerator(labelKind kind) {
    char* res;
    char intString[20];
    if(kind == while_label)
    {
        sprintf(intString, "%d", whileCounter++);
        res = concatStr("while_",intString);
    }
    if(kind == if_label)
    {
        sprintf(intString, "%d", ifCounter++);
        res = concatStr("if_",intString);
    }
    return res;
}

void addToLLD(LLND* llnd)
{
    //Add node to LLD
    if(doubles->first == NULL) //First time we insert something
        doubles->first = llnd;
    else
        doubles->last->next = llnd;
    doubles->last = llnd;
}

int doubleCounter = 0;
char* doubleLabelGenerator(double val)
{
    char intAsString[20];
    sprintf(intAsString,"%d",doubleCounter++);

    char* label = concatStr("doubleconst_",intAsString);
    LLND* node = (LLND*)malloc(sizeof(LLND));
    node->val = val;
    node->label = label;
    node->next = NULL;
    addToLLD(node);

    return label;
}

int getIntFromSuffix(opSuffix size)
{
    switch(size)
    {
        case bits_8:
            return 1;
        case bits_32:
            return 4;
        case bits_64:
        case bits_64_d:
            return 8;
        default:
            return 0;
    }
}

int getSizeOfParameters(FPARAMETERNODE* fpn)
{
    int parameterSize = 0;
    FPARAMETERNODE* currentNode = fpn;
    while(currentNode != NULL)
    {
        parameterSize += getIntFromSuffix(getSuffixOfType(currentNode->current->type));
        currentNode = currentNode->next;
    }
    return parameterSize;
}

opSuffix getSuffixOfType(char* typeName)
{
    if (strcmp(typeName, "BOOLEAN") == 0)
        return bits_8;
    if (strcmp(typeName, "INT") == 0)
        return bits_32;
    if (strcmp(typeName, "DOUBLE") == 0)
        return bits_64_d;
    if (strcmp(typeName, "CHAR") == 0)
        return bits_8;
    return 0;
}

opKind translateCMPtoCMPSD(opKind k)
{
    if(k == setl)
        return setb;
    if(k == setle)
        return setbe;
    return k; //error
}



