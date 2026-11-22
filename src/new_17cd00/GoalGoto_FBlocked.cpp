// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
s32 GoalFollowCrv_FBlocked(GOAL *pgoalFollow);
s32 GoalGoto_FBlocked(GOALGOTO *pgoal)
{
    s32 blocked = 0;
    s32 state = pgoal->state;
    if (state < 3) {
        if (state > 0) {
            return GoalFollowCrv_FBlocked(pgoal->pgoalChild);
        }
        return blocked;
    }
    return blocked;
}
