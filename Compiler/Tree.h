#ifndef __Tree_h
#define __Tree_h

typedef struct EXP {
    int lineno;
    enum {idK,intK,doubleK,boolK,charK,binopK,funK} kind;
    union {
        char* idE;
        char charE;
        int intE, boolE;
        double doubleE;
        struct {struct EXP* left; struct EXP* right; char* operator;} binopE;
        struct {char* id; struct APARAMETERNODE* aparameternode;} funE;
    } val;
    char* type;
    char* coerceTo;
} EXP;

EXP* makeEXPid(char* id);
EXP* makeEXPchar(char charval);
EXP* makeEXPint(int intval);
EXP* makeEXPbool(int boolval);
EXP* makeEXPdouble(double doubleval);
EXP* makeEXPbinop(EXP* left, char* operator, EXP* right);
EXP* makeEXPfun(char* id, struct APARAMETERNODE* aparameternode);

typedef struct STMT {
    int lineno;
    enum {whileK,assignK,ifElseK,returnK,printK,declK,expK} kind;
    union {
        struct {struct EXP* guard; struct STMTCOMP* body;} whileS;
        struct {char* name; struct EXP* val;} assignS;
        struct {struct EXP* cond; struct STMTCOMP* ifbody; struct STMTCOMP* elsebody;} ifElseS;
        struct EXP* returnS;
        struct EXP* printS;
        struct {char* type; char* name; EXP* value;} declS;
        struct EXP* expS;
    } val;
} STMT;

STMT* makeSTMTwhile(EXP* guard, struct STMTCOMP* body);
STMT* makeSTMTassign(char* name, EXP* val);
STMT* makeSTMTifElse(EXP* cond, struct STMTCOMP* ifbody, struct STMTCOMP* elsebody);
STMT* makeSTMTreturn(EXP* returnEXP);
STMT* makeSTMTprint(EXP* printEXP);
STMT* makeSTMTdecl(char* type, char* name, EXP* value);
STMT* makeSTMTexp(EXP* exp);

typedef struct STMTNODE {
    struct STMT* stmt;
    struct STMTNODE* next;
} STMTNODE;

STMTNODE* makeSTMTNODE(STMT* stmt, STMTNODE* stmtnode);

typedef struct STMTCOMP
{
    struct STMTNODE* stmtnode;
    struct SYMBOLTABLE* symbolTable;
} STMTCOMP;

STMTCOMP* makeSTMTCOMP(STMTNODE* stmtnode);

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
    STMTCOMP* body;
} FUNCTION;

FUNCTION* makeFUNCTION(char* returnType, char* name, FPARAMETERNODE* args, STMTCOMP* body);

typedef struct FUNCTIONNODE {
    FUNCTION* current;
    struct FUNCTIONNODE* next;
} FUNCTIONNODE;

FUNCTIONNODE* makeFUNCTIONNODE(FUNCTION* current, FUNCTIONNODE* next);

typedef struct PROGRAM {
    STMTCOMP* body;
    FUNCTIONNODE* fn;
    struct SYMBOLTABLE* symbolTable;
} PROGRAM;

PROGRAM* makePROGRAM(STMTCOMP* body, FUNCTIONNODE* fn);


//SYMBOL COLLECTION PHASE

typedef struct SYMBOL {
    char* name;
    enum {variable,function} kind;
    FPARAMETERNODE* fpn;
    char* type;
} SYMBOL;

SYMBOL* makeSYMBOLvariable(char* name, char* type);
SYMBOL* makeSYMBOLfunction(char* name, char* type, FPARAMETERNODE* fpn);

typedef struct SYMBOLNODE {
    SYMBOL* current;
    struct SYMBOLNODE* next;
} SYMBOLNODE;

SYMBOLNODE* makeSYMBOLNODE(SYMBOL* symbol, SYMBOLNODE* next);

typedef struct SYMBOLTABLE {
    struct SYMBOLTABLE* par;
    SYMBOLNODE* symbols;
} SYMBOLTABLE;

SYMBOLTABLE* makeSYMBOLTABLE(SYMBOLTABLE* par);

SYMBOL* lookupSymbolCurrentTable(char* name, SYMBOLTABLE* st); //Checks only the current table
SYMBOL* lookupSymbolVar(char* name, SYMBOLTABLE* st); //Checks current table and all parent tables
SYMBOL* lookupSymbolFun(char* name, SYMBOLTABLE* st);

void addSymbol(SYMBOL* symbol, SYMBOLTABLE* st);




#endif