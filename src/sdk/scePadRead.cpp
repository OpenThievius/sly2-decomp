/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pad.h"
extern "C" {
s32 func_00239450();
void func_002394A0();
PADFRAME *func_00243270(s32 port, s32 slot);
void *memcpy(void *destination, const void *source, u32 size);
extern PADPORT B_004505D0[];
s32 scePadRead(s32 port, s32 slot, void *destination) {
    s32 interrupts;
    PADFRAME *frame;
    if (B_004505D0[port].slot[slot].opened == 0) {
        return 0;
    }
    interrupts = func_00239450();
    frame = func_00243270(port, slot);
    memcpy(destination, frame, frame->length);
    if (interrupts == 1) {
        func_002394A0();
    }
    return frame->length;
}
}
