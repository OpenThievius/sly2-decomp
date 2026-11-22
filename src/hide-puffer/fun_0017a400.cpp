// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
extern "C" {
void GoalAnim_Update(GOALANIM *pgoal);
s32 func_00209840(void *, void *);

void func_0017A400(GOALJUMP *pgoal) {
    GoalAnim_Update(pgoal);
    if ((pgoal->fMatrix != 0) && (pgoal->state == 0) && (((JUMPER *)pgoal->panimref->pinst)->state >= 2)) {
        func_00209840(&((STEPGUARD *)pgoal->pstep)->heading, &pgoal->mat);
    }
}

}
