// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"
void *ConstructGuard(void *pguard); /* the guard's inlined constructor chain (src/sdk/ConstructGuard.cpp) */
extern char D_002C9DC0[]; /* the vtable this guard class stores last */
void *func_001117E8(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x1010);
    ConstructGuard(pobject);
    pobject->pvtbl = D_002C9DC0;
    return pobject;
}
