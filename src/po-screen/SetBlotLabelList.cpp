// SPDX-License-Identifier: GPL-3.0-or-later
#include "blot.h"

extern "C" {
void SetBlotLabelList(BLOT *blot, s32 count, s32 *labels) {
    s32 index = 0;
    if (index < count) {
        s32 *dest = blot->alabel;
        do {
            *dest = *labels;
            index++; labels++; dest++;
        } while (index < count && (unsigned)index < 10);
    }
    blot->Select(-1);
}
}
