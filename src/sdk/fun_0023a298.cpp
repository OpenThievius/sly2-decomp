/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
s32 func_00239450();
void func_002394A0();
s32 func_0023A228();
s32 func_0023A298(void) {
    s32 interrupts;
    s32 result;
    interrupts = func_00239450();
    result = func_0023A228();
    if (interrupts != 0) {
        func_002394A0();
    }
    return result;
}
}
