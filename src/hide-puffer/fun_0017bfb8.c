/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"
#include "sly2.h"

void Goal_Deactivate(struct GOAL *pgoal);
void RemoveGuardSgs(void *pguard, s32 sgs);
void func_0017C550(struct GOAL *pgoal, s32 state);

void func_0017BFB8(struct GOAL *pgoal) {
    Goal_Deactivate(pgoal);
    func_0017C550(pgoal, -1);
    RemoveGuardSgs(pgoal->pstep, 0x19);
}
