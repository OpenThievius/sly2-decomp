// SPDX-License-Identifier: GPL-3.0-or-later
#include "goalpatrol.h"
/* a quadword in one 128-bit register */
extern "C" QW PosLoWorld(LO *);
extern "C" int FFindSurfaceAlongUp(QW *, int, int, float, float);
int func_0014A478(GOALPATROL *pgoal) {
    STEPGUARD *pguard;
    QW pos;
    pguard = GOAL_GUARD(pgoal);
    if (pguard->psoSurface != 0) {
        return 0;
    }
    pos = PosLoWorld(pguard);
    return FFindSurfaceAlongUp(&pos, 1, 0, 100.0f, -250.0f) == 0;
}
