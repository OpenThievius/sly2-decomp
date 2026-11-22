/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
void *memset(void *destination, s32 value, u32 size);
extern s32 B_0044BDA8;
extern s32 D_002C4A7C;
s32 sceFsReset(void) {
    D_002C4A7C = 0;
    memset(&B_0044BDA8, 0, 4);
    return 0;
}
}
