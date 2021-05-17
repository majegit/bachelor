#ifndef __Tree_h
#define __Tree_h

typedef struct EXP {
    int lineno;
    enum {idK,intK,doubleK,boolK,charK,binopK,funK,coerceK} kind;
    union {
        char* idE;
        char charE;
        int intE, boolE;
        double doubleE;
        struct {struct EXP* left; struct EXP* right; char* operator;} binopE;
        struct {char* id; struct APARAMETERNODE* aparameternode;} funE;
        struct EXP* coerceE;
    } val;
    char* type;
} EXP;

EXP* makeEXPid(char* id);
EXP* makeEXPchar(char charval);
EXP* makeEXPint(int intval);
EXP* makeEXPbool(int boolval);
EXP* makeEXPdouble(double doubleval);
EXP* makeEXPbinop(EXP* left, char* operator, EXP* right);
EXP* makeEXPfun(char* id, struct APARAMETERNODE* aparameternode);
EXP* makeEXPcoerce(char* targetType, EXP* e);
EXP* makeEXPUnaryMinusId(char* id);

typedef struct STMT {
    int lineno;
    enum {whileK,assignK,ifElseK,returnK,printK,varDeclK,funDeclK,expK} kind;
    union {
        struct {struct EXP* guard; struct STMTCOMP* body;} whileS;
        struct {char* name; struct EXP* val;} assignS;
        struct {struct EXP* cond; struct STMTCOMP* ifbody; struct STMTCOMP* elsebody;} ifElseS;
        struct {char* type; char* name;} varDeclS;
        struct FUNCTION* funDeclS;
        struct EXP* returnS;
        struct EXP* printS;
        struct EXP* expS;
    } val;
} STMT;

STMT* makeSTMTwhile(EXP* guard, struct STMTCOMP* body);
STMT* makeSTMTassign(char* name, EXP* val);
STMT* makeSTMTifElse(EXP* cond, struct STMTCOMP* ifbody, struct STMTCOMP* elsebody);
STMT* makeSTMTreturn(EXP* returnEXP);
STMT* makeSTMTprint(EXP* printEXP);
STMT* makeSTMTvarDecl(char* type, char* name);
STMT* makeSTMTfunDecl(struct FUNCTION* f);
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

FPARAMETERNODE* makeFPARAMETERNODE(FPARAMETERNODE* next, FPARAMETER* p);

typedef struct FUNCTION {
    int lineno;
    char* returnType;
    char* name;
    FPARAMETERNODE* args;
    STMTCOMP* body;
} FUNCTION;

FUNCTION* makeFUNCTION(char* returnType, char* name, FPARAMETERNODE* args, STMTCOMP* body);

typedef struct PROGRAM {
    STMTCOMP* sc;
    struct SYMBOLTABLE* globalScope;
} PROGRAM;

PROGRAM* makePROGRAM(STMTNODE* fn);


//SYMBOL COLLECTION PHASE

typedef struct SYMBOL {
    enum {variable,formalParameter,function} kind;
    char* name;
    char* type;
    FPARAMETERNODE* fpn; //Only functions use this
    int offset; //Only variables and formalParameters use this
    char* label; //Used by functions and
} SYMBOL;

SYMBOL* makeSYMBOLvariable(char* name, char* type);
SYMBOL* makeSYMBOLfunction(char* name, char* type, FPARAMETERNODE* fpn);
SYMBOL* makeSYMBOLformalParameter(char* name, char* type);

typedef struct SYMBOLNODE {
    SYMBOL* current;
    struct SYMBOLNODE* next;
} SYMBOLNODE;

SYMBOLNODE* makeSYMBOLNODE(SYMBOL* symbol, SYMBOLNODE* next);

typedef struct SYMBOLTABLE {
    struct SYMBOLTABLE* par;
    SYMBOLNODE* symbols;
    int symbolCount;
    int nextVariableLabel;   //Used to determine where on the stack the local variables of a scope is
    int nextParameterLabel;  //used to determine where on the stack the formal (actual) parameter is during a function call
} SYMBOLTABLE;

SYMBOLTABLE* makeSYMBOLTABLE(SYMBOLTABLE* par);

SYMBOL* lookupSymbolCurrentTable(char* name, SYMBOLTABLE* st); //Checks only the current table
SYMBOL* lookupSymbolVar(char* name, SYMBOLTABLE* st); //Checks current table and all parent tables
SYMBOL* lookupSymbolFun(char* name, SYMBOLTABLE* st);
int* staticLinkCount(char* name, SYMBOLTABLE* st);

void addSymbol(SYMBOL* symbol, SYMBOLTABLE* st);
char* funLabelGenerator(char* funName);

//Util functions
char* concatStr(const char* str1, const char* str2);
char* concatStrFree(char* str1, const char* str2);
char* concatStrFreeFree(char* str1, char* str2);
char* deepCopy(const char* str);

//Print functions
void printSYMBOLTABLE(SYMBOLTABLE* st);



#endif