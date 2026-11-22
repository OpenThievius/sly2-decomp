/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "pad.h"
extern "C" {
s32 func_00239450();
void func_002394A0();
PADFRAME *func_00243270(s32, s32);
extern PADPORT B_004505D0[];
s32 func_00243458(s32 port, s32 slot, s32 mode) {
    s32 interrupts;
    if (B_004505D0[port].slot[slot].opened == 0) {
        return 0;
    }
    interrupts = func_00239450();
    func_00243270(port, slot)->requestState = mode;
    if (interrupts == 1) {
        func_002394A0();
    }
    return 1;
}
}
