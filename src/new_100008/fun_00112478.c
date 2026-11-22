// SPDX-License-Identifier: GPL-3.0-or-later
#include "factory.h"

extern char D_002D5450[];
extern char D_002D9978[]; /* SO's vtable (class 48): the first constructor of the chain stores it */

void *func_00112478(void)
{
    NEWSO *pobject = (NEWSO *)__builtin_new(0x170);
    pobject->basic.pvtbl = D_002D9978;
    pobject->basic.field_0x0 = 0;
    pobject->basic.psidebag = 0;
    __7GLOBSET(&pobject->globset);
    pobject->basic.pvtbl = D_002D5450;
    return pobject;
}
