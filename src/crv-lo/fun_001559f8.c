/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goalpost.h"

void Goal_Deactivate(struct GOALPOSTWATCH *pgoal);
void RemoveGuardSgs(struct STEPGUARD *pguard, s32 sgs);
void func_00155AE0(struct GOALPOSTWATCH *pgoal, s32 state);

/* GoalPostWatch_Deactivate */
void func_001559F8(struct GOALPOSTWATCH *pgoal)
{
    Goal_Deactivate(pgoal);
    func_00155AE0(pgoal, -1);
    RemoveGuardSgs(pgoal->pstep, 0x23);
}
