#include "blot.h"
#include "sw.h"
#include "rgba.h"
/* a movie text: p, rgbaCur, rgbaOther and changed are CMovieText_ChNext's (same offsets for cur, base, other and the base colour rgba) */
struct MT { int a; unsigned char *p; int cur; int base; int other; RGBA rgbaCur; int rgba; RGBA rgbaOther; u8 unknown_0x20[0x20]; QW r0; QW r1; int changed; float ox; float oy; int z6c; int z70; float f74; float f78; float f7c; float f80; float f84; float f88; int i8c; int i90; int i94; };
struct SRC { u8 unknown_0x0[8]; BLOT *owner; u8 unknown_0xC[0x10]; int i1c; float f20; float f24; float f28; int i2c; int i30; };
struct M3 { QW r[3]; };
struct FONTINFO { u8 unknown_0x0[0x54]; s32 word54; };
extern SW B_003DD490;
extern "C" void CMovieText_Reset(MT *, int);

MT *func_00215BA8(MT *t, int a, SRC *s, char *slot)
{
    M3 m = *(M3 *)slot;
    t->a = a;
    t->z6c = 0;
    t->z70 = 0;
    t->f74 = s->f24;
    t->f78 = s->f28;
    t->f7c = 1.0f;
    t->f80 = 1.0f;
    t->i90 = s->i2c;
    t->i8c = s->i30;
    t->ox = s->owner->pblotSelf->field_0x9C;
    t->oy = s->owner->pblotSelf->field_0xA0;
    t->i94 = s->owner->order;
    float g = s->f20;
    t->f84 = g;
    t->f88 = g * 0.01953125f;
    int pf = ((FONTINFO *)B_003DD490.pfont)->word54;
    t->base = pf;
    t->cur = pf;
    t->other = ((FONTINFO *)B_003DD490.pfont)->word54 + 0x40;
    t->rgba = s->i1c;
    t->r0 = m.r[1];
    t->r1 = m.r[2];
    CMovieText_Reset(t, 0);
    return t;
}
