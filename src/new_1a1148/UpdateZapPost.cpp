// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "jtzap.h"
#include "clock.h"
struct SMP;
struct LM { float lo; float hi; };
// SO's word at 0xD0 as retail's zap code reads it: a float alpha (so.h has it as the low half of a 64-bit flag word)
struct JTALPHA { u8 unknown_0x0[0xD0]; float alpha; };
extern "C" {
extern LM g_2bbb60;
extern const float D_002BFAA0[3];
extern const float D_002BFAB0[3];
extern SMP D_002BFAC0;
float cosf(float);
float atan2f(float, float);
void func_001F4BF8(JT *);
void SetStepRadTarget(JT *, float);
int FJtStuck(JT *, void *, float);
void ZapContinue(JTZAP *);
}
float RadSmooth(float, float, float, SMP *, float *);

// Same clamp as RenderLoot: retail loads lo and hi before the two compares.
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

// Retail clamps both quadratics with the same lo/hi pair at g_2bbb60 (each
// clamp reloads it), so both go through one inline GLimitLm. ZapContinue
// takes the zap in $a0 (its own disassembly), and FJtStuck takes
// (jt, vector, time): $a0 = jt, $a1 = 0, $f12 = tState.
void UpdateZapPost(JTZAP *pzap)
{
    if (pzap->flash != -1) {
        float uFade;
        if (pzap->state == -1) {
            float dtElapsed = g_2dded0.t - pzap->tFlash;
            float dtFlash = pzap->dtFlash;
            if (dtFlash < dtElapsed) {
                pzap->flash = -1;
                ((JTALPHA *)pzap->pjt)->alpha = 0.0f;
                func_001F4BF8(pzap->pjt);
                goto after_flash;
            }
            uFade = dtElapsed / dtFlash;
        } else {
            uFade = 0.0f;
        }
        float cosine = cosf((g_2dded0.t - pzap->tPulseStart) * 10.0f);
        float alpha = GLimitLm(&g_2bbb60, D_002BFAA0[0] + uFade * (D_002BFAA0[1] + uFade * D_002BFAA0[2]));
        float pulse = GLimitLm(&g_2bbb60, D_002BFAB0[0] + cosine * (D_002BFAB0[1] + cosine * D_002BFAB0[2]));
        ((JTALPHA *)pzap->pjt)->alpha = alpha * pulse;
    }
after_flash:
    if (pzap->state == -1)
        return;
    if (pzap->state != 7)
        return;
    JT *pjt = pzap->pjt;
    QW velocity = pjt->GetVelocityVec();
    float *pvelocity = (float *)&velocity;
    float radHeading = atan2f(pvelocity[1], pvelocity[0]);
    float radTarget = RadSmooth(pzap->pjt->radHeading, radHeading + 3.1415927f, g_2dded0.dt, &D_002BFAC0, 0);
    SetStepRadTarget(pzap->pjt, radTarget);
    if (0.25f < g_2dded0.t - pzap->tState) {
        if (pzap->pjt->psoSurface != 0) {
            ZapContinue(pzap);
            return;
        }
    }
    if (FJtStuck(pzap->pjt, 0, pzap->tState) != 0)
        ZapContinue(pzap);
}
