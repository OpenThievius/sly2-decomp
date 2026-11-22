// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

extern "C" char D_002CFA10[];

void *func_001133C0(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0xE0);
    pobject->pvtbl = D_002CFA10;
    pobject->field_0x0 = 0;
    pobject->psidebag = 0;
    return pobject;
}
