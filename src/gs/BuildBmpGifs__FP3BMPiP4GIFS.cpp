#include "types.h"
struct GIFS;
struct BMP {
    s16 x0, y0;
    u8 unknown_0x4[4];
    u16 w;
    u16 h;
    u8 b0xC;
    u8 b0xD;
    u8 unknown_0xE[2];
    int unk0x10;
    int unk0x14;
    int count;
};
extern "C" void BuildImageGifs__FiiiiiiP4GIFS(int, int, int, int, int, int, GIFS *);
extern "C" void BuildBmpGifs__FP3BMPiP4GIFS(BMP *bmp, int block, GIFS *gifs)
{
    BuildImageGifs__FiiiiiiP4GIFS(block, bmp->b0xD, bmp->b0xC, bmp->w, bmp->h, bmp->count, gifs);
}
