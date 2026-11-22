// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
extern "C" int FSwBinocActive(void *);
extern "C" char B_003DD490;
int func_00209098(STEPGUARD *pguard)
{
    if (pguard->field_0xFC8 != 0) return 1;
    return FSwBinocActive(&B_003DD490);
}
