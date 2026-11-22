// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"
extern char D_002D9978[]; /* SO's vtable (class 48): the first constructor of the chain stores it */
extern char D_002CB230[]; /* the vtable this class stores last */
void *func_00111728(void)
{
    NEWSO *pobject = (NEWSO *)__builtin_new(0x1880);
    pobject->basic.pvtbl = D_002D9978;
    pobject->basic.field_0x0 = 0;
    pobject->basic.psidebag = 0;
    __7GLOBSET(&pobject->globset);
    pobject->field_0x174 = 0;
    pobject->basic.pvtbl = D_002CB230;
    return pobject;
}
