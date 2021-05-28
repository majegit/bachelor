#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Tree.h"

extern int lineno;

EXP* makeEXPid(char* id)
{
    EXP* e;
    e = (EXP*)malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = idK;
    e->val.idE.id = id;
    e->val.idE.symbol = NULL;
    return e;
}

EXP* makeEXPchar(char charval)
{
    EXP* e;
    e = (EXP* )malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = charK;
    e->val.charE = charval;
    e->type = "CHAR";
    return e;
}

EXP* makeEXPint(int intval)
{
    EXP* e;
    e = (EXP* )malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = intK;
    e->val.intE = intval;
    e->type = "INT";
    return e;
}

EXP* makeEXPbool(int boolval)
{
    EXP* e;
    e = (EXP* )malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = boolK;
    e->val.boolE = boolval;
    e->type = "BOOLEAN";
    return e;
}

EXP* makeEXPdouble(double doubleval)
{
    EXP* e;
    e = (EXP* )malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = doubleK;
    e->val.doubleE = doubleval;
    e->type = "DOUBLE";
    return e;
}

EXP* makeEXPbinop(EXP* left, char* operator, EXP* right)
{
    EXP* e;
    e = (EXP* )malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = binopK;
    e->val.binopE.left = left;
    e->val.binopE.right = right;
    e->val.binopE.operator = operator;
    return e;
}

EXP* makeEXPfun(char* id, APARAMETERNODE* aparameternode)
{
    EXP* e;
    e = (EXP*)malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = funK;
    e->val.funE.id = id;
    e->val.funE.aparameternode = aparameternode;
    return e;
}

EXP* makeEXPcoerce(char* targetType, EXP* exp)
{
    EXP* e;
    e = (EXP*)malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = coerceK;
    e->val.coerceE = exp;
    e->type = targetType;
    return e;
}

EXP* makeEXPUnaryMinusId(char* id)
{
    EXP* eId;
    eId = (EXP*)malloc(sizeof(EXP));
    eId->lineno = lineno;
    eId->kind = idK;
    eId->val.idE.id = id;
    eId->val.idE.symbol = NULL;

    EXP* eZero;
    eZero = (EXP*)malloc(sizeof(EXP));
    eZero->lineno = lineno;
    eZero->kind = intK;
    eZero->val.intE = 0;
    eZero->type = "INT";

    return makeEXPbinop(eZero,"-",eId);
}

STMT* makeSTMTwhile(EXP* guard, STMTCOMP* body)
{
    STMT* s;
    s = (STMT*)malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = whileK;
    s->val.whileS.guard = guard;
    s->val.whileS.body = body;
    return s;
}

STMT* makeSTMTassign(char* name, EXP* val)
{
    STMT* s;
    s = (STMT*)malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = assignK;
    s->val.assignS.name = name;
    s->val.assignS.val = val;
    return s;
}

STMT* makeSTMTifElse(EXP* cond, STMTCOMP* ifbody, STMTCOMP* elsebody)
{
    STMT* s;
    s = (STMT*)malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = ifElseK;
    s->val.ifElseS.cond = cond;
    s->val.ifElseS.ifbody = ifbody;
    s->val.ifElseS.elsebody = elsebody;
    return s;
}

STMT* makeSTMTreturn(EXP* returnEXP)
{
    STMT* s;
    s = (STMT*)malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = returnK;
    s->val.returnS = returnEXP;
    return s;
}

STMT* makeSTMTprint(EXP* printEXP)
{
    STMT* s;
    s = (STMT*)malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = printK;
    s->val.printS = printEXP;
    return s;
}

STMT* makeSTMTvarDecl(char* type, char* name)
{
    STMT* s;
    s = (STMT*)malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = varDeclK;
    s->val.varDeclS.type = type;
    s->val.varDeclS.name = name;
    return s;
}

STMT* makeSTMTfunDecl(FUNCTION* f)
{
    STMT* s;
    s = (STMT*)malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = funDeclK;
    s->val.funDeclS = f;
    return s;
}

STMT* makeSTMTexp(EXP* exp)
{
    STMT* s;
    s = (STMT*)malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = expK;
    s->val.expS = exp;
    if(exp->kind != funK)
    {
        printf("ERROR: Expected function at line: %d.\n",exp->lineno);
        exit(0);
    }
    return s;
}

STMTNODE* makeSTMTNODE(STMT* stmt, STMTNODE* next)
{
    STMTNODE* sn;
    sn = (STMTNODE*)malloc(sizeof(STMTNODE));
    sn->stmt = stmt;
    sn->next = next;
    return sn;
}

STMTCOMP* makeSTMTCOMP(STMTNODE* stmtnode)
{
    STMTCOMP* sc;
    sc = (STMTCOMP*)malloc(sizeof(STMTCOMP));
    sc->stmtnode = stmtnode;
    sc->symbolTable = NULL;
    return sc;
}

APARAMETER* makeAPARAMETER(EXP* exp)
{
    APARAMETER* a;
    a = (APARAMETER*)malloc(sizeof(APARAMETER));
    a->exp = exp;
    a->lineno = lineno;
    return a;
}

APARAMETERNODE* makeAPARAMETERNODE(APARAMETER* p, APARAMETERNODE* next)
{
    APARAMETERNODE* an;
    an = (APARAMETERNODE*)malloc(sizeof(APARAMETERNODE));
    an->current = p;
    an->next = next;
    return an;
}

FPARAMETER* makeFPARAMETER(char* type, char* name)
{
    FPARAMETER* p;
    p = (FPARAMETER*)malloc(sizeof(FPARAMETER));
    p->name = name;
    p->type = type;
    p->lineno = lineno;
    return p;
}

FPARAMETERNODE* makeFPARAMETERNODE(FPARAMETERNODE* next, FPARAMETER* p)
{
    FPARAMETERNODE* fn;
    fn = (FPARAMETERNODE*)malloc(sizeof(FPARAMETERNODE));
    fn->current = p;
    fn->next = next;
    return fn;
}

FUNCTION* makeFUNCTION(char* returnType, char* name, FPARAMETERNODE* args, STMTCOMP* body)
{
    FUNCTION* fun;
    fun = (FUNCTION*)malloc(sizeof(FUNCTION));
    fun->returnType = returnType;
    fun->lineno = body->stmtnode->stmt->lineno - 1;
    fun->name = name;
    fun->args = args;
    fun->body = body;

    //Check if all branches of computation ends with a return stmt
    if(allBranchesReturn(fun->body->stmtnode) == 0)
    {
        printf("ERROR: not all branches of function \"%s\" have a return statement on line: %d",fun->name,fun->lineno);
        exit(0);
    }
    return fun;
}

int allBranchesReturn(STMTNODE* sn)
{
    int alwaysReturn = 0;
    while(sn != NULL && alwaysReturn == 0)
    {
        STMT* this = sn->stmt;
        if(this->kind == returnK)
            alwaysReturn = 1;
        else if(this->kind == ifElseK && this->val.ifElseS.elsebody != NULL)
            alwaysReturn = allBranchesReturn(this->val.ifElseS.ifbody->stmtnode) & allBranchesReturn(this->val.ifElseS.elsebody->stmtnode);
        sn = sn->next;
    }
    return alwaysReturn;
}

PROGRAM* makePROGRAM(STMTNODE* sn)
{
    PROGRAM* prog = (PROGRAM*)malloc(sizeof(PROGRAM));
    prog->sc = makeSTMTCOMP(sn);
    prog->globalScope = makeSYMBOLTABLE(NULL);
    return prog;
}

SYMBOL* makeSYMBOLvariable(char* name, char* type)
{
    SYMBOL* s;
    s = (SYMBOL*)malloc(sizeof(SYMBOL));
    s->name = name;
    s->kind = variable;
    s->type = type;
    return s;
}

SYMBOL* makeSYMBOLfunction(char* name, char* type, FPARAMETERNODE* fpn)
{
    SYMBOL* s;
    s = (SYMBOL*)malloc(sizeof(SYMBOL));
    s->name = name;
    s->kind = function;
    s->fpn = fpn;
    s->type = type;
    s->label = funLabelGenerator(name);
    return s;
}

SYMBOL* makeSYMBOLformalParameter(char* name, char* type)
{
    SYMBOL* s;
    s = (SYMBOL*)malloc(sizeof(SYMBOL));
    s->name = name;
    s->kind = formalParameter;
    s->type = type;
    return s;
}

SYMBOLNODE* makeSYMBOLNODE(SYMBOL* symbol, SYMBOLNODE* next)
{
    SYMBOLNODE* sn;
    sn = (SYMBOLNODE*)malloc(sizeof(SYMBOLNODE));
    sn->current = symbol;
    sn->next = next;
    return sn;
}

SYMBOLTABLE* makeSYMBOLTABLE(SYMBOLTABLE* par)
{
    SYMBOLTABLE* st;
    st = (SYMBOLTABLE*)malloc(sizeof(SYMBOLTABLE));
    st->par = par;
    st->symbols = NULL;
    st->symbolCount = 0;
    st->nextVariableLabel = 0;
    st->nextParameterLabel = 24;
    return st;
}

SYMBOL* lookupSymbolNameCurrentTable(char* name, SYMBOLTABLE* st)
{
    SYMBOLNODE* currentNode = st->symbols;
    while(currentNode)
    {
        if(strcmp(currentNode->current->name,name) == 0)
            return currentNode->current;
        currentNode = currentNode->next;
    }
    return NULL;
}

SYMBOL* lookupSymbolVarName(char* name, SYMBOLTABLE* st)
{
    if(st == NULL)
        return NULL;
    SYMBOL* s = lookupSymbolNameCurrentTable(name,st);
    if(s != NULL && (s->kind == variable || s->kind == formalParameter))
        return s;
    return lookupSymbolVarName(name, st->par);
}

SYMBOL* lookupSymbolFunName(char* name, SYMBOLTABLE* st)
{
    if(st == NULL)
        return NULL;
    SYMBOL* s = lookupSymbolNameCurrentTable(name,st);
    if(s != NULL && s->kind == function)
        return s;
    return lookupSymbolFunName(name, st->par);
}

int getSymbolDepth(SYMBOL* s, SYMBOLTABLE* st)
{
    if(st == NULL)
        return -1;

    int depth = 0;
    SYMBOLTABLE* currTable = st;
    while(currTable != NULL)
    {
        SYMBOLNODE* currNode = currTable->symbols;
        while(currNode != NULL)
        {
            if(s == currNode->current)
                return depth;
            currNode = currNode->next;
        }
        currTable = currTable->par;
        depth++;
    }
    return -1;
}

int* staticLinkCount(char* name, SYMBOLTABLE* st)
{
    int* levelAndNextLabel = (int*)calloc(2,sizeof(int));
    SYMBOL* temp = lookupSymbolNameCurrentTable(name,st);
    while(temp == NULL)
    {
        levelAndNextLabel[0]++;
        st = st->par;
        temp = lookupSymbolNameCurrentTable(name,st);
    }
    levelAndNextLabel[1] = temp->offset;
    return levelAndNextLabel;
}

void addSymbol(SYMBOL* symbol, SYMBOLTABLE* st)
{
    if(lookupSymbolNameCurrentTable(symbol->name, st))
    {
        printf("ERROR: Identifier '%s' already declared in this scope!",symbol->name);
        exit(-1);
    }
    if(symbol->kind == variable) {
        if (strcmp(symbol->type, "BOOLEAN") == 0) {
            st->nextVariableLabel -= 1;
        } else if (strcmp(symbol->type, "INT") == 0) {
            st->nextVariableLabel -= 4;
        } else if (strcmp(symbol->type, "DOUBLE") == 0) {
            st->nextVariableLabel -= 8;
        } else if (strcmp(symbol->type, "CHAR") == 0) {
            st->nextVariableLabel -= 1;
        }
        symbol->offset = st->nextVariableLabel;
    }
    else if(symbol->kind == formalParameter)
    {
        symbol->offset = st->nextParameterLabel;
        if (strcmp(symbol->type, "BOOLEAN") == 0) {
            st->nextParameterLabel += 1;
        } else if (strcmp(symbol->type, "INT") == 0) {
            st->nextParameterLabel += 4;
        } else if (strcmp(symbol->type, "DOUBLE") == 0) {
            st->nextParameterLabel += 8;
        } else if (strcmp(symbol->type, "CHAR") == 0) {
            st->nextParameterLabel += 1;
        }
    }
    SYMBOLNODE* sn = makeSYMBOLNODE(symbol, st->symbols);
    st->symbols = sn;
    st->symbolCount++;
}

int funCounter = 0;
char* funLabelGenerator(char* funName)
{
    char* res;
    char intString[20];
    sprintf(intString, "%d", funCounter++);
    res = concatStr("fun", intString);
    res = concatStrFree(res, "_");
    res = concatStrFree(res, funName);
    return res;
}

//Util function, it does NOT free the input strings
char* concatStr(const char* str1, const char* str2)
{
    //Get sizes of strings and new memory to be allocated
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t size = len1+len2+1;

    //Allocate enough memory to hold both strings
    char* res = (char*)malloc(size);
    memcpy(res,str1,len1);
    memcpy(res+len1,str2,len2);
    res[size-1] = '\0';
    return res;
}

//Frees the first string after making the concatenation
char* concatStrFree(char* str1, const char* str2)
{
    char* res = concatStr(str1,str2);
    free(str1);
    return res;
}