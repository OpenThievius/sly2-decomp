/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
struct SAPEP { float g; unsigned short fMin; unsigned short islot; };
int IepSweepPathzoneCursor(float g, SAPEP *aep, int iep, unsigned *agrf, unsigned fMin)
{
    if (g <= aep[iep].g) {
        for (;;) {
            SAPEP *cur = &aep[iep];
            if (aep[iep].g < g)
                break;
            if (cur->fMin == fMin) {
                unsigned islot = cur->islot;
                unsigned word = islot >> 5;
                unsigned bit = islot - (word << 5);
                if (fMin == 0)
                    agrf[word] |= (1u << bit);
                else
                    agrf[word] -= (1u << bit);
            }
            iep--;
        }
    } else {
    iep++;
    for (;;) {
        SAPEP *cur = &aep[iep];
        if (g < aep[iep].g)
            break;
        if (cur->fMin == fMin) {
            unsigned islot = cur->islot;
            unsigned word = islot >> 5;
            unsigned bit = islot - (word << 5);
            if (fMin != 0)
                agrf[word] |= (1u << bit);
            else
                agrf[word] -= (1u << bit);
        }
        iep++;
    }
    iep--;
    }
    return iep;
}
