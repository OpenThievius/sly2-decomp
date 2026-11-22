// SPDX-License-Identifier: GPL-3.0-or-later
#include "goalpost.h"
extern "C" {
void AddGuardSgs(STEPGUARD *, s32);
void func_001EEF68(GOALPOSTWATCH *);

/* GoalPostWatch_Init */
void func_001559B0(GOALPOSTWATCH *pgoal)
{
    func_001EEF68(pgoal);
    AddGuardSgs((STEPGUARD *)pgoal->pstep, 0x23);
    pgoal->state = -1;
    pgoal->tLimit = 3.4028235e38f;
}
}
