/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guard.h"

void SetStepRadTarget(struct STEP *, f32);

void func_00209818(struct GUARDHEADING *pheading, f32 radTarget) {
    if (pheading->fHold == 0) {
        SetStepRadTarget(pheading->pstep, radTarget);
    }
}
