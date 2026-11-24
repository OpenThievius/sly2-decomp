/* SPDX-License-Identifier: GPL-3.0-or-later */
/* RGBA, a colour: four bytes, red first, 4-byte aligned (C and C++). The GS packers take it as one word (GIFS::PackRGBA,
   FillScreenRectImpl, DrawLoadingLogo read *(u32 *)&rgba), BuildClearGifs reads the bytes one by one, and the alpha byte's sign
   bit picks the blend (BuildClearGifs, DrawLoadingLogo). Its users: the camera's fog colour (cm.h), CRichText's base colour,
   CProg's four colours, the sprite and movie text colours of font-break and screen-font, the shaders' texture colour, the static
   bitmaps' palette. source:sly1 RGBA (common.h: bRed, bGreen, bBlue, bAlpha there; the names here are ours). */
#ifndef SLY2_RGBA_H
#define SLY2_RGBA_H
/* No types.h: FillShaders declares its own opaque QW, which types.h's typedef of QW would clash with. */
struct RGBA {
    unsigned char r, g, b, a;
};

#if defined(__mips__)
typedef char check_RGBA_size[(sizeof(struct RGBA) == 4) ? 1 : -1];
#endif
#endif
