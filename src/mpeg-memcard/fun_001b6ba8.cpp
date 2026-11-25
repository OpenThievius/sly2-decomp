// SPDX-License-Identifier: GPL-3.0-or-later
#include "lo.h"
#include "so.h"
#include "sly2.h"
#include "murray.h"
#include "joy.h"
extern "C" int FAsegaGone(int);
extern "C" int FJtStuck(MURRAY *, void *, float);
extern "C" void SetMurrayState(MURRAY *, int);
extern "C" QW SetVectorCylind__FP6VECTORfff(float, float, float);
extern "C" void WarpJtToSafePoint(MURRAY *, int);
extern "C" void func_001B6DA8(MURRAY *, int);
extern "C" float D_002BF730;
extern "C" float D_002C09A0;
extern "C" void func_001B6BA8(MURRAY *pmurray)
{
    int flops;
    for (;;) {
        int flopsStart = pmurray->field_0x13D8;
        if (pmurray->field_0x1030 == 0 || FAsegaGone((int)pmurray->field_0x1030)) {
            SetMurrayState(pmurray, 0);
        } else if (pmurray->field_0x13D8 == 1) {
            if (pmurray->field_0x13E4 != 0) {
                func_001B6DA8(pmurray, 2);
            } else if (FJtStuck(pmurray, pmurray->field_0x131C, pmurray->field_0x13DC)) {
                WarpJtToSafePoint(pmurray, 0);
            }
        }
        flops = pmurray->field_0x13D8;
        if (flops == flopsStart || flops == -1)
            break;
    }
    if (flops < 2) {
        if (flops >= 0) {
            JOY *pjoy = pmurray->pjoy;
            pmurray->velGoal = SetVectorCylind__FP6VECTORfff(pjoy->radStick + 3.1415927f, D_002C09A0 * D_002BF730 * pjoy->uStick, 0.0f);
        }
    }
}
