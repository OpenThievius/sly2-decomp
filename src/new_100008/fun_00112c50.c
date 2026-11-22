// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

void *Blot_Construct(void *);
extern char D_002DAA50[];

void *func_00112C50(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x110);
    Blot_Construct(pobject);
    pobject->pvtbl = D_002DAA50;
    return pobject;
}
