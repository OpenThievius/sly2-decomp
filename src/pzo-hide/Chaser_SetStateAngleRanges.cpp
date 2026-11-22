// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"

extern "C" void Chaser_SetStateAngleRanges(CHASER *chaser, u32 state, BYTES8 *angleMin, BYTES8 *angleMax)
{
    if (state < 5U) {
        CHASERRANGE *range = &chaser->arange[state];
        range->fAngle = 1;
        range->angleMin = *angleMin;
        range->angleMax = *angleMax;
    }
}
