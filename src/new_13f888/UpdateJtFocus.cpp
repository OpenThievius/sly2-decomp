// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
#include "jt.h"
extern "C" int func_00208E70(STEPGUARD *, JT *, float *);
extern "C" STEPGUARD *B_003E1444;
extern "C" const float RO_FLT_002A4D18;

extern "C" void UpdateJtFocus(JT *pjt)
{
    if (pjt->fFocusBusy != 0) return;
    float sBest = RO_FLT_002A4D18;
    STEPGUARD *pguardBest = 0;
    STEPGUARD *pguardNear = 0;
    int prioBest = -1;
    int prioNear = -1;
    float sNear = sBest;
    for (STEPGUARD *pguard = B_003E1444; pguard != 0; pguard = pguard->pnext) {
        float sa[2];
        int prio = func_00208E70(pguard, pjt, &sa[1]);
        float s = sa[1];
        if (s < sNear) {
            sNear = s;
            prioNear = prio;
            pguardNear = pguard;
        }
        if (prioBest < prio || (prio == prioBest && s < sBest)) {
            sBest = s;
            prioBest = prio;
            pguardBest = pguard;
        }
    }
    pjt->SetFocus(prioNear, pguardNear, prioBest, pguardBest);
}
