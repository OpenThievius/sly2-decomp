// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "ps2inline.h"
#include "vu0inline.h"
#include "dancer.h"
#include "rhythm.h"
union VU_SCALE { QW q; VECTOR v; };
extern "C" {
extern RHYTHM *B_002DE570;
void UpdateStep(DANCER *, float);
int FAsegaGone(ASEGA *);
void SetXfKind(SO *, XF *, int);
void PlayDancerAnim(DANCER *, void *, int);
void PlayDancerMove(DANCER *, int, int, int);
void JudgeRhythmPress(RHYTHM *, DANCER *);
QW func_00204E38(DANCER *, ASEGA *, float);
}
void UpdateDancer(DANCER *dancer, float dt)
{
    UpdateStep(dancer, dt);
    ASEGA *pasega = dancer->pasega;
    if (pasega == 0 || FAsegaGone(pasega)) {
        SetXfKind(dancer, dancer->pxfLinear, 1);
        SetXfKind(dancer, dancer->pxfAngular, 1);
        dancer->fMove = 0;
        PlayDancerAnim(dancer, dancer->pasegIdle, 8);
    }
    int state = 0;
    if (B_002DE570)
        state = B_002DE570->mode;
    switch (state) {
    case 0:
        if (dancer->fMove == 0)
            PlayDancerMove(dancer, -1, -1, 0);
        break;
    case 2:
        JudgeRhythmPress(B_002DE570, dancer);
        break;
    }
    ASEGA *panim = dancer->pasega;
    if (panim) {
        QW vel = func_00204E38(dancer, panim, panim->tLocal);
        VU_SCALE scale;
        scale.q = VectorFromFloat(-1.0f);
        dancer->velGoal = VectorScaleX(vel, scale.q);
    }
}
