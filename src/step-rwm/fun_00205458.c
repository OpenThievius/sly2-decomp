/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

struct GOAL *GoalStack_PgoalFind(struct GOALSTACK *, s32);

struct GOAL *func_00205458(struct STEPGUARDVIEW *pguard, s32 type) {
    return GoalStack_PgoalFind(&pguard->goalstack, type);
}
