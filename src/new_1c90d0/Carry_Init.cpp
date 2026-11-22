// SPDX-License-Identifier: GPL-3.0-or-later
#include "carrypart.h"

void Carry_Init(CARRYPART *pcarry)
{
    pcarry->state = -1;
    pcarry->field_0x90 = -1;
}
