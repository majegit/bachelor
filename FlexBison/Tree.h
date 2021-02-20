#ifndef __tree_h
#define __tree_h

typedef struct EXP {
    int lineno;
    enum {idK,intK,doubleK,charK,boolK,binopK,varK,funK} kind;
    union {
        char* idE;
        int intE, boolE;
        double doubleE;
        char charE;
        struct {struct EXP* left; struct EXP* right; char* operator} binopE;
        struct {char* id, char* type} varE;
        struct {char* id, struct PARAMETERNODE* parameternode} funE;
    } val;
} EXP;

EXP* makeEXPid(char* id);
EXP* makeEXPvar(char* type, char* id);
EXP* makeEXPint(int intval);
EXP* makeEXPbool(int boolval);
EXP* makeEXPdouble(double doubleval);
EXP* makeEXPchar(char charval);
EXP* makeEXPbinop(EXP* left, char* operator, EXP* right);
EXP* makeEXPfun(char* id, PARAMETERNODE* parameternode);

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

STMT* makeSTMTwhile(EXP* guard, STMTNODE* body);
STMT* makeSTMTassign(EXP* id, EXP* val);
STMT* makeSTMTifElse(EXP* cond, STMTNODE* ifbody, STMTNODE* elsebody);
STMT* makeSTMTreturn(EXP* returnEXP);
STMT* makeSTMTprint(EXP* printEXP);

typedef struct STMTNODE {
    STMT* stmt;
    STMTNODE* next;
} STMTNODE;

STMTNODE* makeSTMTNODE(STMT* stmt, STMTNODE* stmtnode);

typedef struct APARAMETER {
    int lineno;
    enum {idK,intK,doubleK,charK,boolK} kind;
    union {
        char* idP;
        int intP, boolP;
        double doubleP;
        char charP;
    } val;
} APARAMETER;

APARAMETER* makeAPARAMETERid(char* id);
APARAMETER* makeAPARAMETERint(int intval);
APARAMETER* makeAPARAMETERdouble(double doubleval);
APARAMETER* makeAPARAMETERbool(int boolval);
APARAMETER* makeAPARAMETERchar(char charval);


typedef struct APARAMETERNODE {
    APARAMETER* aparameter;
    APARAMETERNODE* next;
} APARAMETERNODE;

APARAMETERNODE* makeAPARAMETERNODE(APARAMETER* p, APARAMETERNODE* next);

typedef struct FPARAMETER {
    int lineno;
    enum {intK,doubleK,charK,boolK} kind;
    char* id;
} FPARAMETER;

FPARAMETER* makeFPARAMETER(char* type, char* id);

typedef struct FPARAMETERNODE {
    FPARAMETER* fparameter;
    FPARAMETERNODE* next;
} FPARAMETERNODE;

FPARAMETERNODE* makeFPARAMETERNODE(FPARAMETER* p, FPARAMETERNODE* next);

typedef struct FUNCTION {
    int lineno;
    char* returnType;
    char* id;
    FPARAMETERNODE* args;
    STMTNODE* body;
} FUNCTION;

FUNCTION* makeFUNCTION(char* returnType, char* id, FPARAMETERNODE* args, STMTNODE* body);

typedef struct FUNCTIONNODE {
    FUNCTION* fun;
    FUNCTIONNODE* next;
} FUNCTIONNODE;

FUNCTIONNODE* makeFUNCTIONNODE(FUNCTION* fun, FUNCTIONNODE* next);

typedef struct PROGRAM {
    STMTNODE* body;
    FUNCTIONNODE* fn;
} PROGRAM;

#endif