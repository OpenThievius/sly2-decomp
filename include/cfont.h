/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CFont and its bitmap-font subclass CFontBrx, as the font functions of src/font/ read them (PushScaling, PopScaling, DxFromCh,
   DxDrawCh, SwitchTex0, SetupDraw, FEnsureLoaded). C and C++ (plain fields, no virtuals). The scaling stack holds four
   entries: CFontBrx's own fields start at 0x3C (SetupDraw, DxDrawCh and SwitchTex0 read 0x3C to 0x50 as below; func_0015F710 and PglyffFromCh the fields after 0x58). */
#ifndef SLY2_CFONT_H
#define SLY2_CFONT_H
#include "types.h"
#include "ctextbox.h"

struct GIFS;

/* one entry of CFont's scaling stack (PushScaling stores the current scale, PopScaling restores it) */
struct CFONTSCALE {
    f32 sx;
    f32 sy;
};

/* a glyph of a CFontBrx (PglyffFromCh returns it; DxFromCh reads the width, DxDrawCh the rest) */
struct GLYPH {
    /* 0x0 */ u16 code;     /* PglyffFromCh: the glyph table is sorted by it (a binary search on the font's character map) */
    u16 u;
    u16 v;
    u16 width;
};

struct CFONT {
    /* 0x00 */ s32 fontk;          /* FEnsureLoaded: the font's bit in the loaded mask */
    /* 0x04 */ s32 dxChar;        /* reader: func_0015F710 (loads the font record into the object; it also writes the fields below) */
    /* 0x08 */ s32 dxSpace;        /* DxFromCh: advance of a character with no glyph, before scaling */
    /* 0x0C */ s32 lineHeight;     /* DxDrawCh */
    /* 0x10 */ f32 scaleX;         /* PushScaling, PopScaling, DxFromCh, DxDrawCh */
    /* 0x14 */ f32 scaleY;
    /* 0x18 */ s32 scaleDepth;     /* PushScaling post-increments it, PopScaling decrements it */
    /* 0x1C */ struct CFONTSCALE ascale[4];
    /* 0x3C */ s32 fTest;          /* SetupDraw: nonzero when the font carries its own TEST register value */
    /* 0x40 */ s64 test;           /* SetupDraw: PackAD register 0x47 */
    /* 0x48 */ s32 depth;         /* DxDrawCh: the Z of each glyph's vertices */
    u8 unknown_0x4C[4];
    /* 0x50 */ s64 tex0;           /* SetupDraw, SwitchTex0, DxDrawCh: PackAD register 6 */
    /* 0x58: what func_0015F710 (the font loader) stores after the bitmap and the palette are built: the sizes and the DMA packets
       of the two, then the glyph table that PglyffFromCh searches */
    /* 0x58 */ s32 cbBmp;
    /* 0x5C */ void *pqwBmp;
    /* 0x60 */ u8 packetBmp[0x60];
    /* 0xC0 */ s32 cbBmp2;
    /* 0xC4 */ void *pqwBmp2;
    /* 0xC8 */ s32 cbClut;
    /* 0xCC */ void *pqwClut;
    /* 0xD0 */ u8 packetClut[0x60];
    /* 0x130 */ s32 cbClut2;
    /* 0x134 */ void *pqwClut2;
    /* 0x138 */ s32 cglyff;        /* func_0015F710 stores it, PglyffFromCh reads it (two agree) */
    /* 0x13C */ struct GLYPH *aglyff; /* the same */
};

/* the text box SetupDraw clips to (CleanupDraw resets the scissor): CTextBox, ctextbox.h */
#endif
