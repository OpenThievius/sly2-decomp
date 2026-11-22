/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "mpeg.h"
/* The decoder's three component slots (0x1C8, stride 0x10): two pointers each, to objects whose word at 0x28 is cleared here. */
struct MPEGSLOTTARGET {
    u8 unknown_0x0[0x28];
    s32 field_0x28;
};
struct MPEGSLOT {
    MPEGSLOTTARGET *first;
    MPEGSLOTTARGET *second;
    u8 unknown_0x8[0x8];
};
struct MPEGDECSLOTS {
    u8 unknown_0x0[0x1C8];
    MPEGSLOT slots[3];
};
extern "C" {
s32 func_0024B7A8(MPEGHANDLE *handle) {
    MPEGDECSLOTS *decoder = (MPEGDECSLOTS *)handle->state;
    if (decoder->slots[0].first != 0) {
        decoder->slots[0].first->field_0x28 = 0;
    }
    if (decoder->slots[1].first != 0) {
        decoder->slots[1].first->field_0x28 = 0;
    }
    if (decoder->slots[2].first != 0) {
        decoder->slots[2].first->field_0x28 = 0;
    }
    if (decoder->slots[0].second != 0) {
        decoder->slots[0].second->field_0x28 = 0;
    }
    if (decoder->slots[1].second != 0) {
        decoder->slots[1].second->field_0x28 = 0;
    }
    if (decoder->slots[2].second != 0) {
        decoder->slots[2].second->field_0x28 = 0;
    }
    return 1;
}
}
