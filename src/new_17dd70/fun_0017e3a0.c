/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

void func_001EEF68(struct GOALFOLLOWROUTE *pgoal);
void AddGuardSgs(struct STEPGUARD *pguard, s32 sgs);

void func_0017E3A0(struct GOALFOLLOWROUTE *pgoal) {
    func_001EEF68(pgoal);
    pgoal->state = -1;
    AddGuardSgs(pgoal->pstep, 0x2C);
}
