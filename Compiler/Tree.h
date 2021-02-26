#ifndef __Tree_h
#define __Tree_h

typedef struct EXP {
    int lineno;
    enum {idK,intK,doubleK,boolK,binopK,funK} kind;
    union {
        char* idE;
        int intE, boolE;
        double doubleE;
        struct {struct EXP* left; struct EXP* right; char* operator;} binopE;
        struct {char* id; struct APARAMETERNODE* aparameternode;} funE;
    } val;
} EXP;

EXP* makeEXPid(char* id);
EXP* makeEXPint(int intval);
EXP* makeEXPbool(int boolval);
EXP* makeEXPdouble(double doubleval);
EXP* makeEXPbinop(EXP* left, char* operator, EXP* right);
EXP* makeEXPfun(char* id, struct APARAMETERNODE* aparameternode);

typedef struct STMT {
    int lineno;
    enum {whileK,assignK,ifElseK,returnK,printK,declK,expK} kind;
    union {
        struct {struct EXP* guard; struct STMTNODE* body;} whileS;
        struct {char* name; struct EXP* val;} assignS;
        struct {struct EXP* cond; struct STMTNODE* ifbody; struct STMTNODE* elsebody;} ifElseS;
        struct EXP* returnS;
        struct EXP* printS;
        struct {char* type; char* name; void* value;} declS;
        struct EXP* expS;
    } val;
} STMT;

STMT* makeSTMTwhile(EXP* guard, struct STMTNODE* body);
STMT* makeSTMTassign(char* name, EXP* val);
STMT* makeSTMTifElse(EXP* cond, struct STMTNODE* ifbody, struct STMTNODE* elsebody);
STMT* makeSTMTreturn(EXP* returnEXP);
STMT* makeSTMTprint(EXP* printEXP);
STMT* makeSTMTdecl(char* type, char* name, void* value);
STMT* makeSTMTexp(EXP* exp);

typedef struct STMTNODE {
    STMT* stmt;
    struct STMTNODE* next;
} STMTNODE;

STMTNODE* makeSTMTNODE(STMT* stmt, STMTNODE* stmtnode);

typedef struct APARAMETER {
    int lineno;
    EXP* exp;
} APARAMETER;

APARAMETER* makeAPARAMETER(EXP* exp);

typedef struct APARAMETERNODE {
    APARAMETER* current;
    struct APARAMETERNODE* next;
} APARAMETERNODE;

APARAMETERNODE* makeAPARAMETERNODE(APARAMETER* p, APARAMETERNODE* next);

typedef struct FPARAMETER {
    int lineno;
    char* type;
    char* name;
} FPARAMETER;

FPARAMETER* makeFPARAMETER(char* type, char* name);

typedef struct FPARAMETERNODE {
    FPARAMETER* current;
    struct FPARAMETERNODE* next;
} FPARAMETERNODE;

FPARAMETERNODE* makeFPARAMETERNODE(FPARAMETER* p, FPARAMETERNODE* next);

typedef struct FUNCTION {
    int lineno;
    char* returnType;
    char* name;
    FPARAMETERNODE* args;
    STMTNODE* body;
} FUNCTION;

FUNCTION* makeFUNCTION(char* returnType, char* name, FPARAMETERNODE* args, STMTNODE* body);

typedef struct FUNCTIONNODE {
    FUNCTION* current;
    struct FUNCTIONNODE* next;
} FUNCTIONNODE;

FUNCTIONNODE* makeFUNCTIONNODE(FUNCTION* current, FUNCTIONNODE* next);

typedef struct PROGRAM {
    STMTNODE* body;
    FUNCTIONNODE* fn;
} PROGRAM;

PROGRAM* makePROGRAM(STMTNODE* body, FUNCTIONNODE* fn);

#endif