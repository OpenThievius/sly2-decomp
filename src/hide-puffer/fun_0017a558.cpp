/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goal.h"
#include "stepguard.h"

extern "C" {
void GoalFlinch_SetState(GOAL *, int);
void ReplaceSwHitFx(void *, int, QW, int, HITFX **);
void func_00174B28();
extern int B_003DD490;
extern QW g_2a2dd0;
}

extern "C" void func_0017A558(GOAL *pgoal)
{
    func_00174B28();
    GoalFlinch_SetState(pgoal, -1);
    ReplaceSwHitFx(&B_003DD490, -1, g_2a2dd0, 0, &((STEPGUARD *)pgoal->pstep)->phitfx);
}
