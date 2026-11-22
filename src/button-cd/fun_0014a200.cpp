// SPDX-License-Identifier: GPL-3.0-or-later
#include "clock.h"
#include "goalpatrol.h"
extern "C" {
void func_0014AE38(GOALPATROL *, s32);
void func_001EEF70(GOALPATROL *);
void func_0014A200(GOALPATROL *pgoal) {
    func_001EEF70(pgoal);
    func_0014AE38(pgoal, 0);
    pgoal->tActivate = g_2dded0.t;
    GOAL_GUARD(pgoal)->field_0x4A4 = 0;
}
}
