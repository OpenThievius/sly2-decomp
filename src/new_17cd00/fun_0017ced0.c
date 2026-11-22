/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goalb9.h"
#include "sly2.h"

void Goal_Deactivate(struct GOALB9 *pgoal);
void RemoveGuardSgs(void *pguard, s32 sgs);
void func_0017D058(struct GOALB9 *pgoal, s32 state);

void func_0017CED0(struct GOALB9 *pgoal) {
    Goal_Deactivate(pgoal);
    func_0017D058(pgoal, -1);
    RemoveGuardSgs(pgoal->pstep, 0x27);
}
