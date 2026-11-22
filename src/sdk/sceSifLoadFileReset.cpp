/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
void *memset(void *destination, s32 value, u32 size);
extern s32 B_0044C268;
extern s32 D_002C4A98;
s32 sceSifLoadFileReset(void) {
    D_002C4A98 = -1;
    memset(&B_0044C268, 0, 4);
    return 0;
}
}
