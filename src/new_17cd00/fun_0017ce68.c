/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goalb9.h"
#include "sly2.h"

void AddGuardSgs(void *pguard, s32 sgs);
void func_001EEF68(struct GOALB9 *pgoal);

void func_0017CE68(struct GOALB9 *pgoal) {
    func_001EEF68(pgoal);
    pgoal->state = -1;
    AddGuardSgs(pgoal->pstep, 0x27);
}
