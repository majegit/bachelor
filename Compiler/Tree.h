#ifndef __tree_h
#define __tree_h

typedef struct EXP {
    int lineno;
    enum {idK,intK,doubleK,charK,boolK,binopK,funK} kind;
    union {
        char* idE;
        int intE, boolE;
        double doubleE;
        char charE;
        struct {struct EXP* left; struct EXP* right; char* operator;} binopE;
        struct {char* id; struct APARAMETERNODE* aparameternode;} funE;
    } val;
} EXP;

EXP* makeEXPid(char* id);
EXP* makeEXPint(int intval);
EXP* makeEXPbool(int boolval);
EXP* makeEXPdouble(double doubleval);
EXP* makeEXPchar(char charval);
EXP* makeEXPbinop(EXP* left, char* operator, EXP* right);
EXP* makeEXPfun(char* id, struct APARAMETERNODE* aparameternode);

typedef struct STMT {
    int lineno;
    enum {whileK,assignK,ifElseK,returnK,printK,declK} kind;
    union {
        struct {struct EXP* guard; struct STMTNODE* body;} whileS;
        struct {struct EXP* id; struct EXP* val;} assignS;
        struct {struct EXP* cond; struct STMTNODE* ifbody; struct STMTNODE* elsebody;} ifElseS;
        struct EXP* returnS;
        struct EXP* printS;
        struct {char* type; char* name; void* value;} declS;
    } val;
} STMT;

STMT* makeSTMTwhile(EXP* guard, struct STMTNODE* body);
STMT* makeSTMTassign(EXP* id, EXP* val);
STMT* makeSTMTifElse(EXP* cond, struct STMTNODE* ifbody, struct STMTNODE* elsebody);
STMT* makeSTMTreturn(EXP* returnEXP);
STMT* makeSTMTprint(EXP* printEXP);
STMT* makeSTMTdecl(char* type, char* name, void* value);

typedef struct STMTNODE {
    STMT* stmt;
    struct STMTNODE* next;
} STMTNODE;

STMTNODE* makeSTMTNODE(STMT* stmt, STMTNODE* stmtnode);

typedef struct APARAMETER {
    int lineno;
    enum {idT,intT,doubleT,charT,boolT} type;
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

#endif