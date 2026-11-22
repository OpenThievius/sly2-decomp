/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

void func_0017E6B0(struct GOALFOLLOWROUTE *pgoal, s32 newState);
void func_001EF038(struct GOALFOLLOWROUTE *pgoal);

void func_0017E580(struct GOALFOLLOWROUTE *pgoal) {
    pgoal->index = pgoal->index + 1;
    if (pgoal->index < pgoal->proute->cwaypoint) {
        func_0017E6B0(pgoal, -1);
        func_0017E6B0(pgoal, 0);
        return;
    }
    func_0017E6B0(pgoal, -1);
    func_001EF038(pgoal);
}
