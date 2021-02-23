#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"

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
STMT* makeSTMTdecl(char* type, char* name, void* value)
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

STMTNODE* makeSTMTNODE(STMT* stmt, STMTNODE* next)
{
    STMTNODE* sn;
    sn = (STMTNODE*)malloc(sizeof(STMTNODE));
    sn->stmt = stmt;
    sn->next = next;
    return sn;
}

APARAMETER* makeAPARAMETERid(char* id)
{
    APARAMETER* p;
    p = (APARAMETER*)malloc(sizeof(APARAMETER));
    p->type = idT;
    p->val.idP = id;
    return p;
}

APARAMETER* makeAPARAMETERint(int intval)
{
    APARAMETER* p;
    p = (APARAMETER*)malloc(sizeof(APARAMETER));
    p->type = intT;
    p->val.intP = intval;
    return p;
}

APARAMETER* makeAPARAMETERdouble(double doubleval)
{
    APARAMETER* p;
    p = (APARAMETER*)malloc(sizeof(APARAMETER));
    p->type = doubleT;
    p->val.doubleP = doubleval;
    return p;
}

APARAMETER* makeAPARAMETERbool(int boolval)
{
    APARAMETER* p;
    p = (APARAMETER*)malloc(sizeof(APARAMETER));
    p->type = boolT;
    p->val.boolP = boolval;
    return p;
}

APARAMETER* makeAPARAMETERchar(char charval)
{
    APARAMETER* p;
    p = (APARAMETER*)malloc(sizeof(APARAMETER));
    p->type = charT;
    p->val.charP = charval;
    return p;
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

FUNCTION* makeFUNCTION(char* returnType, char* name, FPARAMETERNODE* args, STMTNODE* body)
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

PROGRAM* makePROGRAM(STMTNODE* body, FUNCTIONNODE* fn)
{
    PROGRAM* prog;
    prog = (PROGRAM*)malloc(sizeof(PROGRAM));
    prog->body = body;
    prog->fn = fn;
    return prog;
}


