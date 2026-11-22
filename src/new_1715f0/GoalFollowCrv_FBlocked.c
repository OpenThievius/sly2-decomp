/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

s32 GoalFollowCrv_FBlocked(struct GOALFOLLOWCRV *goal) {
    return goal->state == 3;
}
