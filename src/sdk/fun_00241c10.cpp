/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
s32 func_00239450();
void func_002394A0();
void func_0023ADA8(int, void (*)(void), int);
extern s32 D_002C6764;
extern s32 D_002C6788;
void func_00241BB8(void);
s32 func_00241C10(void) {
    s32 interrupts;
    D_002C6764 = 1;
    interrupts = func_00239450();
    func_0023ADA8(0x80000012, func_00241BB8, 0);
    if (interrupts != 0) {
        func_002394A0();
    }
    D_002C6764 = 0;
    D_002C6788 = 1;
    return 1;
}
}
