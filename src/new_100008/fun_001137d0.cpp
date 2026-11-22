// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

extern "C" char D_002CFD20[];

void *func_001137D0(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x50);
    pobject->pvtbl = D_002CFD20;
    pobject->field_0x0 = 0;
    pobject->psidebag = 0;
    return pobject;
}
