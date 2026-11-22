// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"

extern "C" void Chaser_SetStateDistanceRanges(CHASER *chaser, u32 state, BYTES8 *distanceMin, BYTES8 *distanceMax)
{
    if (state < 5U) {
        CHASERRANGE *range = &chaser->arange[state];
        range->fDistance = 1;
        range->distanceMin = *distanceMin;
        range->distanceMax = *distanceMax;
    }
}
