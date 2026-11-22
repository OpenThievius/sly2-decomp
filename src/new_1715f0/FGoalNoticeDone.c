/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

s32 FGoalNoticeDone(struct GOALNOTICE *goal) {
    return goal->state == -1;
}
