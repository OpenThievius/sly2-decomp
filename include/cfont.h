/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CFont and its bitmap-font subclass CFontBrx, as the font functions of src/font/ read them (PushScaling, PopScaling, DxFromCh,
   DxDrawCh, SwitchTex0, SetupDraw, FEnsureLoaded). C and C++ (plain fields, no virtuals). The scaling stack holds four
   entries: CFontBrx's own fields start at 0x3C (SetupDraw, DxDrawCh and SwitchTex0 read 0x3C to 0x50 as below). */
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
    u8 unknown_0x0[2];
    u16 u;
    u16 v;
    u16 width;
};

struct CFONT {
    /* 0x00 */ s32 fontk;          /* FEnsureLoaded: the font's bit in the loaded mask */
    u8 unknown_0x4[4];
    /* 0x08 */ s32 dxSpace;        /* DxFromCh: advance of a character with no glyph, before scaling */
    /* 0x0C */ s32 lineHeight;     /* DxDrawCh */
    /* 0x10 */ f32 scaleX;         /* PushScaling, PopScaling, DxFromCh, DxDrawCh */
    /* 0x14 */ f32 scaleY;
    /* 0x18 */ s32 scaleDepth;     /* PushScaling post-increments it, PopScaling decrements it */
    /* 0x1C */ struct CFONTSCALE ascale[4];
    /* 0x3C */ s32 fTest;          /* SetupDraw: nonzero when the font carries its own TEST register value */
    /* 0x40 */ s64 test;           /* SetupDraw: PackAD register 0x47 */
    u8 unknown_0x48[8];            /* 0x48 holds DxDrawCh's depth */
    /* 0x50 */ s64 tex0;           /* SetupDraw, SwitchTex0, DxDrawCh: PackAD register 6 */
};

/* the text box SetupDraw clips to (CleanupDraw resets the scissor): CTextBox, ctextbox.h */
#endif
