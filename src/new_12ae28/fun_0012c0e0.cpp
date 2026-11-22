// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "acr.h"

extern "C" {

s32 func_0012C0E0(ACRAXIS *pacr, f32 time) {
    f32 *elements;
    s32 count;
    s32 index;

    index = 1;
    count = pacr->ckey - 1;
    if (index < count) {
        elements = pacr->atime;
        while (index < count) {
            if (time < elements[index]) {
                break;
            }
            index += 1;
        }
    }
    return index;
}

}
