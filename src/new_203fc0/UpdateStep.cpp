// SPDX-License-Identifier: GPL-3.0-or-later
#include "step.h"
#include "clock.h"
#include "sly2.h"
extern "C" void UpdateSo(STEP *);
void UpdateStepPhys(STEP *);
extern "C" float atan2f(float, float);
float RadNormalize(float);
extern "C" float D_002C3C80[3];
extern "C" float g_2bbb60[2];

void UpdateStep(STEP *pstep)
{
    UpdateSo(pstep);
    UpdateStepPhys(pstep);
    int mode = pstep->fLock;
    switch (mode) {
    case 0: {
        MATRIX4 *pmatForY = pstep->PmatWorld();
        MATRIX4 *pmatForX = pstep->PmatWorld();
        float radCurrent = atan2f(pmatForY->mat[0][1], pmatForX->mat[0][0]);
        float dradHeading = RadNormalize(pstep->radHeading - radCurrent);
        float gAbs = dradHeading < 0.0f ? -dradHeading : dradHeading;
        float uRun = D_002C3C80[0] + gAbs * (D_002C3C80[1] + gAbs * D_002C3C80[2]);
        float uMin = g_2bbb60[0];
        float uMax = g_2bbb60[1];
        if (uRun < uMin)
            uRun = uMin;
        else if (uMax < uRun)
            uRun = uMax;
        pstep->uTarget = uRun;
        break;
    }
    case 1:
    case -1: {
        float one = 1.0f;
        pstep->uTarget = one;
        break;
    }
    }
    if (pstep->psoSurface != 0)
        pstep->tJump = g_2dded0.t;
}
