// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

extern "C" char D_002CC440[];

void *func_001138C0(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x50);
    pobject->pvtbl = D_002CC440;
    pobject->field_0x0 = 0;
    pobject->psidebag = 0;
    return pobject;
}
