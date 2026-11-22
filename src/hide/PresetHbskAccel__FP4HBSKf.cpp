// SPDX-License-Identifier: GPL-3.0-or-later
#include "hbsk.h"
#include "crefboxes.h"
#include "sly2.h"

struct ROWS3 { VECTOR row[3]; };
extern "C" {
void AccelSoTowardMatSpring__FP2SOP7MATRIX3P3CLQP6VECTORT2f(HBSK *, ROWS3 *, CLQ *, QW, CLQ *);
void AddSoGravityAcceleration(HBSK *);
void *PmatLoWorld(HBSK *);
void TiltMatUpright__FP7MATRIX3N20(void *, void *, ROWS3 *);
extern CLQ D_002BE8D0;
extern CLQ D_002BE8E0;
extern QW g_2a2dd0;
void PresetHbskAccel__FP4HBSKf(HBSK *phbsk) {
    ROWS3 matrix;
    AddSoGravityAcceleration(phbsk);
    if ((phbsk->fLocked != 0) && (phbsk->hbsks == 0)) {
        TiltMatUpright__FP7MATRIX3N20(PmatLoWorld(phbsk), 0, &matrix);
        AccelSoTowardMatSpring__FP2SOP7MATRIX3P3CLQP6VECTORT2f(phbsk, &matrix, &D_002BE8D0, g_2a2dd0, &D_002BE8E0);
    }
}
}
