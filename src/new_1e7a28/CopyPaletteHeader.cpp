#include "sly2.h"
struct B8 { char b[8]; };
struct PAL { B8 h0; B8 h1; };
#include "palette.h"
extern "C" void FilterColorRgba8_1ed278(unsigned *);
PALETTE *CopyPaletteHeader(PALETTE *dst, PALETTE *src)
{
    PAL *d = (PAL *)dst; PAL *s = (PAL *)src;
    d[0] = s[0];
    unsigned *p = dst->pdata;
    for (; p < dst->pdata + dst->cword; p++)
        FilterColorRgba8_1ed278(p);
    dst->cqw = ((unsigned)dst->cword * 4 + 0xF) >> 4;
    return dst;
}
