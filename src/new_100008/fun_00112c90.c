// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

void *Blot_Construct(void *);
extern char D_002DAD90[];

void *func_00112C90(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x220);
    Blot_Construct(pobject);
    pobject->pvtbl = D_002DAD90;
    return pobject;
}
