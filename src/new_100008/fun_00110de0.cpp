// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"
extern "C" char D_002DB6B8[]; /* the vtable this class's constructor stores */
void *func_00110DE0(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x1c0);
    pobject->pvtbl = D_002DB6B8;
    pobject->field_0x0 = 0;
    pobject->psidebag = 0;
    return pobject;
}
