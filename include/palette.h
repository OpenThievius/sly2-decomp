/* SPDX-License-Identifier: GPL-3.0-or-later */
/* PALETTE (0x20 bytes) and MATERIAL (0x28 bytes), the records of the tables at B_003DCFFC and B_003DCFF4 (counts B_003DCFF8 and
   B_003DCFF0). Local to the src/new_1e7a28 sources: func_001EA568 (rebases pdata of both), func_001EA8A8 (reads one palette
   from the stream), func_001EAE40 (reads the table), CopyPaletteHeader (copies the first eight bytes). Fields by their readers. C++ only. */
#ifndef WAVE_C5_PALETTE_H
#define WAVE_C5_PALETTE_H
#include "types.h"

struct PALETTE {
    /* 0x00 */ s32 id;          /* func_001EA8A8 looks up a shared palette by it */
    /* 0x04 */ u8 kind;         /* 1: pdata is an offset to rebase (func_001EA568), counted by func_001EAE40 */
    /* 0x05 */ s8 ccond;        /* func_001EA8A8: the number of load conditions */
    u8 unknown_0x6[2];
    /* 0x08 */ u16 cword;       /* the colour count: func_001EA568, func_001EA8A8, CopyPaletteHeader */
    u8 unknown_0xA[2];
    /* 0x0C */ u32 *pdata;      /* the colours */
    /* 0x10 */ s32 cqw;         /* the colour count in quadwords: func_001EA8A8, CopyPaletteHeader */
    u8 unknown_0x14[0xC];
};

struct MATERIAL {
    u8 unknown_0x0[4];
    /* 0x04 */ u8 kind;         /* func_001EA568 */
    u8 unknown_0x5[0xF];
    /* 0x14 */ s32 pdata;       /* func_001EA568 rebases it */
    u8 unknown_0x18[0x10];
};
#endif
