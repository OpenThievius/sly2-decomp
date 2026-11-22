/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "mpeg.h"
extern "C" {
void func_0024AC10(MPEGDEC *);
s32 func_0024B590(MPEGHANDLE *handle) {
    MPEGDEC *decoder;
    decoder = handle->state;
    decoder->field_0x878 = 0;
    decoder->done = 0;
    decoder->field_0x4 = 0;
    decoder->field_0x8 = 0;
    handle->field_0x8 = 0;
    decoder->field_0xC0 = 0;
    decoder->field_0x98 = -1;
    func_0024AC10(decoder);
    decoder->field_0x128 = 0;
    decoder->field_0x858 = 0;
    *(s32 *)0x10002010 = (*(s32 *)0x10002010 & 0xFF7FFFFF) | 0x800000;
    return 1;
}
}
