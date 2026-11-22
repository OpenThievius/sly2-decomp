/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"
#include "sly2.h"

void Goal_Deactivate(struct GOAL *pgoal);
void func_0017B750(struct GOAL *pgoal, s32 state);

void func_0017B5F0(struct GOAL *pgoal) {
    Goal_Deactivate(pgoal);
    func_0017B750(pgoal, -1);
}
