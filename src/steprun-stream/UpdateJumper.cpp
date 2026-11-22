// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
extern float g_2dded0;
extern float D_002C3DE0;
extern "C" {
void SetJumperState(JUMPER *, int);
int FIsBasicDerivedFrom(STEP *, int);
void EnableFallCheck(void *);
int FAsegaGone(void *);
void UpdateJumper(JUMPER *pjumper)
{
    for (;;) {
        int state = pjumper->state;
        switch (state) {
        case 1:
            if (pjumper->pso->psoSurface != 0 && pjumper->tState + 0.15f < g_2dded0)
                SetJumperState(pjumper, 3);
            else if (pjumper->tLandStart <= g_2dded0)
                SetJumperState(pjumper, 2);
            break;
        case 2:
            if (pjumper->pso->psoSurface != 0 || D_002C3DE0 < g_2dded0 - pjumper->tLand)
                SetJumperState(pjumper, 3);
            else if (pjumper->tLand <= g_2dded0) {
                if (pjumper->fTrackTarget != 0)
                    SetJumperState(pjumper, 3);
                else if (FIsBasicDerivedFrom(pjumper->pso, 0x38))
                    EnableFallCheck(((STEPGUARD *)pjumper->pso)->pfallcheck);
            }
            break;
        case 3:
            if (FAsegaGone(pjumper->pasega))
                SetJumperState(pjumper, 4);
            break;
        default:
            break;
        }
        if (state == pjumper->state) return;
    }
}
}
