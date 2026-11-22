// SPDX-License-Identifier: GPL-3.0-or-later
#include "step.h"
extern "C" void PostSoLoad(STEP *);
extern "C" int PcrvNew(int, int);
extern "C" void SetXfKind(STEP *, XF *, int);
extern "C" void *PpartFindAlo(STEP *, int);
extern "C" void CloneStepHullGeom(STEP *, void *);
extern "C" void func_001F2AD0(STEP *, void *);
extern "C" void GoalStack_AllocGoals(void *);
extern "C" void PostStepLoad(STEP *pstep)
{
    PostSoLoad(pstep);
    pstep->pcrv = (void *)PcrvNew(0x2C9, 0x10);
    SetXfKind(pstep, pstep->pxfLinear, 1);
    SetXfKind(pstep, pstep->pxfAngular, 1);
    if (pstep->keyHull != -1) {
        void *pgeom = PpartFindAlo(pstep, pstep->keyHull);
        pstep->pasegDefault = pgeom;
        if (pgeom != 0) {
            CloneStepHullGeom(pstep, pgeom);
            func_001F2AD0(pstep, pstep->pasegDefault);
        }
    }
    GoalStack_AllocGoals((char *)pstep + 0x26C);
}
