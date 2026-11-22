/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

void GoalFollowCrv_Init(struct GOALFOLLOWCRVVJOY *);

void GoalFollowCrvVjoy_Init(struct GOALFOLLOWCRVVJOY *pgoal) {
    GoalFollowCrv_Init(pgoal);
    pgoal->field_0xD0 = 1.0f;
}
