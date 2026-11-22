/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
void memclr(u8 *destination, s32 size) {
    s32 remaining;
    u8 *cursor;
    cursor = destination;
    remaining = size - 1;
    if (size != 0) {
        do {
            *cursor = 0;
            remaining -= 1;
            cursor += 1;
        } while (remaining != -1);
    }
}
}
