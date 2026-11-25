// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
typedef struct MpegState {
    u8 unknown_0x0[0xC4];
    int field0C4;
    u8 unknown_0xC8[0xEC - 0xC8];
    unsigned field0EC;
    unsigned field0F0;
    unsigned field0F4;
    unsigned field0F8;
} MpegState;
typedef struct MpegHandle {
    u8 unknown_0x0[0x40];
    MpegState *state;
} MpegHandle;
extern "C" int func_0024ACD8(MpegHandle *handle);
extern "C" int sceMpegGetPicture(MpegHandle *handle, unsigned destination, unsigned size) {
    MpegState *state = handle->state;
    state->field0C4 = 1;
    state->field0EC = (destination & 0xFFFFFFF) | 0x20000000;
    state->field0F8 = size;
    state->field0F4 = 0;
    state->field0F0 = 0;
    return func_0024ACD8(handle);
}
