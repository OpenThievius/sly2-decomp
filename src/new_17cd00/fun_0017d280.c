/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"
#include "sly2.h"

void Goal_Deactivate(struct GOAL *pgoal);
void RemoveGuardSgs(void *pguard, s32 sgs);

void func_0017D280(struct GOAL *pgoal) {
    Goal_Deactivate(pgoal);
    RemoveGuardSgs(pgoal->pstep, 0x28);
}
