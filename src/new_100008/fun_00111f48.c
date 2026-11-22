// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"
extern char D_002D9978[]; /* SO's vtable (class 48): the first constructor of the chain stores it */
extern char D_002D3AA0[]; /* the vtable this class stores last */
void *func_00111F48(void)
{
    NEWSO *pobject = (NEWSO *)__builtin_new(0x290);
    pobject->basic.pvtbl = D_002D9978;
    pobject->basic.field_0x0 = 0;
    pobject->basic.psidebag = 0;
    __7GLOBSET(&pobject->globset);
    pobject->basic.pvtbl = D_002D3AA0;
    return pobject;
}
