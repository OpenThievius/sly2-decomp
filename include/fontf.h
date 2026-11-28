/* SPDX-License-Identifier: GPL-3.0-or-later */
/* FONTF, the constant record of a built-in bitmap font, and FONTD, the descriptor that ties it to its glyph table, bitmap and palette.
   func_0015F710 (src/font/fun_0015f710.cpp, the font loader InitFonts calls through the FONTD table at 0x2BE320) copies FONTF's fields
   into the CFONT (include/cfont.h) and FONTD's glyph table into CFONT::aglyff, which PglyffFromCh searches. C and C++. */
#ifndef SLY2_FONTF_H
#define SLY2_FONTF_H
#include "types.h"

struct FONTF {
    u8 unknown_0x0[4];
    /* 0x4 */ u8 dxChar;   /* func_0015F710: CFONT::dxChar */
    /* 0x5 */ u8 dxSpace;  /* CFONT::dxSpace */
    /* 0x6 */ u8 dy;       /* CFONT::lineHeight */
    /* 0x7 */ u8 fontk;    /* CFONT::fontk */
    /* 0x8 */ f32 rScale;  /* CFONT::scaleX and scaleY */
    /* 0xC */ u16 cglyff;  /* CFONT::cglyff: the entries of the glyph table */
};
#endif
