// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

void func_002562A8(void *);
extern char D_002CFC20[];

void *func_00113840(void)
{
    NEWSUB30 *pobject = (NEWSUB30 *)__builtin_new(0x50);
    pobject->basic.pvtbl = D_002CFC20;
    pobject->basic.field_0x0 = 0;
    pobject->basic.psidebag = 0;
    func_002562A8(pobject->sub_0x30);
    return pobject;
}
