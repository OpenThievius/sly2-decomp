/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The movie font of src/font-break/ (DxFromFontCh, PglyphFromFontCh; IglyphFromFontCh maps a character to a 1-based glyph index):
   a table of 0x40-byte glyph records at 0x14 and the advance of each glyph at 0x1C. Not CFONT (cfont.h): its field 0x14 is the
   scale. C and C++. */
#ifndef FBFONT_H
#define FBFONT_H
#include "types.h"

typedef struct MOVIEGLYPH {
    u8 unknown_0x0[0x40];
} MOVIEGLYPH;

typedef struct MOVIEFONT {
    u8 unknown_0x0[0x14];
    /* 0x14 */ MOVIEGLYPH *aglyph;  /* PglyphFromFontCh */
    u8 unknown_0x18[4];
    /* 0x1C */ f32 *adx;            /* DxFromFontCh */
} MOVIEFONT;
#endif
