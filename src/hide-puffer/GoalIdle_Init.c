/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"
#include "sly2.h"

void AddGuardSgs(void *pguard, s32 sgs);
void func_001EEF68(struct GOAL *pgoal);

void GoalIdle_Init(struct GOALIDLE *pgoal) {
    func_001EEF68((struct GOAL *)pgoal);
    pgoal->state = -1;
    pgoal->tWaitLimit = 3.4028235e38f;
    pgoal->tScriptLimit = 3.4028235e38f;
    AddGuardSgs(pgoal->pstep, 0x1E);
}
