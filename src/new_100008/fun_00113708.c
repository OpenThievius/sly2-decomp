// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

void func_002562A8(void *);
extern char D_002CFE20[];

void *func_00113708(void)
{
    NEWSUB3 *pobject = (NEWSUB3 *)__builtin_new(0xD0);
    pobject->basic.pvtbl = D_002CFE20;
    pobject->basic.field_0x0 = 0;
    pobject->basic.psidebag = 0;
    func_002562A8(pobject->sub_0x40);
    func_002562A8(pobject->sub_0x60);
    func_002562A8(pobject->sub_0x80);
    return pobject;
}
