/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

void Goal_Deactivate(struct GOALFOLLOWROUTE *pgoal);
void RemoveGuardSgs(struct STEPGUARD *pguard, s32 sgs);
void func_0017E6B0(struct GOALFOLLOWROUTE *pgoal, s32 newState);
void func_001EF038(struct GOALFOLLOWROUTE *pgoal);

void func_0017E410(struct GOALFOLLOWROUTE *pgoal) {
    Goal_Deactivate(pgoal);
    func_0017E6B0(pgoal, -1);
    func_001EF038(pgoal);
    RemoveGuardSgs(pgoal->pstep, 0x2C);
}
