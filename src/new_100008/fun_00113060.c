// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

void *memset(void *, int, unsigned int);
extern char D_002D04A0[];

void *func_00113060(void)
{
    NEWCLEARED30 *pobject = (NEWCLEARED30 *)__builtin_new(0xB0);
    pobject->basic.pvtbl = D_002D04A0;
    pobject->basic.field_0x0 = 0;
    pobject->basic.psidebag = 0;
    memset(pobject->cleared_0x30, 0, 0x70);
    return pobject;
}
