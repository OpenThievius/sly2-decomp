/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

void GoalFollowCrv_Init(struct GOALFOLLOWCRVANIM *pgoal); /* extern */
extern f32 g_2be694;

void GoalFollowCrvAnim_Init(struct GOALFOLLOWCRVANIM *pgoal) {
    GoalFollowCrv_Init(pgoal);
    pgoal->tStuck = g_2be694;
    pgoal->field_0xC4 = 1.0f;
    pgoal->kind = 9;
}
