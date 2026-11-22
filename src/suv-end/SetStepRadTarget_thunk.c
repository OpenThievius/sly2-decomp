/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

void SetStepRadTarget(void *pstep, float rad);

void SetStepRadTarget_thunk(void *pstep, float rad) {
    SetStepRadTarget(pstep, rad);
}
