// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

extern "C" char D_002CFDA0[];

void *func_00113888(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x60);
    pobject->pvtbl = D_002CFDA0;
    pobject->field_0x0 = 0;
    pobject->psidebag = 0;
    return pobject;
}
