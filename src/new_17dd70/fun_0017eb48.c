/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

void func_001EEF68(struct GOALFOLLOWCURVE *pgoal);
void AddGuardSgs(struct STEPGUARD *pguard, s32 sgs);

void func_0017EB48(struct GOALFOLLOWCURVE *pgoal) {
    func_001EEF68(pgoal);
    pgoal->s = -1.0f;
    AddGuardSgs(pgoal->pstep, 0x2E);
}
