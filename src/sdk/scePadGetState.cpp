/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pad.h"
extern "C" {
PADFRAME *func_00243270(s32 port, s32 slot);
extern PADPORT B_004505D0[];
u8 scePadGetState(s32 port, s32 slot) {
    if (B_004505D0[port].slot[slot].opened == 0) {
        return 0;
    }
    return func_00243270(port, slot)->requestState;
}
}
