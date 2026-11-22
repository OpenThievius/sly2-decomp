// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "stepguard.h"
#include "goals.h"
extern "C" {
void Goal_Deactivate(GOALFLEE *);
void RemoveGuardSgs(STEPGUARD *, int);
void ResetSensorStates(struct SENSOR *);
void func_0017E278(GOALFLEE *, int);
void func_00208540(STEP *, int);

void func_0017DDE8(GOALFLEE *pgoal) {
    Goal_Deactivate(pgoal);
    func_0017E278(pgoal, -1);
    ResetSensorStates(((STEPGUARD *)pgoal->pstep)->psensor);
    func_00208540(pgoal->pstep, 0);
    RemoveGuardSgs((STEPGUARD *)pgoal->pstep, 0x2B);
}

}
