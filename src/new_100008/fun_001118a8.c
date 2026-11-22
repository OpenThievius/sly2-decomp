// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"
void *ConstructGuard(void *pguard); /* the guard's inlined constructor chain (src/sdk/ConstructGuard.cpp) */
extern char D_002D7188[]; /* the vtable this guard class stores last */
void *func_001118A8(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x1020);
    ConstructGuard(pobject);
    pobject->pvtbl = D_002D7188;
    return pobject;
}
