/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "pad.h"
extern "C" {
s32 func_00239450();
void func_002394A0();
PADFRAME *func_00243270(s32, s32);
extern PADPORT B_004505D0[];
u8 func_00243388(s32 port, s32 slot) {
    s32 interrupts;
    PADFRAME *frame;
    if (B_004505D0[port].slot[slot].opened == 0) {
        return 0x63;
    }
    interrupts = func_00239450();
    frame = func_00243270(port, slot);
    if (frame->state == 6) {
        if (frame->requestState == 2) {
            if (interrupts == 1) {
                func_002394A0();
            }
            return 5;
        }
    }
    if (interrupts == 1) {
        func_002394A0();
    }
    return frame->state;
}
}
