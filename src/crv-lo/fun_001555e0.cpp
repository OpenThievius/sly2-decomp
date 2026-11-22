// SPDX-License-Identifier: GPL-3.0-or-later
#include "goalpost.h"
extern "C" {
void func_00155788(GOALPOSTRUN *, s32);
POSTPAIR *func_00155868(GOALPOSTRUN *);
void func_001EEF70(GOALPOSTRUN *);
void func_00208540(STEPGUARD *, LO *);

/* GoalPostRun_Activate */
void func_001555E0(GOALPOSTRUN *pgoal)
{
    STEPGUARDPOSTS *pguard;

    func_001EEF70(pgoal);
    func_00208540((STEPGUARD *)pgoal->pstep, pgoal->ptarget);
    pguard = (STEPGUARDPOSTS *)pgoal->pstep;
    if ((pguard->tickPick - pguard->field_0x33C) >= 0x5A) {
        pgoal->ppost = func_00155868(pgoal);
    }
    if (pgoal->ppost != 0) {
        func_00155788(pgoal, 0);
        return;
    }
    func_00155788(pgoal, 1);
}
}
