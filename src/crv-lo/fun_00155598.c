/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goalpost.h"

void Goal_Deactivate(struct GOALPOSTRUN *pgoal);
void RemoveGuardSgs(struct STEPGUARD *pguard, s32 sgs);
void func_00155788(struct GOALPOSTRUN *pgoal, s32 state);
void func_00208540(struct STEPGUARD *pguard, struct LO *ptarget);

/* GoalPostRun_Deactivate */
void func_00155598(struct GOALPOSTRUN *pgoal)
{
    Goal_Deactivate(pgoal);
    func_00155788(pgoal, -1);
    RemoveGuardSgs(pgoal->pstep, 0x22);
    func_00208540(pgoal->pstep, 0);
}
