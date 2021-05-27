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
    quickAddMeta(PROGRAM_PROLOGUE);

    int globalStackSpace = currentScope->nextVariableLabel;              //Stack space needed in global scope
    quickAddMetaWithInfo(ALLOCATE_STACK_SPACE, globalStackSpace);   //Push rbp and allocate stack space
    icgTraverseSTMTNODE(prog->sc->stmtnode);

    quickAddMeta(PROGRAM_EPILOGUE);

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
        quickAddIns(makeINS(op,args));
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
    quickAddMetaWithInfo(ALLOCATE_STACK_SPACE, compStackSpace);   //Push rbp and allocate stack space
    icgTraverseSTMTNODE(sc->stmtnode);
    quickAddMetaWithInfo(DEALLOCATE_STACK_SPACE, compStackSpace); //Deallocate stack space and pop rbp

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

            quickAddLabelString(while_label, labelName);       //while_X:
            icgTraverseEXP(s->val.whileS.guard);                    //Guard
            quickAddPopRRT(bits_8);                             //Move boolean to rrt
            quickAddCheckTruthValue();                              //cmp rrt, $1
            quickAddJumpIfFalse(endwhile_label,endlabelName);    //jne endwhile_X
            icgTraverseSTMTCOMP(s->val.whileS.body);                //generate the code for the body of the whileloop
            quickAddLabelString(endwhile_label, endlabelName); //endwhile_X:
            break;
        }
        case assignK:
        {
            OP* op;
            Target* src, *dest;
            ARG* srcA, *destA;
            EXP* e = s->val.assignS.val;

            icgTraverseEXP(e);
            quickAddPopRRT(getSuffixOfType(e->type));

            int varDepth = getSymbolDepth(s->val.assignS.symbol, currentScope); //Scope depth
            int varOffset = s->val.assignS.symbol->offset; //Offset from base pointer

            quickAddMoveRBPToRSL();
            for(int i=0; i < varDepth; i++)
                quickAddMeta(FOLLOW_STATIC_LINK);

            op = makeOP(move,getSuffixOfType(e->type));
            src = makeTarget(rrt);
            srcA = makeARG(src,makeMode(dir));
            dest = makeTarget(rsl);
            destA = makeARG(dest,makeModeIRL(varOffset));

            ARG* args[2] = {srcA, destA};
            quickAddIns(makeINS(op,args));
            break;
        }
        case ifElseK:
        {
            int elsePart = s->val.ifElseS.elsebody != NULL;           //Check if there is an else part
            char* labelName = labelGenerator(if_label);        //Generate if_X label

            quickAddLabelString(if_label, labelName);          //if_X:
            icgTraverseEXP(s->val.ifElseS.cond);                    //Guard
            quickAddPopRRT(bits_8);                             //Move boolean to rrt
            quickAddCheckTruthValue();                              //cmp rrt, $1
            labelName = concatStr("end",labelName);             //Generate endif_X label
            quickAddJumpIfFalse(endif_label,labelName);          //jne endif_X
            icgTraverseSTMTCOMP(s->val.ifElseS.ifbody);             //if-body

            char* endelseLabel;
            if(elsePart)
            {
                endelseLabel = concatStr("endelse",labelName+5);//Generate endelse_X
                quickAddUnconditionalJmp(endelse_label,endelseLabel); //jmp endelse_X
            }
            quickAddLabelString(endif_label, labelName);        //endif_X:
            if(elsePart)
            {
                icgTraverseSTMTCOMP(s->val.ifElseS.elsebody);        //else-body
                quickAddLabelString(endelse_label,endelseLabel);//endelse_X:
            }
            break;
        }
        case returnK:
        {
            icgTraverseEXP(s->val.returnS);
            SYMBOL* funSymbol = lookupSymbolFunName(currentFunction->name, currentScope);

            quickAddMoveRBPToRSL();
            for (int i = 0; i < depth; i++)
                quickAddMeta(FOLLOW_STATIC_LINK);
            quickAddMoveRSLToRBP();

            char *endLabel = concatStr("end", funSymbol->label);
            quickAddUnconditionalJmp(endfunction_label, endLabel);
            break;
        }
        case printK:
        {
            opSuffix typeSize = getSuffixOfType(s->val.printS->type);
            icgTraverseEXP(s->val.printS);  //TODO: DOUBLES

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


            quickAddCallFun(printFun);

            //Decrement stack pointer (reverse push arguments)
            Target* src = makeTargetIMI(getIntFromSuffix(typeSize));
            ARG* srcA = makeARG(src,makeMode(dir));

            Target* dest = makeTarget(rsp);
            ARG* destA = makeARG(dest,makeMode(dir));

            ARG* args[2] = {srcA,destA};
            OP* op = makeOP(add, bits_64);
            quickAddIns(makeINS(op,args));

            quickAddCallFun("printNewline");
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
            quickAddPushId(e->val.idE.symbol);
            break;
        }
        case intK:
        {
            Target* target = makeTargetIMI(e->val.intE); //e->val.charE = e->val.boolE = e->val.intE, they are all ints in an union
            ARG* arg = makeARG(target, makeMode(dir));
            ARG* args[2] = {arg, NULL};
            OP* op = makeOP(push, bits_32);
            quickAddIns(makeINS(op, args));
            break;
        }
        case boolK:
        case charK:
        {
            Target* target = makeTargetIMI(e->val.charE); //e->val.charE = e->val.boolE, they are both ints in an union
            ARG* arg = makeARG(target, makeMode(dir));
            ARG* args[2] = {arg, NULL};
            OP* op = makeOP(push, bits_8);
            quickAddIns(makeINS(op, args));
            break;
        }
        case doubleK:
        {
            char* dLabel = doubleLabelGenerator(e->val.doubleE);
            quickAddPushDoubleLabel(dLabel);
            break;
        }
        case binopK:
        {
            icgTraverseEXP(e->val.binopE.left);
            icgTraverseEXP(e->val.binopE.right);

            char* op = e->val.binopE.operator;
            opSuffix size = getSuffixOfType(e->val.binopE.right->type); //Using the fact that for all operations, the operands are same type


            quickAddPopReg(size,1); //Right side of binop
            quickAddPopReg(size,0); //Left side of binop

            if(strcmp(op,"-") == 0)
                quickAddArithmeticINS(sub,size);
            else if (strcmp(op,"+") == 0)
                quickAddArithmeticINS(add,size);
            else if (strcmp(op,"*") == 0)
                quickAddArithmeticINS(mul,size);
            else if (strcmp(op,"/") == 0)
                quickAddArithmeticINS(divi,size);
            else if (strcmp(op,"L") == 0)
                quickAddCompareINS(setl,size);
            else if (strcmp(op,"G") == 0)
                quickAddCompareINS(setg,size);
            else if (strcmp(op,"LEQ") == 0)
                quickAddCompareINS(setle,size);
            else if (strcmp(op,"GEQ") == 0)
                quickAddCompareINS(setge,size);
            else if (strcmp(op,"EQ") == 0)
                quickAddCompareINS(sete,size);
            else if (strcmp(op,"NEQ") == 0)
                quickAddCompareINS(setne,size);
            else if (strcmp(op,"AND") == 0)
                quickAddBooleanINS(and);
            else if (strcmp(op,"OR") == 0)
                quickAddBooleanINS(or);

            break;
        }
        case funK:
        {
            icgTraverseAPARAMETERNODE(e->val.funE.aparameternode);
            SYMBOL* funSymbol = lookupSymbolFunName(e->val.funE.id,currentScope);

            int scopeDepth = getSymbolDepth(funSymbol,currentScope);
            quickAddPushRBP(); //Save old base pointer
            for(int i = 0; i<scopeDepth; ++i)
                quickAddIncrementScopeOneLevel(); //Movq (%rbp), %rbp
            quickAddCallFun(funSymbol->label);
            quickAddPopRBP();
            int sizeOfParameters = getSizeOfParameters(funSymbol->fpn);

            OP* op = makeOP(add,bits_64);

            Target* src = makeTargetIMI(sizeOfParameters);
            ARG* srcA = makeARG(src,makeMode(dir));

            Target* dest = makeTarget(rsp);
            ARG* destA = makeARG(dest,makeMode(dir));

            ARG* args[2] = {srcA,destA};
            quickAddIns(makeINS(op,args));

            quickAddPushRRT(getSuffixOfType(funSymbol->type));
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
            quickAddIns(makeINS(op,args));

            //Remove the top of stack (uncoerced expression)
            op = makeOP(add,bits_64);

            src = makeTargetIMI(getIntFromSuffix(suffixPre));
            srcA = makeARG(src,makeMode(dir));

            dest = makeTarget(rsp);
            destA = makeARG(dest,makeMode(dir));

            args[0] = srcA;
            args[1] = destA;
            quickAddIns(makeINS(op,args));

            //Push register 0 onto the stack
            op = makeOP(push,suffixPost);

            src = makeTargetReg(0);
            srcA = makeARG(src,makeMode(dir));

            args[0] = srcA;
            args[1] = destA;
            quickAddIns(makeINS(op,args));
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

    char* funLabel = lookupSymbolFunName(f->name,f->body->symbolTable->par)->label;//funLabel = funX_<function name>
    quickAddMetaString(FUNCTION_DECLARATION,funLabel); //.type funX_<function name>, @function
    quickAddLabelString(function_label,funLabel);       //funX_<function name>
    currentScope = f->body->symbolTable;                     //update currentScope
    int stackSpace = currentScope->nextVariableLabel;

    quickAddMetaWithInfo(ALLOCATE_STACK_SPACE,stackSpace);
    quickAddMeta(CALLEE_SAVE);                          //Push callee save registers

    icgTraverseSTMTNODE(f->body->stmtnode);                  //Traverse contents of function

    char* endfunLabel = concatStr("end",funLabel);
    quickAddLabelString(endfunction_label,endfunLabel); //endfunX_<function name>
    quickAddPopRRT(getSuffixOfType(f->returnType));
    quickAddMoveRBPToRSP();
    quickAddPopRBP();
    quickAddMeta(CALLEE_RESTORE);                       //Pop callee save registers
    quickAddMeta(CALLEE_EPILOGUE);                      //ret

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
void quickAddIns(INS* ins)
{
    LLN* node = makeLLN(ins);
    addToLL(node);
}

void quickAddMeta(metaKind metaK) {
    OP* op = makeOPMeta(metaK,0,0,NULL);
    ARG* args[2] = {NULL,NULL};
    quickAddIns(makeINS(op,args));
};

void quickAddMetaWithInfo(metaKind metaK, int metaInt)
{
    OP* op = makeOPMeta(metaK,metaInt,0,NULL);
    ARG* args[2] = {NULL,NULL};
    quickAddIns(makeINS(op,args));
}

void quickAddMetaString(metaKind metaK, char* str)
{
    OP* op = makeOPMeta(metaK,0,0,str);
    ARG* args[2] = {NULL,NULL};
    quickAddIns(makeINS(op,args));
}

void quickAddLabelString(labelKind kind, char* name)
{
    Target* t = makeTargetLabel(kind,name);
    ARG* arg = makeARG(t, makeMode(dir));
    ARG* args[2] = {arg, NULL};
    OP* op = makeOP(label,bits_64);
    quickAddIns(makeINS(op,args));
}

void quickAddPush(opSuffix size, Target* target, Mode* mode)
{
    ARG* arg = makeARG(target, mode);
    ARG* args[2] = {arg,NULL};
    OP* op = makeOP(push,size);
    quickAddIns(makeINS(op, args));
}

void quickAddPop(Target* t, Mode* m)
{
    ARG* arg = makeARG(t, m);
    ARG* args[2] = {arg, NULL};
    OP* op = makeOP(pop,bits_64);
    quickAddIns(makeINS(op, args));
}

//Pushes a variable (identifier) on the stack
void quickAddPushId(SYMBOL* s)
{
    int varDepth = getSymbolDepth(s,currentScope); //Scope depth
    int varOffset = s->offset;

    quickAddMoveRBPToRSL();
    for(int i=0; i < varDepth; i++)
        quickAddMeta(FOLLOW_STATIC_LINK);

    Target* t = makeTarget(rsl);
    Mode* m = makeModeIRL(varOffset);

    quickAddPush(getSuffixOfType(s->type),t,m);
}

void quickAddPopRRT(opSuffix size)
{
    Target* t = makeTarget(rrt);
    ARG* arg = makeARG(t,makeMode(dir));
    ARG* args[2] = {arg,NULL};
    OP* op = makeOP(pop,size);
    quickAddIns(makeINS(op,args));
}

//Pop into a register (normal or XMM)
void quickAddPopReg(opSuffix size, int registerNumber)
{
    Target* t = makeTargetReg(registerNumber);
    ARG* arg = makeARG(t,makeMode(dir));
    ARG* args[2] = {arg,NULL};
    OP* op = makeOP(pop,size);
    quickAddIns(makeINS(op,args));
}

void quickAddPushReg(int regNumber, opSuffix size)
{
    Target* t = makeTargetReg(regNumber);
    quickAddPush(size,t,makeMode(dir));
}

void quickAddMoveRBPToRSL()
{
    Target* src = makeTarget(rbp);
    ARG* srcA = makeARG(src,makeMode(dir));

    Target* dest = makeTarget(rsl);
    ARG* destA = makeARG(dest,makeMode(dir));

    ARG* args[2] = {srcA, destA};

    OP* op = makeOP(move,bits_64);
    quickAddIns(makeINS(op,args));
}

void quickAddMoveRSLToRBP()
{
    Target* src = makeTarget(rsl);
    ARG* srcA = makeARG(src,makeMode(dir));

    Target* dest = makeTarget(rbp);
    ARG* destA = makeARG(dest,makeMode(dir));

    ARG* args[2] = {srcA,destA};

    OP* op = makeOP(move,bits_64);
    quickAddIns(makeINS(op,args));
}

void quickAddCheckTruthValue()
{
    Target* src = makeTargetIMI(1);
    ARG* srcA = makeARG(src,makeMode(dir));

    Target* dest = makeTarget(rrt);
    ARG* destA = makeARG(dest,makeMode(dir));

    ARG* args[2] = {srcA,destA};
    OP* op = makeOP(cmp,bits_8);
    quickAddIns(makeINS(op,args));
}

void quickAddJumpIfFalse(labelKind k, char* labelName)
{
    Target* t = makeTargetLabel(k,labelName);
    ARG* a = makeARG(t,makeMode(dir));
    ARG* args[2] = {a,NULL};
    OP* op = makeOP(jne,bits_64);
    quickAddIns(makeINS(op,args));
}

void quickAddUnconditionalJmp(labelKind k, char* labelName)
{
    Target* t = makeTargetLabel(k,labelName);
    ARG* a = makeARG(t,makeMode(dir));
    ARG* args[2] = {a,NULL};
    OP* op = makeOP(jmp,bits_64);
    quickAddIns(makeINS(op,args));
}

void quickAddArithmeticINS(opKind k, opSuffix size)  //L 'OP' R
{
    Target* src = makeTargetReg(1);
    ARG* srcA = makeARG(src, makeMode(dir));

    Target* dest = makeTargetReg(0);
    ARG* destA = makeARG(dest, makeMode(dir));

    ARG* args[2] = {srcA,destA};
    OP* op = makeOP(k,size);
    quickAddIns(makeINS(op,args));
    quickAddPushReg(0,size);
}

void quickAddCompareINS(opKind k, opSuffix size)
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
    quickAddIns(makeINS(op,args));

    //Store result in reg0 (example: setle %bl)
    dest = makeTargetReg(0);
    destA = makeARG(dest,makeMode(dir));

    args[0] = destA;
    args[1] = NULL;

    op = makeOP(k,bits_8);
    quickAddIns(makeINS(op, args));
    quickAddPushReg(0,bits_8);
}

void quickAddBooleanINS(opKind k)
{
    Target* src = makeTargetReg(1);
    ARG* srcA = makeARG(src, makeMode(dir));

    Target* dest = makeTargetReg(0);
    ARG* destA = makeARG(dest, makeMode(dir));
    ARG* args[2] = {srcA,destA};

    OP* op = makeOP(k,bits_8);
    quickAddIns(makeINS(op,args));
    quickAddPushReg(0,bits_8);
}

void quickAddCallFun(char* funLabel)
{
    Target* funTarget = makeTargetLabel(function_label,funLabel);
    ARG* funARG = makeARG(funTarget, makeMode(dir));
    ARG* args[2] = {funARG,NULL};

    OP* callOP = makeOP(call,0);
    quickAddIns(makeINS(callOP,args));
}

void quickAddPushRSP()
{
    Target* dest = makeTarget(rsp);
    ARG* destA = makeARG(dest,makeMode(dir));
    OP* op = makeOP(push, bits_64);
    ARG* args[2] = {destA,NULL};
    quickAddIns(makeINS(op,args));
}

void quickAddMoveRBPToRSP()
{
    OP* op = makeOP(move, bits_64);
    Target* src = makeTarget(rbp);
    ARG* srcA = makeARG(src,makeMode(dir));
    Target* dest = makeTarget(rsp);
    ARG* destA = makeARG(dest,makeMode(dir));
    ARG* args[2] = {srcA, destA};
    quickAddIns(makeINS(op,args));
}

void quickAddPopRBP()
{
    OP* op = makeOP(pop, bits_64);
    Target* dest = makeTarget(rbp);
    ARG* destA = makeARG(dest,makeMode(dir));
    ARG* args[2] = {destA, NULL};
    quickAddIns(makeINS(op,args));
}

void quickAddPushRBP()
{
    OP* op = makeOP(push, bits_64);
    Target* dest = makeTarget(rbp);
    ARG* destA = makeARG(dest,makeMode(dir));
    ARG* args[2] = {destA, NULL};
    quickAddIns(makeINS(op,args));
}
void quickAddIncrementScopeOneLevel()
{
    OP* op = makeOP(move, bits_64);
    Target* src = makeTarget(rbp);
    ARG* srcA = makeARG(src,makeMode(ind));
    Target* dest = makeTarget(rbp);
    ARG* destA = makeARG(dest,makeMode(dir));
    ARG* args[2] = {srcA, destA};
    quickAddIns(makeINS(op,args));
}
void quickAddPushRRT(opSuffix suffix)
{
    OP* op = makeOP(push, suffix);
    Target* dest = makeTarget(rrt);
    ARG* destA = makeARG(dest,makeMode(dir));
    ARG* args[2] = {destA, NULL};
    quickAddIns(makeINS(op,args));
}

void quickAddPushDoubleLabel(char* label)
{
    Target* t = makeTargetLabel(double_label, label);
    ARG* arg = makeARG(t,makeMode(dir));
    OP* op = makeOP(push, bits_64_d);
    ARG* args[2] = {arg, NULL};
    quickAddIns(makeINS(op,args));
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

opSuffix getSizeOfId(char* idName)
{
    SYMBOL* id = lookupSymbolVarName(idName,currentScope);
    return getSuffixOfType(id->type);
}

opKind translateCMPtoCMPSD(opKind k)
{
    if(k == setl)
        return setb;
    if(k == setle)
        return setbe;
    return k; //error
}



