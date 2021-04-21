#include "Tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    return e;
}

EXP* makeEXPint(int intval)
{
    EXP* e;
    e = (EXP* )malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = intK;
    e->val.intE = intval;
    return e;
}

EXP* makeEXPbool(int boolval)
{
    EXP* e;
    e = (EXP* )malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = boolK;
    e->val.boolE = boolval;
    if(boolval != 0 && boolval != 1)
        printf("Error boolean value not 1 or 0, line: %d", lineno);
    return e;
}

EXP* makeEXPdouble(double doubleval)
{
    EXP* e;
    e = (EXP* )malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = doubleK;
    e->val.doubleE = doubleval;
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
STMT* makeSTMTdecl(char* type, char* name, EXP* value)
{
    STMT* s;
    s = (STMT*)malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = declK;
    s->val.declS.type = type;
    s->val.declS.name = name;
    s->val.declS.value = value;
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

FPARAMETERNODE* makeFPARAMETERNODE(FPARAMETER* p, FPARAMETERNODE* next)
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

FUNCTIONNODE* makeFUNCTIONNODE(FUNCTION* fun, FUNCTIONNODE* next)
{
    FUNCTIONNODE* fn;
    fn = (FUNCTIONNODE*)malloc(sizeof(FUNCTIONNODE));
    fn->current = fun;
    fn->next = next;
    return fn;
}

PROGRAM* makePROGRAM(STMTCOMP* body, FUNCTIONNODE* fn)
{
    PROGRAM* prog;
    prog = (PROGRAM*)malloc(sizeof(PROGRAM));
    prog->body = body;
    prog->fn = fn;
    prog->symbolTable = NULL;
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
    st->nextLabel = 0;
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
    printf("looking up name: %s\n",name);
    if(st == NULL)
    {
        printf("st is NULL\n");
        return NULL;
    }
    if(lookupSymbolCurrentTable(name,st))
        return lookupSymbolCurrentTable(name,st);
    lookupSymbolVar(name, st->par);
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
    SYMBOL* temp;
    int* levelAndNextLabel = (int*)malloc(sizeof(int)*2);
    temp = lookupSymbolCurrentTable(name,st);
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
            st->nextLabel += 1;
        } else if (strcmp(symbol->type, "INT") == 0) {
            st->nextLabel += 4;
        } else if (strcmp(symbol->type, "DOUBLE") == 0) {
            st->nextLabel += 8;
        } else if (strcmp(symbol->type, "CHAR") == 0) {
            st->nextLabel += 1;
        }
    }
    symbol->offset = st->nextLabel;
    SYMBOLNODE* sn = makeSYMBOLNODE(symbol, st->symbols);
    st->symbols = sn;
    st->symbolCount++;
}