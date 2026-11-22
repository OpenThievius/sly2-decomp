/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
void func_00235868(int);
s32 func_002368A0(s32 unused_first, s32 unused_second, s32 value) {
    if (value != 0) {
        func_00235868(value);
    }
    return 1;
}
}
