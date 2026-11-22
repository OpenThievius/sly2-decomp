// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

extern "C" char D_002D0420[];

void *func_001134D8(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x40);
    pobject->pvtbl = D_002D0420;
    pobject->field_0x0 = 0;
    pobject->psidebag = 0;
    return pobject;
}
