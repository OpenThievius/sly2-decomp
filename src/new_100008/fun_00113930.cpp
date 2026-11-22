// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

extern "C" char D_002CC340[];

void *func_00113930(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x40);
    pobject->pvtbl = D_002CC340;
    pobject->field_0x0 = 0;
    pobject->psidebag = 0;
    return pobject;
}
