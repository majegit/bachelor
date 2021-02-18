#ifndef __tree_h
#define __tree_h

typedef struct EXP {
    int lineno;
    enum {idK,intK,doubleK,charK,boolK,binopK} kind;
    union {
        char* idE;
        int intE, boolE;
        double doubleE;
        char charE;
        struct {struct EXP* left; struct EXP* right; char* operator} binopE;
    } val;
} EXP;

EXP* makeEXPid(char* id);

EXP* makeEXPint(int intval);

EXP* makeEXPbool(int boolval);

EXP* makeEXPdouble(double doubleval);

EXP* makeEXPchar(char charval);

EXP* makeEXPbinop(EXP* left, char* operator, EXP* right);

typedef struct STMT {
    int lineno;
    enum {whileK,assignK,ifElseK,returnK,printK} kind;
    union {
        struct {struct EXP* guard, struct STMTNODE* body} whileS;
        struct {struct EXP* id, struct EXP* val} assignS;
        struct {struct EXP* cond, struct STMTNODE* ifbody, struct STMTNODE* elsebody} ifElseS;
        struct EXP* returnS;
        struct EXP* printS;
    } val;
} STMT;

typedef struct STMTNODE {
    STMT* stmt;
    STMTNODE* next;
} STMTNODE;

STMT* makeSTMTwhile(EXP* guard, STMTNODE* body);

STMT* makeSTMTassign(EXP* id, STMT* val);

STMT* makeSTMTifElse(EXP* cond, STMTNODE* ifbody, STMTNODE* elsebody);

STMT* makeSTMTreturn(EXP* returnEXP);

STMT* makeSTMTprint(EXP* printEXP);

STMTNODE* makeSTMTNODE(STMT* stmt, STMTNODE* stmtnode);

#endif