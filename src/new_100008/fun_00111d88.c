// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

extern char D_002D7CA8[];
extern char D_002D9978[]; /* SO's vtable (class 48): the first constructor of the chain stores it */

void *func_00111D88(void)
{
    NEWSO598 *pobject = (NEWSO598 *)__builtin_new(0x5D0);
    pobject->so.basic.pvtbl = D_002D9978;
    pobject->so.basic.field_0x0 = 0;
    pobject->so.basic.psidebag = 0;
    __7GLOBSET(&pobject->so.globset);
    pobject->so.field_0x174 = 0;
    pobject->so.basic.pvtbl = D_002D7CA8;
    pobject->field_0x598 = 0;
    return pobject;
}
