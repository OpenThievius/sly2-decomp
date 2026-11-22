// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "hitfx.h"
#include "stepguard.h"
#include "clock.h"
extern "C" {
int func_00208D70(STEPGUARD *);
int NCompareHitfxForGuard(STEPGUARD *, HITFX *, HITFX *);
SENSORENTRY *PentryFindSensorLo(SENSOR *, LO *);
void SetSensorEntryState(SENSOR *, SENSORENTRY *, int);
extern HITFX *B_003E148C;
extern float D_002C3DB0;
}
extern "C" HITFX *PhitfxChooseForGuard(STEPGUARD *pguard, HITFX *phitfxCurrent)
{
    VECTOR vector;
    if (func_00208D70(pguard) == 0)
        return phitfxCurrent;
    HITFX *pbest = phitfxCurrent;
    HITFX *phitfx = B_003E148C;
    while (phitfx != 0) {
        if (pguard->Slot89(phitfx) != 0) {
            if (pbest == 0 || NCompareHitfxForGuard(pguard, phitfx, pbest) < 0)
                pbest = phitfx;
        }
        phitfx = phitfx->pnext;
    }
    if (pbest != 0 && pbest->level == 4) {
        SENSORENTRY *pentry = PentryFindSensorLo(pguard->psensor, pbest->source);
        if (pentry != 0) {
            if (pentry->state == 0) {
                SetSensorEntryState(pguard->psensor, pentry, 2);
                pguard->tCooldown = g_2dded0.t + D_002C3DB0;
            }
            return phitfxCurrent;
        }
    }
    return pbest;
}
