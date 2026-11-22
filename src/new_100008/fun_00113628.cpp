// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

extern "C" char D_002CCE90[];

void *func_00113628(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x50);
    pobject->pvtbl = D_002CCE90;
    pobject->field_0x0 = 0;
    pobject->psidebag = 0;
    return pobject;
}
