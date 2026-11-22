/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "goals.h"

void func_001EEF70(struct GOALFLEE *pgoal);
void func_0017E278(struct GOALFLEE *pgoal, s32 newState);
void func_00208540(struct STEPGUARD *pguard, struct LO *ptarget);

void func_0017DDA8(struct GOALFLEE *pgoal) {
    func_001EEF70(pgoal);
    func_0017E278(pgoal, 0);
    func_00208540(pgoal->pstep, pgoal->ptarget);
}
