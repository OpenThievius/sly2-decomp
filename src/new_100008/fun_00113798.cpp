// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

extern "C" char D_002CFEA0[];

void *func_00113798(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x30);
    pobject->pvtbl = D_002CFEA0;
    pobject->field_0x0 = 0;
    pobject->psidebag = 0;
    return pobject;
}
