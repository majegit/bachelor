#ifndef __FunctionInline_H
#define __FunctionInline_H

int isInlineable(FUNCTION* f);
int stmtcompContainsFunCall(STMTCOMP* sc);
int expContainsFunCall(EXP* e);

#endif