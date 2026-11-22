// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"
extern "C" char D_002D3540[]; /* the vtable this class's constructor stores */
void *func_00110AD8(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x50);
    pobject->pvtbl = D_002D3540;
    pobject->field_0x0 = 0;
    pobject->psidebag = 0;
    return pobject;
}
