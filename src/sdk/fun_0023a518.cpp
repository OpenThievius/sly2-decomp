/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
struct ALARMSLOT;
s32 func_00239450();
void func_002394A0();
s32 func_0023A420(s32, s32, void (*)(void), ALARMSLOT *);
s32 func_0023A518(s32 id, s32 time, void (*callback)(void), ALARMSLOT *slot) {
    s32 interrupts;
    s32 result;
    interrupts = func_00239450();
    result = func_0023A420(id, time, callback, slot);
    if (interrupts != 0) {
        func_002394A0();
    }
    return result;
}
}
