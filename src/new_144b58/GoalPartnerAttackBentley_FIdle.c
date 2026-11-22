/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jtview.h"

s32 GoalPartnerAttackBentley_FIdle(struct GOALPARTNERATTACK *pgoal) {
    return pgoal->state == -1;
}
