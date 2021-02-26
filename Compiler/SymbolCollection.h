
typedef struct SYMBOL {
    char* name;
    char* type;
    char* kind;

} SYMBOL;

typedef struct SYMBOLTABLE {

    SYMBOLTABLE* par;
    SYMBOL* symbols[]

} SYMBOLTABLE;

traverse(struct
