// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
/* copies size bytes as words; the byte count is rounded down to whole words */
extern "C" s32 func_00239920(s32 *destination, s32 *source, u32 size) {
    u32 count = size >> 2;
    u32 index = 0;
    if (count != 0) {
        do {
            s32 word = *source;
            index += 1;
            source += 1;
            *destination = word;
            destination += 1;
        } while (index < count);
    }
    return 0;
}
