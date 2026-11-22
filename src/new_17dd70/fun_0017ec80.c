/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

void Goal_Deactivate(struct GOALFOLLOWCURVE *pgoal);
void RemoveGuardSgs(struct STEPGUARD *pguard, s32 sgs);

void func_0017EC80(struct GOALFOLLOWCURVE *pgoal) {
    Goal_Deactivate(pgoal);
    RemoveGuardSgs(pgoal->pstep, 0x2E);
}
