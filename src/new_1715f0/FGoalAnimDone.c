/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

s32 FGoalAnimDone(struct GOALANIM *goal) {
    return goal->state == 1;
}
