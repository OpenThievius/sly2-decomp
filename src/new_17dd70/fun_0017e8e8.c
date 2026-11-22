/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

void Goal_Deactivate(struct GOALSNAPTOPOINT *pgoal);
void RemoveGuardSgs(struct STEPGUARD *pguard, s32 sgs);

void func_0017E8E8(struct GOALSNAPTOPOINT *pgoal) {
    Goal_Deactivate(pgoal);
    RemoveGuardSgs(pgoal->pstep, 0x2D);
}
