// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"
void *ConstructGuard(void *pguard); /* the guard's inlined constructor chain (src/sdk/ConstructGuard.cpp) */
extern char D_002D4820[]; /* the vtable this guard class stores last */
void *func_00111868(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x10A0);
    ConstructGuard(pobject);
    pobject->pvtbl = D_002D4820;
    return pobject;
}
