// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
extern "C" void func_001EEF68(GOAL *);
extern "C" void AddGuardSgs(STEPGUARD *, int);
void func_0017BED0(GOALB3 *pgoal)
{
    func_001EEF68(pgoal);
    AddGuardSgs((STEPGUARD *)pgoal->pstep, 0x19);
    pgoal->state = -1;
}
