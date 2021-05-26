#include "FunctionInline.h"
#include "Tree.h"
#include "stdlib.h"


//Right now the criteria for being inline is simply that the function contains no other funcalls.
int isInlineable(FUNCTION* f)
{
    if(!stmtcompContainsFunCall(f->body)) //No function calls within the function
        return 1;
    return 0;
}

int stmtcompContainsFunCall(STMTCOMP* sc)
{
    STMTNODE* currNode = sc->stmtnode;
    while(currNode != NULL)
    {
        STMT* stmt = currNode->stmt;
        switch(stmt->kind)
        {
            case whileK:
            {
                if(expContainsFunCall(stmt->val.whileS.guard) || stmtcompContainsFunCall(stmt->val.whileS.body))
                    return 1;
                break;
            }
            case assignK
            {
                if(expContainsFunCall(stmt->val.assignS.val))
                    return 1;
                break;
            }
            case ifElseK:
            {
                if(expContainsFunCall(stmt->val.ifElseS.cond)
                || stmtcompContainsFunCall(stmt->val.ifElseS.ifbody)
                || (stmt->val.ifElseS.elsebody != NULL && stmtcompContainsFunCall(stmt->val.ifElseS.elsebody)))
                    return 1;
                break;
            }
            case returnK:
            {
                if(expContainsFunCall(stmt->val.returnS))
                    return 1;
            }
            case printK:
            {
                if(expContainsFunCall(stmt->val.printS))
                    return 1;
                break;
            }
            case expK: //Only funcalls are allowed as free standing expressions
                return 1;
            default:
                break;
        }
        currNode = currNode->next;
    }
    return 0; //No function calls found
}

int expContainsFunCall(EXP* e)
{
    switch(e->kind)
    {
        case binopK:
        {
            if(expContainsFunCall(e->val.binopE.left) || expContainsFunCall(e->val.binopE.right))
                return 1;
            break;
        }
        case coerceK:
        {
            if(expContainsFunCall(e->val.coerceE))
                return 1;
            break;
        }
        case funK: //The expression is a function call
            return 1;
        default:
            break;
    }
    return 0; //No function calls found
}