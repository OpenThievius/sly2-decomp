/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

extern f32 g_2dded0;

void GoalFollowCrv_SetState(struct GOALFOLLOWCRV *goal, s32 state) {
    if (state != goal->state) {
        goal->state = state;
        goal->tState = g_2dded0;
    }
}
