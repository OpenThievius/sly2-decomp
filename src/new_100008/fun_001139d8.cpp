// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

extern "C" char D_002CC1C0[];

void *func_001139D8(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x40);
    pobject->pvtbl = D_002CC1C0;
    pobject->field_0x0 = 0;
    pobject->psidebag = 0;
    return pobject;
}
