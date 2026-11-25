/* SPDX-License-Identifier: GPL-3.0-or-later */
/* TFT, the format-conversion record of the formatted-output functions (the printf family of src/text/): CchParsePchzTft fills it from
   one `%...` specification (it clears 0x34 bytes first), WriteTft dispatches on chType and WriteTftUl, WriteTftDouble and FNegTftUl
   read the flags, the width and the precision. The flag words are 0 or 1. Private copy for wave c5 (not in include/ yet). C++ only. */
#ifndef SLY2_TFT_H
#define SLY2_TFT_H
#include "types.h"

struct TFT {
    /* 0x00 */ s32 fLeft;      /* '-' flag: CchParsePchzTft sets it (also for a negative `*` width); WriteTftUl, WriteTftDouble pad on the right */
    /* 0x04 */ s32 fPlus;      /* '+' flag */
    /* 0x08 */ s32 fSpace;     /* ' ' flag */
    /* 0x0C */ s32 fAlt;       /* '#' flag: WriteTftUl writes the 0b, 0 or 0x prefix */
    /* 0x10 */ s32 fZero;      /* '0' flag */
    /* 0x14 */ s32 fPrec;      /* CchParsePchzTft sets it when a `.` precision parsed to 0; WriteTftDouble and WriteTftUl test it */
    /* 0x18 */ s32 cchWidth;   /* the field width */
    /* 0x1C */ s32 cchPrec;    /* the precision (WriteTft sets 8 for `p`) */
    /* 0x20 */ s32 cbArg;      /* the size class: 0 int, 1 short (`h`), 2 64-bit (`l`, `ll`, `L`, `q`): WriteTft, FNegTftUl */
    /* 0x24 */ s32 cVecElem;   /* the element count of a vector conversion (`v`, `m`: 3 or 4): WriteTft */
    /* 0x28 */ s32 cVecRow;    /* the row count: 1 for `v`, the element count for `m` */
    /* 0x2C */ u8 chType;      /* the conversion character, lowered: WriteTft switches on it; FNegTftUl tests d and i */
    u8 unknown_0x2D[0x3];
    /* 0x30 */ s32 fUpper;     /* the conversion was an upper-case one: WriteTftUl and WriteTftDouble upper-case the text */
};
#endif
