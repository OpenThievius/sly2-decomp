/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

struct GOAL *GoalStack_Push(struct GOALSTACK *, s32);

struct GOAL *func_00205438(struct STEPGUARDVIEW *pguard, s32 type) {
    return GoalStack_Push(&pguard->goalstack, type);
}
