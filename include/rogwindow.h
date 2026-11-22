/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ROGWINDOW: one 0x28-byte window record of the array at 0x3E1A78 (B_003E1A78): func_001BE6F0 reads its size, origin and camera,
   func_001BEE10 divides by its size to index a table. C and C++. */
#ifndef SLY2_ROGWINDOW_H
#define SLY2_ROGWINDOW_H
#include "types.h"

struct ROGWINDOW {
    /* 0x00 */ s32 width;
    /* 0x04 */ s32 height;
    u8 unknown_0x8[0x8];
    /* 0x10 */ s32 originX;
    /* 0x14 */ s32 originY;
    u8 unknown_0x18[0x8];
    /* 0x20 */ void *pcamobj;
    u8 unknown_0x24[0x4];
};
#endif
