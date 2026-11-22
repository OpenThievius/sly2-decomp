/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
s32 GetMemorySize();
void _InitTLB();
void func_0023B3A8();
void func_0023B368(void) {
    if (GetMemorySize() == 0x02000000) {
        func_0023B3A8();
        return;
    }
    _InitTLB();
}
}
