// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

extern "C" char D_002CDD40[];

void *func_001135F0(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x60);
    pobject->pvtbl = D_002CDD40;
    pobject->field_0x0 = 0;
    pobject->psidebag = 0;
    return pobject;
}
