// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

extern "C" char D_002D4AF8[];

void *func_00113468(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x40);
    pobject->pvtbl = D_002D4AF8;
    pobject->field_0x0 = 0;
    pobject->psidebag = 0;
    return pobject;
}
