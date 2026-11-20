#include "sly2.h"
struct RGBA { unsigned char r, g, b, a; };
struct RGBA5551 { unsigned short r : 5, g : 5, b : 5, a : 1; };
extern "C" int B_003E12C8;
extern "C" void FilterColorRgba8_1ed278(RGBA *);

static inline void SetRgba(RGBA *prgba, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    prgba->r = r;
    prgba->g = g;
    prgba->b = b;
    prgba->a = a;
}

void FilterColorRgba5551_1ed1a8(RGBA5551 *pcolor)
{
    RGBA rgba;
    RGBA copy;
    RGBA5551 out;
    if (B_003E12C8) {
        SetRgba(&rgba, pcolor->r << 3, pcolor->g << 3, pcolor->b << 3, pcolor->a ? 0xFF : 0);
        FilterColorRgba8_1ed278(&rgba);
        copy = rgba;
        out.r = copy.r >> 3;
        out.g = copy.g >> 3;
        out.b = copy.b >> 3;
        out.a = copy.a >> 7;
        *pcolor = out;
    }
}
