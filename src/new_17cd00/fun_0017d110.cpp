// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
#include "goalb9.h"
extern "C" {
f32 SMaxCrv(void *);
f32 SMinCrv(void *);
void func_0017D058(GOALB9 *pgoal, int state);

void func_0017D110(GOALB9 *pgoal, s32 fMax) {
    STEPGUARD *pguard;
    void *pcrv;

    pcrv = GOAL_GUARD(pgoal)->ptargetPath;
    if (fMax != 0) {
        pgoal->sCrv = SMaxCrv(pcrv);
    } else {
        pgoal->sCrv = SMinCrv(pcrv);
    }
    pguard = GOAL_GUARD(pgoal);
    pguard->nPath = (pguard->sPath < pgoal->sCrv) ? 1 : 0;
    func_0017D058(pgoal, 0);
}
}
