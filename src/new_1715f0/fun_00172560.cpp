// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
extern "C" {
f32 GRandInRange(f32, f32);
extern f32 RO_002BE5A0;
extern f32 g_2dded0;

void func_00172560(GOALSEARCH *goal) {
    f32 now = g_2dded0;
    STEPGUARD *pguard = GOAL_GUARD(goal);
    goal->field_0x38 = now + GRandInRange(pguard->field_0xE6C, pguard->field_0xE70);
    if (GOAL_GUARD(goal)->field_0xE78 == 1) {
        goal->field_0x3C = g_2dded0 + RO_002BE5A0;
    } else {
        goal->field_0x3C = 3.4028235e38f;
    }
}
}
