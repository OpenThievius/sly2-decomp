// SPDX-License-Identifier: GPL-3.0-or-later
#include "guardview.h"
#include "joy.h"

f32 RadYawSo(struct STEPVIEW *pstep);
void RotateSoToMat();                               /* extern */
void SetStepRadTarget(struct STEPVIEW *pstep, f32 radTarget);

void RotateStepToMat(struct STEPVIEW *pstep) {
    struct JOY *pjoy;

    RotateSoToMat();
    SetStepRadTarget(pstep, RadYawSo(pstep));
    pjoy = pstep->pjoy;
    if (pjoy != 0) {
        pjoy->radStick = pstep->radHeading;
    }
}
