// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "clock.h"
#include "loot.h"
struct MATRIX44 { float mat[4][4]; } __attribute__((aligned(16)));
struct ROWS3 { VECTOR row[3]; };
// local view: the blend duration sits inside LOOT's unknown span, read here only
struct LOOTBLENDVIEW { u8 unknown_0x0[0x180]; float dtBlend; };
struct LM { float lo; float hi; };
extern "C" LM g_2bbb60;
extern const float RO_002A4B30[4];
extern "C" void func_001F3C70(LOOT *);
extern "C" void func_001A5EE8(LOOT *, MATRIX44 *, float, float);
extern "C" void LoadMatrixFromPosRotScale(MATRIX44 *, QW, ROWS3 *, float *);
extern "C" QW PosLoWorld(LOOT *);
extern "C" ROWS3 *PmatLoWorld(LOOT *);
static inline float GLimitLm(LM *plm, float g)
{
    float lo = plm->lo;
    float hi = plm->hi;
    if (g < lo)
        return lo;
    if (hi < g)
        return hi;
    return g;
}
extern "C" void RenderLoot(LOOT *ploot)
{
    char buf[0x90] __attribute__((aligned(16)));
    switch (ploot->state) {
    case 4: {
        float dtBlend = ((LOOTBLENDVIEW *)ploot)->dtBlend;
        float elapsed = g_2dded0.t - ploot->tState;
        if (dtBlend <= elapsed) {
            *(QW *)buf = ploot->vHeld;
        } else {
            float u = elapsed / dtBlend;
            float gBlend = GLimitLm(&g_2bbb60, RO_002A4B30[0] + u * (RO_002A4B30[1] + u * RO_002A4B30[2]));
            float *pheld = (float *)&ploot->vHeld;
            float *pscale = (float *)buf;
            for (int iaxis = 0; iaxis < 3; iaxis++)
                pscale[iaxis] = (1.0f - gBlend) + gBlend * pheld[iaxis];
        }
        MATRIX44 *pmat = (MATRIX44 *)(buf + 0x50);
        QW pos = PosLoWorld(ploot);
        LoadMatrixFromPosRotScale(pmat, pos, PmatLoWorld(ploot), (float *)buf);
        *(MATRIX44 *)(buf + 0x10) = *(MATRIX44 *)(buf + 0x50);
        func_001A5EE8(ploot, (MATRIX44 *)(buf + 0x10), 1.0f, 1.0f);
        break;
    }
    case 1:
    case 5:
        func_001F3C70(ploot);
        break;
    case 2:
    case 3:
        break;
    }
}
