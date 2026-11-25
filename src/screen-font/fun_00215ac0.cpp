#include "sly2.h"
#include "sw.h"
struct MT { int a; int unknown_0x4; int cur; int base; int other; u8 unknown_0x14[4]; int rgba; u8 unknown_0x1C[0x24]; QW r0; QW r1; u8 unknown_0x60[4]; float ox; float oy; int z6c; int z70; int z74; int z78; float f7c; float f80; float f84; float f88; int i8c; int i90; int i94; };
struct FONTINFO { u8 unknown_0x0[0x54]; s32 word54; };
extern SW B_003DD490;
extern "C" QW g_2a2e10;
extern "C" QW g_2a2e20;
extern "C" void CMovieText_Reset(MT *, int);
MT *func_00215AC0(MT *t, int a, float scale)
{
    t->a = a;
    t->f7c = 1.0f; //P
    t->f88 = scale; //P
    t->f80 = 1.0f; //P
    t->ox = 1792.0f; //P
    t->oy = 1936.0f; //P
    t->z6c = 0; //P
    t->z70 = 0; //P
    t->z74 = 0; //P
    t->z78 = 0; //P
    t->i90 = 1;
    t->i8c = 1;
    t->i94 = 6;
    t->f84 = scale * 51.2f; //P
    int pf = ((FONTINFO *)B_003DD490.pfont)->word54;
    t->base = pf;
    t->cur = pf;
    t->other = ((FONTINFO *)B_003DD490.pfont)->word54 + 0x40;
    t->rgba = 0x80808080;
    t->r0 = g_2a2e10;
    t->r1 = g_2a2e20;
    CMovieText_Reset(t, 0);
    return t;
}
