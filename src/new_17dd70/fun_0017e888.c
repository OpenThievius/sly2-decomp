/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

void func_001EEF68(struct GOALSNAPTOPOINT *pgoal);
void AddGuardSgs(struct STEPGUARD *pguard, s32 sgs);

void func_0017E888(struct GOALSNAPTOPOINT *pgoal) {
    func_001EEF68(pgoal);
    AddGuardSgs(pgoal->pstep, 0x2D);
}
