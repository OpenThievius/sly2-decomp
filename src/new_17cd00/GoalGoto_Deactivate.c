/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"
#include "sly2.h"

void GoalGoto_SetState(struct GOALGOTO *pgoal, s32 state);
void Goal_Deactivate(struct GOALGOTO *pgoal);
void RemoveGuardSgs(void *pguard, s32 sgs);

void GoalGoto_Deactivate(struct GOALGOTO *pgoal) {
    Goal_Deactivate(pgoal);
    GoalGoto_SetState(pgoal, -1);
    if (pgoal->field_0x38 != -1) {
        RemoveGuardSgs(pgoal->pstep, pgoal->field_0x38);
    }
}
