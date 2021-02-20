#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

extern int lineno;

EXP* makeEXPid(char* id)
{
    EXP* e;
    e = (EXP* )malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = idK;
    e->val.idE = id;
    return e;
}

EXP* makeEXPvar(VARIABLE* var)
{
    EXP* e;
    e = (EXP* )malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = varK;
    e->val.varE = var;
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

EXP* makeEXPchar(char charval)
{
    EXP* e;
    e = (EXP*)malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = charK;
    e->val.charE = charval;
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

STMT* makeSTMTwhile(EXP* guard, STMTNODE* body)
{
    STMT* s;
    s = (STMT*)malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = whileK;
    s->val.whileS.guard = guard;
    s->val.whileS.body = body;
    return s;
}

STMT* makeSTMTassign(EXP* id, EXP* val)
{
    STMT* s;
    s = (STMT*)malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = assignK;
    s->val.assignS.id = id;
    s->val.assignS.val = val;
    return s;
}

STMT* makeSTMTifElse(EXP* cond, STMTNODE* ifbody, STMTNODE* elsebody)
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

STMTNODE* makeSTMTNODE(STMT* stmt, STMTNODE* next)
{
    STMTNODE* sn;
    sn = (STMTNODE*)malloc(sizeof(STMTNODE));
    sn->stmt = stmt;
    sn->next = next;
    return sn;
}

VARIABLE* makeVARIABLE(char* type, char* id)
{
    VARIABLE* v;
    v = (VARIABLE*)malloc(sizeof(VARIABLE));
    v->lineno = lineno;
    v->type = type;
    v->id = id;
    return v;
}

