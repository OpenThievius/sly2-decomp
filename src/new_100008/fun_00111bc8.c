// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"
extern char D_002D9978[]; /* SO's vtable (class 48): the first constructor of the chain stores it */
extern char D_002D15D0[]; /* the vtable this class stores last */
void *func_00111BC8(void)
{
    NEWSO2A4 *pobject = (NEWSO2A4 *)__builtin_new(0x2B0);
    pobject->so.basic.pvtbl = D_002D9978;
    pobject->so.basic.field_0x0 = 0;
    pobject->so.basic.psidebag = 0;
    __7GLOBSET(&pobject->so.globset);
    pobject->so.field_0x174 = 0;
    pobject->so.basic.pvtbl = D_002D15D0;
    pobject->field_0x2A4 = 0;
    return pobject;
}
