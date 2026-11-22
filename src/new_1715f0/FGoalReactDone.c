/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

s32 FGoalReactDone(struct GOALREACT *goal) {
    return goal->state == -1;
}
