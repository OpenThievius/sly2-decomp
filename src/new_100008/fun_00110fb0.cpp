// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"
extern "C" char D_002DC210[]; /* the vtable this class's constructor stores */
void *func_00110FB0(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x140);
    pobject->pvtbl = D_002DC210;
    pobject->field_0x0 = 0;
    pobject->psidebag = 0;
    return pobject;
}
