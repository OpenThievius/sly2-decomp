// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"
extern "C" char D_002D2B18[]; /* the vtable this class's constructor stores */
void *func_00110C60(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x120);
    pobject->pvtbl = D_002D2B18;
    pobject->field_0x0 = 0;
    pobject->psidebag = 0;
    return pobject;
}
