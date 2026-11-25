// SPDX-License-Identifier: GPL-3.0-or-later
#include "crv.h"
extern "C" void InitXfm(LO *);
extern "C" void InitCrv(CRV *crv)
{
    InitXfm(crv);
    crv->field_0x148 = -1;
    crv->icvHint = 1;
}
