// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"
extern "C" char D_002C9C20[]; /* the vtable this class's constructor stores */
void *func_00111020(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x2d0);
    pobject->pvtbl = D_002C9C20;
    pobject->field_0x0 = 0;
    pobject->psidebag = 0;
    return pobject;
}
