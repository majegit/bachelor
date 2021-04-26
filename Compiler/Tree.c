#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Tree.h"
#include "Error.h"

extern int lineno;

EXP* makeEXPid(char* id)
{
    EXP* e;
    e = (EXP*)malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = idK;
    e->val.idE = id;
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
    e = (EXP* )malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = funK;
    e->val.funE.id = id;
    e->val.funE.aparameternode = aparameternode;
    return e;
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
STMT* makeSTMTvarDecl(char* type, char* name, EXP* value)
{
    STMT* s;
    s = (STMT*)malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = varDeclK;
    s->val.varDeclS.type = type;
    s->val.varDeclS.name = name;
    s->val.varDeclS.value = value;
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
    fun->name = name;
    fun->args = args;
    fun->body = body;
    return fun;
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
    printf("funLabel: %s\n",s->label);
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
    st->nextParameterLabel = 8;
    return st;
}
SYMBOL* lookupSymbolCurrentTable(char* name, SYMBOLTABLE* st)
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

SYMBOL* lookupSymbolVar(char* name, SYMBOLTABLE* st)
{
    if(st == NULL)
        return NULL;
    if(lookupSymbolCurrentTable(name,st))
        return lookupSymbolCurrentTable(name,st);
    lookupSymbolVar(name, st->par);
    return NULL;
}

SYMBOL* lookupSymbolFun(char* name, SYMBOLTABLE* st)
{
    if(st == NULL)
        return NULL;
    if(lookupSymbolCurrentTable(name,st))
    {
        SYMBOL* symbol = lookupSymbolCurrentTable(name,st);
        if(symbol != NULL && symbol->kind == function)
            return symbol;
    }
    lookupSymbolFun(name, st->par);
}

int* staticLinkCount(char* name, SYMBOLTABLE* st)
{
    int* levelAndNextLabel = (int*)calloc(2,sizeof(int));
    SYMBOL* temp = lookupSymbolCurrentTable(name,st);
    while(temp == NULL)
    {
        levelAndNextLabel[0]++;
        st = st->par;
        temp = lookupSymbolCurrentTable(name,st);
    }
    levelAndNextLabel[1] = temp->offset;
    return levelAndNextLabel;
}

void addSymbol(SYMBOL* symbol, SYMBOLTABLE* st)
{
    if(lookupSymbolCurrentTable(symbol->name, st))
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
        st->nextParameterLabel -= 8;
        symbol->offset = st->nextParameterLabel;
    }
    SYMBOLNODE* sn = makeSYMBOLNODE(symbol, st->symbols);
    st->symbols = sn;
    st->symbolCount++;
}

int funCounter = 0;
char* funLabelGenerator(char* funName)
{
    if(strcmp(funName, "main") == 0)
        return "main";
    char* res;
    char intString[20];
    sprintf(intString, "%d", funCounter++);
    res = concatStr("fun", intString);
    res = concatStrFree(res, "_");
    res = concatStrFree(res, funName);
    return res;
}

int doubleCounter = 0;
char* doubleLabelGenerator()
{
    char intAsString[20];
    sprintf(intAsString,"%d",doubleCounter++);
    return concatStr("doubleconst_",intAsString);
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

char* concatStrFreeFree(char* str1, char* str2)
{
    char* res = concatStr(str1,str2);
    free(str1);
    free(str2);
    return res;
}

//Copies a string into a new memory location and returns a pointer to it
char* deepCopy(const char* str)
{
    char* res = (char*)malloc(strlen(str)+1);
    memcpy(res,str,strlen(str)+1);
    return res;
}