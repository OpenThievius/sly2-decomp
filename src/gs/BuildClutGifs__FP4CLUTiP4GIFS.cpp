#include "types.h"
/* a palette: BuildClutGifs reads its colour count and the word at 0x10 that BuildImageGifs takes last (BuildClutTex2 has its own view) */
struct CLUT {
    u8 unknown_0x0[8];
    /* 0x08 */ u16 count;
    u8 unknown_0xA[6];
    /* 0x10 */ s32 field_0x10;
};
extern "C" {
void BuildImageGifs__FiiiiiiP4GIFS(s32, s32, s32, s32, s32, s32, void *);
void BuildClutGifs__FP4CLUTiP4GIFS(CLUT *arg0, s32 arg1, void *arg2) {
    s32 step = arg0->count >= 0x11U ? 0x10 : 8;
    unsigned last = arg0->count - 1;
    BuildImageGifs__FiiiiiiP4GIFS(arg1, 1, 0, step, (s32)((last + step) & -step) / step, arg0->field_0x10, arg2);
}
}
