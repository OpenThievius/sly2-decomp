/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
/* reads an unsigned LEB128 number at bytes into *value and returns the address after it */
u8 *func_0023F240(u8 *bytes, s32 *value) {
    s32 result;
    s32 shift;
    u8 *cursor;
    u8 byte;
    u8 nextByte;
    byte = *bytes;
    shift = 0;
    cursor = bytes + 1;
    result = byte & 0x7F;
    if (byte & 0x80) {
        do {
            nextByte = *cursor;
            shift += 7;
            cursor += 1;
            result |= (nextByte & 0x7F) << shift;
        } while (nextByte & 0x80);
    }
    *value = result;
    return cursor;
}
}
