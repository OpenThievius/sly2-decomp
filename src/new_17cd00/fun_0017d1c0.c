/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"
#include "sly2.h"

void AddGuardSgs(void *pguard, s32 sgs);
void func_001EEF68(struct GOAL *pgoal);

void func_0017D1C0(struct GOAL *pgoal) {
    func_001EEF68(pgoal);
    AddGuardSgs(pgoal->pstep, 0x28);
}
