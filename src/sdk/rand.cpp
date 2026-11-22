/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "libcstate.h"
extern "C" {
extern LIBCSTATE *D_002C49D4;
s32 rand(void) {
    s32 next;
    next = (D_002C49D4->randomSeed * 0x41C64E6D) + 0x3039;
    D_002C49D4->randomSeed = next;
    return next & 0x7FFFFFFF;
}
}
