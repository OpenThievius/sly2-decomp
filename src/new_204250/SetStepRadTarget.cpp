// SPDX-License-Identifier: GPL-3.0-or-later
#include "step.h"

extern "C" {
MATRIX3Q LoadRotateMatrixRad(QW axis, float rad);
extern QW g_2a2dc0;

void SetStepRadTarget(STEP *pstep, float rad) {
    pstep->radHeading = rad;
    pstep->matHeading = LoadRotateMatrixRad(g_2a2dc0, rad);
}
}
