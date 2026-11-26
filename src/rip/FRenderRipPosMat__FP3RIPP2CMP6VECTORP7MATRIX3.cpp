// SPDX-License-Identifier: GPL-3.0-or-later
#include "ps2inline.h"
#include "vu0inline.h"
#include "sly2.h"
#include "rip.h"
#include "alo.h"
#include "cm.h"
#include "rows3.h"
struct MATRIX44 { float mat[4][4]; } __attribute__((aligned(16)));
struct LM { float lo; float hi; };
extern "C" LM g_2bbb60;
extern "C" float g_2dded0;
extern "C" int FInsideCmFrustrum(CM *, QW, QW);
extern "C" int FInsideCmMrd(CM *, QW, float *, float);
extern "C" MATRIX44 func_0011C288(QW, ROWS3 *, float);
extern "C" void func_001A5EE8(ALO *, MATRIX44 *, float, float);
static inline float Quadratic(RIPQUADRATIC *pcoeffs, float u)
{
    return pcoeffs->c0 + u * (pcoeffs->c1 + u * pcoeffs->c2);
}
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
int FRenderRipPosMat__FP3RIPP2CMP6VECTORP7MATRIX3(RIP *rip, QW pos, ROWS3 *rows)
{
    if (rip->palo == 0)
        return 1;
    float duration = rip->dtLifetime;
    if (duration <= 0.0f)
        return 0;
    float u = (g_2dded0 - rip->tStart) / duration;
    float gScale = GLimitLm(&g_2bbb60, Quadratic(&rip->scale, u));
    float radius = Quadratic(&rip->radius, u);
    QW offset = VectorSub(pos, B_002DDF40.mat.row[3]);
    union { QW q; float f[4]; } extent;
    extent.q = QuadFromFloat(radius * 100.0f);
    if (!FInsideCmFrustrum(&B_002DDF40, offset, extent.q))
        return 1;
    float t;
    if (!FInsideCmMrd(&B_002DDF40, offset, &t, rip->palo->field_0x38))
        return 0;
    if (gScale < 0.0001f && radius < 0.0001f)
        return 1;
    MATRIX44 world;
    MATRIX44 built = func_0011C288(pos, rows, radius);
    world = built;
    func_001A5EE8(rip->palo, &world, gScale * t, 1.0f);
    return 1;
}
