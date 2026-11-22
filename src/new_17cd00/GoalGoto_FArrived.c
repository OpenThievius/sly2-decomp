/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"
#include "sly2.h"

s32 GoalFollowCrv_FAtEnd(struct GOAL *pgoalFollow);

s32 GoalGoto_FArrived(struct GOALGOTO *pgoal) {
    s32 state;
    s32 arrived;

    state = pgoal->state;
    arrived = 0;
    if (state == 1) {
        arrived = (GoalFollowCrv_FAtEnd(pgoal->pgoalChild) != 0) ? state : 0;
    }
    return arrived;
}
