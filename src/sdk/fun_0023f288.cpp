/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
/* reads a signed LEB128 number at bytes into *value and returns the address after it */
u8 *func_0023F288(u8 *bytes, s32 *value) {
    s32 result;
    u32 shift;
    u8 *cursor;
    u8 byte;
    cursor = bytes;
    shift = 0;
    result = 0;
    do {
        byte = *cursor;
        cursor += 1;
        result |= (byte & 0x7F) << shift;
        shift += 7;
    } while (byte & 0x80);
    if ((shift < 0x20U) && (byte & 0x40)) {
        result |= -1 << shift;
    }
    *value = result;
    return cursor;
}
}
