/* SPDX-License-Identifier: GPL-3.0-or-later */
/* FADE, the screen fade (class 0x74, an LO of 0x74 bytes, PloNew(0x74, ...) in func_0020E338): colours at 0x50 to 0x58, three
   durations and the start time. Fields from the two readers that agree: DrawFade and UpdateFade (src/emitter-font/InitFade_file.cpp,
   which still has its own copy) and func_0020E338, which sets c1, d2, d3 and kind. C++ only. */
#ifndef SLY2_FADE_H
#define SLY2_FADE_H
#include "types.h"
#include "lo.h"

struct FADERGBA { u8 r, g, b, a; };

struct FADE : LO {
    /* 0x50 */ FADERGBA c0;   /* DrawFade: colour at the start */
    union {
        /* 0x54 */ FADERGBA c1;   /* the colour it fades to, holds, then leaves from */
        s32 rgbaC1;               /* func_0020E338 stores it as one word */
    };
    /* 0x58 */ FADERGBA c2;   /* the colour it ends on */
    /* 0x5C */ f32 d1;        /* DrawFade: duration of the first leg; UpdateFade sums d1 + d2 + d3 */
    /* 0x60 */ f32 d2;        /* the hold */
    /* 0x64 */ f32 d3;        /* the last leg */
    /* 0x68 */ f32 start;     /* StartFade stores g_2dded0; DrawFade and UpdateFade measure from it */
    /* 0x6C */ s32 kind;      /* DrawFade: 0 or 1 picks the display-list word */
};
#endif
