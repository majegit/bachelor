#ifndef __tree_h
#define __tree_h

typedef struct EXP {
    int lineno;
    enum {idK,intK,doubleK,charK,boolK,binopK,varK} kind;
    union {
        char* idE;
        struct VARIABLE* varE;
        int intE, boolE;
        double doubleE;
        char charE;
        struct {struct EXP* left; struct EXP* right; char* operator} binopE;
    } val;
} EXP;

EXP* makeEXPid(char* id);

EXP* makeEXPvar(VARIABLE* var);

EXP* makeEXPint(int intval);

EXP* makeEXPbool(int boolval);

EXP* makeEXPdouble(double doubleval);

EXP* makeEXPchar(char charval);

EXP* makeEXPbinop(EXP* left, char* operator, EXP* right);

typedef struct VARIABLE {
    int lineno;
    char* type;
    char* id;
} VARIABLE;

VARIABLE* makeVARIABLE(char* id, char* type);

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

STMT* makeSTMTassign(EXP* id, EXP* val);

STMT* makeSTMTifElse(EXP* cond, STMTNODE* ifbody, STMTNODE* elsebody);

STMT* makeSTMTreturn(EXP* returnEXP);

STMT* makeSTMTprint(EXP* printEXP);

STMTNODE* makeSTMTNODE(STMT* stmt, STMTNODE* stmtnode);

#endif