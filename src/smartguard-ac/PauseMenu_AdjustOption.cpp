// SPDX-License-Identifier: GPL-3.0-or-later
// source:sly1-decomp HandlePauseMenuInput (src/main/pause_menu.cpp, AGPL-3.0, same maintainers): display register types, a draft
#include "types.h"
struct LM { float gMin; float gMax; };
struct SNDBANKS { char pad[0x14C]; float gVolumeMusic; float gVolumeFx; };
struct DisplayReg64 { u64 lo : 12; u64 mid : 11; u64 rest : 41; };
struct DisplayReg32 { u32 lo : 12; u32 mid : 11; u32 rest : 9; u32 hi; } __attribute__((aligned(8)));
struct DisplayRegs { u8 pad0[0x18]; DisplayReg32 f18; u8 pad20[0x20]; DisplayReg64 f40; };
struct BLOT;
struct ITEM { int kind; };
struct PAGE { int citem; ITEM *aitem; BLOT *pblot; };
struct PAUSEMENU { char pad0[0x10]; void *pjoy; };
extern "C" {
float GLimitLm__FP2LMf(LM *, float);
void SetSndbankVolumeFactor(SNDBANKS *, int, float, int);
void SeekBlotLabel(BLOT *, int, float);
int UpdateJoyNavX(void *);
int UpdateJoyNavY(void *);
s32 func_0023E1C8(float);
extern DisplayRegs D_002DEB80;
extern SNDBANKS D_003DD040;
extern float D_002F6468;
extern float D_002F646C;
extern float D_002C01C8;
extern float D_002C01CC;
extern LM g_2bbb60;
extern float g_2ddf10;
}
static inline float ClampFloat(float value, float low, float high)
{
    if (value < low)
        return low;
    if (high < value)
        return high;
    return value;
}
extern "C" void PauseMenu_AdjustOption(PAUSEMENU *pmenu, PAGE *ppage, ITEM *pitem)
{
    float g;
    switch (pitem->kind) {
    case 0x67: {
        float dx = (float)UpdateJoyNavX(pmenu->pjoy);
        if (dx != 0.0f) {
            g = GLimitLm__FP2LMf(&g_2bbb60, D_003DD040.gVolumeFx + dx * g_2ddf10 * 1.5f);
            SetSndbankVolumeFactor(&D_003DD040, 1, g, 1);
            SeekBlotLabel(ppage->pblot, 0x315, g);
        }
        break;
    }
    case 0x68: {
        float dx = (float)UpdateJoyNavX(pmenu->pjoy);
        if (dx != 0.0f) {
            g = GLimitLm__FP2LMf(&g_2bbb60, D_003DD040.gVolumeMusic + dx * g_2ddf10 * 1.5f);
            SetSndbankVolumeFactor(&D_003DD040, 0, g, 1);
            SetSndbankVolumeFactor(&D_003DD040, 3, g, 1);
            SeekBlotLabel(ppage->pblot, 0x315, g);
        }
        break;
    }
    case 0x3F: {
        float dx = (float)UpdateJoyNavX(pmenu->pjoy);
        float dy = (float)UpdateJoyNavY(pmenu->pjoy);
        if (dx == 0.0f && dy == 0.0f)
            break;
        D_002F6468 = ClampFloat(D_002F6468 + dx * D_002C01C8, 424.0f, 848.0f);
        float v = ClampFloat(D_002F646C + dy * D_002C01CC, 10.0f, 90.0f);
        D_002F646C = v;
        DisplayRegs *gs = &D_002DEB80;
        s32 h = func_0023E1C8(D_002F6468);
        DisplayReg64 ra = gs->f40;
        DisplayReg32 rb = gs->f18;
        ra.lo = h;
        rb.lo = h;
        gs->f40 = ra;
        gs->f18 = rb;
        s32 w = func_0023E1C8(v);
        ra.mid = w & ~1;
        rb.mid = w & 0x7FE;
        gs->f40 = ra;
        gs->f18 = rb;
        break;
    }
    }
}
