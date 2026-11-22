// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "sly2.h"
extern "C" {
void GoalHit_Activate(GOALHIT *pgoal);
void bevy_camera_follow_activity(void *mgr, int event, STEPGUARD *arg);
void func_00154038(s32 psensor, s32 field_0x50, s32 sensorState);
s32 func_001F78A0(u32 mask);
extern char B_002DEB30[];

void func_001796D0(GOALHIT *pgoal) {
    ANIMREF *panimref;

    panimref = ((STEPGUARD *)pgoal->pstep)->aarefB + func_001F78A0(pgoal->args.grfHit);
    pgoal->panimref = panimref;
    if (panimref->kind == -1) {
        pgoal->panimref = 0;
    }
    GoalHit_Activate(pgoal);
    bevy_camera_follow_activity(B_002DEB30, 0x15, (STEPGUARD *)pgoal->pstep);
    func_00154038((s32)((STEPGUARD *)pgoal->pstep)->psensor, pgoal->args.arg, 2);
}

}
