/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "swview.h"

void AddGrfusr__Fi(s32 grfusr);                     /* extern */

void IncrementSwHandsOff__FP2SW(struct SWVIEW *sw) {
    s32 chandsoff;

    chandsoff = sw->chandsOffSw + 1;
    sw->chandsOffSw = chandsoff;
    if (chandsoff == 1) {
        AddGrfusr__Fi(4);
    }
}
