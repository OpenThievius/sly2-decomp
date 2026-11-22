/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pad.h"
extern "C" {
s32 func_00242F70(s32 port, s32 slot);
PADFRAME *func_00243270(s32 port, s32 slot);
extern PADPORT B_004505D0[];
s32 scePadSetActDirect(s32 port, s32 slot, u8 *data) {
    s32 index;
    s32 result;
    PADACT *request;
    if (func_00243270(port, slot)->field_0x72 != 1) {
        return 0;
    }
    request = B_004505D0[port].slot[slot].act;
    for (index = 0; index < 6; index++) {
        request->data[index] = data[index];
    }
    result = 1;
    request->pending = result;
    request->length = 6;
    if (func_00242F70(port, slot) != 1) {
        result = 0;
    }
    return result;
}
}
