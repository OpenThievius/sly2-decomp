// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
extern "C" void func_001EEF68(GOALFLEE *);
extern "C" void AddGuardSgs(STEPGUARD *, int);
void func_0017DD70(GOALFLEE *pgoal)
{
    func_001EEF68(pgoal);
    AddGuardSgs((STEPGUARD *)pgoal->pstep, 0x2B);
    pgoal->state = -1;
}
