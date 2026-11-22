// SPDX-License-Identifier: GPL-3.0-or-later
#include "step.h"
#include "xf.h"
struct SMP;
extern "C" float atan2f(float, float);
float RadSmooth(float, float, float, SMP *, float *);
void FixStepAngularVelocity(STEP *pstep)
{
    VECTOR w = *(VECTOR *)&pstep->pxfAngular->vel;
    MATRIX4 *pmat = pstep->PmatWorld();
    MATRIX4 *pmat2 = pstep->PmatWorld();
    float radCur = atan2f(pmat->mat[0][1], pmat2->mat[0][0]);
    RadSmooth(radCur, pstep->radHeading, 0.0f, (SMP *)&pstep->field_0x1F4, &w.z);
    pstep->Slot36(*(QW *)&w);
}
