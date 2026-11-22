// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
/* copies size bytes */
extern "C" s32 func_00239898(u8 *destination, u8 *source, u32 size) {
    u32 index = 0;
    if (size != 0) {
        do {
            u8 byte = *source;
            index += 1;
            source += 1;
            *destination = byte;
            destination += 1;
        } while (index < size);
    }
    return 0;
}
