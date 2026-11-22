// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
extern "C" {
void ClearGuardPathMode(STEPGUARD *pguard);
void GoalAnimLeap_SetState(GOALGRAB *pgoal, int state);
void func_00154038(s32 psensor, s32 flags, s32 sensorState);
void func_00174950(GOAL *pgoal);
void func_001EEFC0(GOAL *pgoal);
void func_0020AB68(STEPGUARD *pguard, void *panim, int mode, QW vec);
extern QW g_2a2dd0;

void GoalGrab_Activate(GOALGRAB *pgoal) {
    func_00174950(pgoal);
    func_0020AB68((STEPGUARD *)pgoal->pstep, 0, 0, g_2a2dd0);
    ClearGuardPathMode((STEPGUARD *)pgoal->pstep);
    GoalAnimLeap_SetState(pgoal, 0);
    func_001EEFC0(pgoal);
    func_00154038((s32)((STEPGUARD *)pgoal->pstep)->psensor, (s32)pgoal->psoHeld, 2);
}

}
