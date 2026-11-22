// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
extern "C" {
void AddGuardSgs(STEPGUARD *pguard, int sgs);
void func_001EEF68(GOAL *pgoal);

void func_0017CAC8(GOALB8 *pgoal) {
    func_001EEF68(pgoal);
    pgoal->state = -1;
    pgoal->field_0x38 = 1.0f;
    AddGuardSgs((STEPGUARD *)pgoal->pstep, 0x1B);
}

}
