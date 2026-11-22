// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

void *Blot_Construct(void *);
extern char D_002CEEB8[];

void *func_00112CF8(void)
{
    NEWBASIC *pobject = (NEWBASIC *)__builtin_new(0x140);
    Blot_Construct(pobject);
    pobject->pvtbl = D_002CEEB8;
    return pobject;
}
