/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "swview.h"

void RemoveGrfusr__Fi(s32 grfusr);                  /* extern */

void DecrementSwHandsOff__FP2SW(struct SWVIEW *sw) {
    s32 chandsoff;

    chandsoff = sw->chandsOffSw - 1;
    sw->chandsOffSw = chandsoff;
    if (chandsoff == 0) {
        RemoveGrfusr__Fi(4);
    }
}
