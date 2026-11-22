// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"
extern "C" char D_002D9040[]; /* the vtable this class's constructor stores */
void *func_00110C98(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x190);
    pobject->pvtbl = D_002D9040;
    pobject->field_0x0 = 0;
    pobject->psidebag = 0;
    return pobject;
}
