/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"
#include "sly2.h"

void AddGuardSgs(void *pguard, s32 sgs);
void GoalGoto_Replan(struct GOALGOTO *pgoal);
void GoalGoto_SetState(struct GOALGOTO *pgoal, s32 state);
void func_001EEF70(struct GOALGOTO *pgoal);

void GoalGoto_Activate(struct GOALGOTO *pgoal) {
    if (pgoal->field_0x38 != -1) {
        AddGuardSgs(pgoal->pstep, pgoal->field_0x38);
    }
    func_001EEF70(pgoal);
    GoalGoto_SetState(pgoal, 4);
    GoalGoto_Replan(pgoal);
}
