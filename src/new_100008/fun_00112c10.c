// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

void *Blot_Construct(void *);
extern char D_002DABF0[];

void *func_00112C10(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x120);
    Blot_Construct(pobject);
    pobject->pvtbl = D_002DABF0;
    return pobject;
}
