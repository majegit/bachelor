#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"
#include "IntermediateCodeGeneration.h"

SYMBOLTABLE* currentScope;
LL* code = &(LL){NULL,NULL,0,0,0,0};
LLFUN* funs = &(LLFUN){NULL,NULL};
int depth = 0;
FUNCTION* currentFunction;

LL* icgTraversePROGRAM(PROGRAM* prog)
{
    currentScope = prog->sc->symbolTable;                          //Update pointer to global scope
    quickAddMeta(PROGRAM_PROLOGUE);

    int globalStackSpace = currentScope->nextVariableLabel;              //Stack space needed in global scope
    quickAddMetaWithInfo(ALLOCATE_STACK_SPACE, globalStackSpace);   //Push rbp and allocate stack space
    icgTraverseSTMTNODE(prog->sc->stmtnode);
    quickAddCallFun("main");

    quickAddMeta(PROGRAM_EPILOGUE);

    LLNFUN* currentNode = funs->first;
    while(currentNode != NULL)
    {
        icgTraverseFUNCTION(currentNode->f);
        currentNode = currentNode->next;
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
            Target* from, *to;
            ARG* argFrom, *argTo;
            EXP* e = s->val.assignS.val;
            int* varDepthAndOffset = staticLinkCount(s->val.assignS.name,currentScope); //Find relative nested depth and offset from rbp
            Mode* modeIRL = makeModeIRL(varDepthAndOffset[1]);
            if(e->kind == intK || e->kind == boolK || e->kind == charK)
                from = makeTargetIMI(e->val.intE);
            else if(e->kind == doubleK)
            {
                from = NULL; //TODO: add doubles
            }
            else if(e->kind == idK)
            {
                Target* memFromTarget;
                int* idDepthAndOffset = staticLinkCount(e->val.idE,currentScope);
                if(idDepthAndOffset[0] != 0)
                {
                    quickAddMoveRBPToRSL();
                    for(int i=0; i < idDepthAndOffset[0]; i++)
                        quickAddMeta(FOLLOW_STATIC_LINK);
                    memFromTarget = makeTarget(rsl,bits_64);
                }
                else
                    memFromTarget = makeTarget(rbp,bits_64);
                ARG* memFromArg = makeARG(memFromTarget,makeModeIRL(idDepthAndOffset[1]));

                Target* reg1 = makeTargetReg(getSizeOfId(e->val.idE),1);
                ARG* argReg1 = makeARG(reg1,makeMode(dir));

                ARG* args[2] = {memFromArg,argReg1};
                OP* moveMem = makeOP(move,getSizeOfId(e->val.idE));
                quickAddIns(makeINS(moveMem,args));
                free(idDepthAndOffset);
                from = makeTargetReg(getSizeOfId(s->val.assignS.name),1);
            }
            else
            {
                icgTraverseEXP(e);
                quickAddPopRRT(getSizeOfType(e->type));
                from = makeTarget(rrt,getSizeOfId(s->val.assignS.name));
            }
            if(varDepthAndOffset[0] != 0) //The variable is NOT in the current scope
            {
                quickAddMoveRBPToRSL();
                for(int i=0; i < varDepthAndOffset[0]; i++)
                    quickAddMeta(FOLLOW_STATIC_LINK);
                to = makeTarget(rsl,bits_64);
            }
            else
                to = makeTarget(rbp,bits_64);
            argFrom = makeARG(from,makeMode(dir));
            argTo = makeARG(to,modeIRL);

            ARG* args[2] = {argFrom, argTo};
            OP* op = makeOP(move,getSizeOfId(s->val.assignS.name));
            quickAddIns(makeINS(op,args));

            free(varDepthAndOffset); //Free malloc'ed memory
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

            char* endelseLabel = "";
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
            SYMBOL *funSymbol = lookupSymbolFun(currentFunction->name, currentScope);
            if (depth != 0) {
                quickAddMoveRBPToRSL();
                for (int i = 0; i < depth; i++)
                    quickAddMeta(FOLLOW_STATIC_LINK);
                quickAddMoveRSLToRBP();
            }
            char *endLabel = concatStr("end", funSymbol->label);
            quickAddUnconditionalJmp(endfunction_label, endLabel);
            break;
        }
        case printK:
        {
            opSize typeSize = getSizeOfType(s->val.printS->type);
            icgTraverseEXP(s->val.printS);  //TODO: DOUBLES

            char* printFun = concatStr("print",s->val.printS->type);
            if(strcmp(s->val.printS->type,"BOOLEAN") == 0)
                code->pFlagBOOLEAN = 1;
            if(strcmp(s->val.printS->type,"CHAR") == 0)
                code->pFlagCHAR = 1;
            if(strcmp(s->val.printS->type,"INT") == 0)
                code->pFlagINT = 1;
            if(strcmp(s->val.printS->type,"DOUBLE") == 0)
                code->pFlagDOUBLE = 1;

            quickAddCallFun(printFun);

            Target* t = makeTarget(rsp,bits_64);
            ARG* rsp = makeARG(t,makeMode(dir));
            Target* imiT = makeTargetIMI(getIntFromopSize(typeSize));
            ARG* imiArg = makeARG(imiT,makeMode(dir));
            ARG* args[2] = {imiArg,rsp};
            OP* op = makeOP(add, bits_64);
            quickAddIns(makeINS(op,args));
            break;
        }
        case varDeclK:
        {
            if(s->val.varDeclS.value == NULL)
                break;

            Target* from, *to;
            ARG* argFrom, *argTo;
            EXP* e = s->val.varDeclS.value;
            int* varDepthAndOffset = staticLinkCount(s->val.varDeclS.name,currentScope); //Find relative nested depth and offset from rbp
            Mode* modeIRL = makeModeIRL(varDepthAndOffset[1]);
            if(varDepthAndOffset[0] != 0) //The variable is NOT in the current scope
            {
                quickAddMoveRBPToRSL();
                for(int i=0; i < varDepthAndOffset[0]; i++)
                    quickAddMeta(FOLLOW_STATIC_LINK);
                to = makeTarget(rsl,bits_64);
            }
            else
                to = makeTarget(rbp,bits_64);
            if(e->kind == intK || e->kind == boolK || e->kind == charK)
                from = makeTargetIMI(e->val.intE);
            else if(e->kind == doubleK)
            {
                from = NULL; //TODO: add doubles
            }
            else
            {
                icgTraverseEXP(e);
                quickAddPopRRT(getSizeOfType(s->val.varDeclS.type));
                from = makeTarget(rrt,getSizeOfType(s->val.varDeclS.type));
            }
            argFrom = makeARG(from,makeMode(dir));
            argTo = makeARG(to,modeIRL);

            ARG* args[2] = {argFrom, argTo};
            OP* op = makeOP(move,getSizeOfType(s->val.varDeclS.type));
            quickAddIns(makeINS(op,args));
            free(varDepthAndOffset); //Free malloc'ed memory
            break;
        }
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
            quickAddPushId(e->val.idE);
            break;
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
            //TODO: add doubles
            break;
        case binopK:
            icgTraverseEXP(e->val.binopE.left);
            icgTraverseEXP(e->val.binopE.right);

            char* op = e->val.binopE.operator;
            opSize size = getSizeOfType(e->val.binopE.right->type);

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
            quickAddPushReg(1,getSizeOfType(e->type));
            break;
        case funK:
        {
            icgTraverseAPARAMETERNODE(e->val.funE.aparameternode);
            SYMBOL* funSymbol = lookupSymbolFun(e->val.funE.id,currentScope);
            quickAddCallFun(funSymbol->label);
            int sizeOfParameters = getSizeOfParameters(funSymbol->fpn);
            quickAddMetaWithInfo(DEALLOCATE_ARGUMENTS,sizeOfParameters);
            quickAddPushRRT();
            break;
        }
    }
    if(e->coerceTo != NULL)
    {
        //TODO: pop into reg 1, do the coercion, and push back onto stack
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

    char* funLabel = lookupSymbolFun(f->name,f->body->symbolTable->par)->label;//funLabel = funX_<function name>
    quickAddMetaString(FUNCTION_DECLARATION,funLabel); //.type funX_<function name>, @function
    quickAddLabelString(function_label,funLabel);       //funX_<function name>
    currentScope = f->body->symbolTable;                     //update currentScope
    int stackSpace = currentScope->nextVariableLabel;

    quickAddMeta(CALLEE_PROLOGUE);                      //Possibly nothing
    quickAddMetaWithInfo(ALLOCATE_STACK_SPACE,stackSpace);
    quickAddMeta(CALLEE_SAVE);                          //Push callee save registers

    icgTraverseSTMTNODE(f->body->stmtnode);                  //Traverse contents of function

    char* endfunLabel = concatStr("end",funLabel);
    quickAddLabelString(endfunction_label,endfunLabel); //endfunX_<function name>
    quickAddPopRRT(getSizeOfType(f->returnType));
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

Target* makeTarget(targetKind k, opSize s)
{
    Target* t = (Target*)malloc(sizeof(Target));
    t->targetK = k;
    t->size = s;
    return t;
}

Target* makeTargetLabel(labelKind k, char* name)
{
    Target* t = makeTarget(mem,0);
    t->labelK = k;
    t->labelName = name;
    return t;
}

Target* makeTargetReg(opSize s, int regNumber)
{
    Target* t = makeTarget(reg,s);
    t->additionalInfo = regNumber;
    return t;
}

Target* makeTargetIMI(int imiValue)
{
    Target* t = makeTarget(imi,0);
    t->additionalInfo = imiValue;
    return t;
}

OP* makeOP(opKind opK, opSize size)
{
    OP* op = (OP*)malloc(sizeof(OP));
    op->opK = opK;
    op->size = size;
    return op;
}

OP* makeOPMeta(metaKind k, int metaInfo, char* metaLabel)
{
    OP* op = makeOP(meta,bits_64);
    op->opK = meta;
    op->metaK = k;
    op->metaInformation = metaInfo;
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
    OP* op = makeOPMeta(metaK,0,NULL);
    ARG* args[2] = {NULL,NULL};
    quickAddIns(makeINS(op,args));
};

void quickAddMetaWithInfo(metaKind metaK, int metaInformation)
{
    OP* op = makeOPMeta(metaK,metaInformation,NULL);
    ARG* args[2] = {NULL,NULL};
    quickAddIns(makeINS(op,args));
}

void quickAddMetaString(metaKind metaK, char* str)
{
    OP* op = makeOPMeta(metaK,0,str);
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

void quickAddPush(opSize size, Target* target, Mode* mode)
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
void quickAddPushId(char* name)
{
    Target* t;
    int* varDepthAndOffset = staticLinkCount(name,currentScope);
    if(varDepthAndOffset[0] != 0)
    {
        quickAddMoveRBPToRSL();
        for(int i=0; i < varDepthAndOffset[0]; i++)
            quickAddMeta(FOLLOW_STATIC_LINK);
        t = makeTarget(rsl,bits_64);
    }
    else
        t = makeTarget(rbp,bits_64);

    Mode* m = makeModeIRL(varDepthAndOffset[1]);
    quickAddPush(getSizeOfId(name),t,m);
    free(varDepthAndOffset); //Free malloc'ed memory
}

void quickAddPopRRT(opSize size)
{
    Target* t = makeTarget(rrt,size);
    ARG* arg = makeARG(t,makeMode(dir));
    ARG* args[2] = {arg,NULL};
    OP* op = makeOP(pop,size);
    quickAddIns(makeINS(op,args));
}

//Pop into a register
void quickAddPopReg(opSize size, int registerNumber)
{
    Target* t = makeTargetReg(size,registerNumber);
    ARG* arg = makeARG(t,makeMode(dir));
    ARG* args[2] = {arg,NULL};
    OP* op = makeOP(pop,size);
    quickAddIns(makeINS(op,args));
}

void quickAddPushReg(int regNumber, opSize size)
{
    Target* t = makeTargetReg(size,regNumber);
    quickAddPush(size,t,makeMode(dir));
}

void quickAddMoveRBPToRSL()
{
    Target* rbpTarget = makeTarget(rbp,bits_64);
    ARG* rbpARG = makeARG(rbpTarget,makeMode(dir));

    Target* rslTarget = makeTarget(rsl,bits_64);
    ARG* rslARG = makeARG(rslTarget,makeMode(dir));

    ARG* args[2] = {rbpARG, rslARG};

    OP* op = makeOP(move,bits_64);
    quickAddIns(makeINS(op,args));
}

void quickAddMoveRSLToRBP()
{
    Target* rbpTarget = makeTarget(rbp,bits_64);
    ARG* rbpARG = makeARG(rbpTarget,makeMode(dir));

    Target* rslTarget = makeTarget(rsl,bits_64);
    ARG* rslARG = makeARG(rslTarget,makeMode(dir));

    ARG* args[2] = {rslARG,rbpARG};

    OP* op = makeOP(move,bits_64);
    quickAddIns(makeINS(op,args));
}

void quickAddCheckTruthValue()
{
    ARG* from = makeARG(makeTargetIMI(1),makeMode(dir));
    ARG* to = makeARG(makeTarget(rrt,bits_64),makeMode(dir));
    ARG* args[2] = {from,to};
    OP* op = makeOP(cmp,bits_64);
    quickAddIns(makeINS(op,args));
}

void quickAddJumpIfFalse(labelKind k, char* labelName)
{
    Target* t = makeTargetLabel(k,labelName);
    ARG* arg = makeARG(t,makeMode(dir));
    ARG* args[2] = {arg,NULL};
    OP* op = makeOP(jne,bits_64);
    quickAddIns(makeINS(op,args));
}

void quickAddUnconditionalJmp(labelKind k, char* labelName)
{
    Target* t = makeTargetLabel(k,labelName);
    ARG* arg = makeARG(t,makeMode(dir));
    ARG* args[2] = {arg,NULL};
    OP* op = makeOP(jmp,bits_64);
    quickAddIns(makeINS(op,args));
}

void quickAddArithmeticINS(opKind k, opSize size)  //L 'OP' R
{
    quickAddPopReg(size,2); //Right side of binop
    quickAddPopReg(size,1); //Left side of binop

    Target* rightEXP = makeTargetReg(size,2);
    ARG* argRight = makeARG(rightEXP, makeMode(dir));

    Target* leftEXP = makeTargetReg(size,1);
    ARG* argLeft = makeARG(leftEXP, makeMode(dir));

    ARG* args[2] = {argRight,argLeft};

    OP* op = makeOP(k,size);
    quickAddIns(makeINS(op,args));
}

void quickAddCompareINS(opKind k, opSize size)
{
    quickAddPopReg(size, 1); //pop reg2  #Right side of binop
    quickAddPopReg(size, 2); //pop reg1  #Left side of binop

    Target* tLeft = makeTargetReg(size,2);
    ARG* argLeft = makeARG(tLeft, makeMode(dir));

    Target* tRight = makeTargetReg(size,1);
    ARG* argRight = makeARG(tRight, makeMode(dir));

    ARG* args[2] = {argRight,argLeft};

    OP* cmpOP = makeOP(cmp,size);
    quickAddIns(makeINS(cmpOP,args));

    Target* resultRegister = makeTargetReg(bits_8,1);
    ARG* arg = makeARG(resultRegister,makeMode(dir));
    ARG* argsSet[2] = {arg,NULL};
    OP* setOP = makeOP(k,bits_8);
    quickAddIns(makeINS(setOP,argsSet)); //set<k> reg2  #8 bits register
}

void quickAddBooleanINS(opKind k)
{
    quickAddPopReg(bits_8,2); //Right side of binop
    quickAddPopReg(bits_8,1); //Left side of binop

    Target* rightEXP = makeTargetReg(bits_8,2);
    ARG* argRight = makeARG(rightEXP, makeMode(dir));

    Target* leftEXP = makeTargetReg(bits_8,1);
    ARG* argLeft = makeARG(leftEXP, makeMode(dir));
    ARG* args[2] = {argRight,argLeft};

    OP* boolOP = makeOP(k,bits_8);
    quickAddIns(makeINS(boolOP,args));
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
    Target* t = makeTarget(rsp,bits_64);
    ARG* arg = makeARG(t,makeMode(dir));
    OP* op = makeOP(push, bits_64);
    ARG* args[2] = {arg,NULL};
    quickAddIns(makeINS(op,args));
}

void quickAddMoveRBPToRSP()
{
    Target* from = makeTarget(rbp,bits_64);
    ARG* argFrom = makeARG(from,makeMode(dir));
    Target* to = makeTarget(rsp,bits_64);
    ARG* argTo = makeARG(to,makeMode(dir));
    OP* op = makeOP(move, bits_64);
    ARG* args[2] = {argFrom, argTo};
    quickAddIns(makeINS(op,args));
}

void quickAddPopRBP()
{
    Target* t = makeTarget(rbp,bits_64);
    ARG* arg = makeARG(t,makeMode(dir));
    OP* op = makeOP(pop, bits_64);
    ARG* args[2] = {arg, NULL};
    quickAddIns(makeINS(op,args));
}

void quickAddPushRRT()
{
    Target* t = makeTarget(rrt,bits_64);
    ARG* arg = makeARG(t,makeMode(dir));
    OP* op = makeOP(push, bits_64);
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

int getIntFromopSize(opSize size)
{
    switch(size)
    {
        case bits_8:
            return 1;
        case bits_32:
            return 4;
        case bits_64:
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
        parameterSize += getIntFromopSize(getSizeOfType(currentNode->current->type));
        currentNode = currentNode->next;
    }
    return parameterSize;
}

opSize getSizeOfType(char* typeName)
{
    if (strcmp(typeName, "BOOLEAN") == 0)
        return bits_8;
    if (strcmp(typeName, "INT") == 0)
        return bits_32;
    if (strcmp(typeName, "DOUBLE") == 0)
        return bits_64;
    if (strcmp(typeName, "CHAR") == 0)
        return bits_8;
    return 0;
}

opSize getSizeOfId(char* idName)
{
    SYMBOL* id = lookupSymbolVar(idName,currentScope);
    return getSizeOfType(id->type);
}

int isCompareOp(char* operator)
{
    return 1;
    //if(strcmp(operator,"-"))
}

int isArithmeticOp(char* operator)
{
    if(strcmp(operator,"+"))
        return 1;
    if(strcmp(operator,"-"))
        return 1;
    if(strcmp(operator,"*"))
        return 1;
    if(strcmp(operator,"/"))
        return 1;
    return 0;
}

int isBooleanOp(char* operator)
{

}


