// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
#include "goals.h"
struct CAM;
extern CAM B_002DEB30;
extern "C" int func_001F78A0(int);
extern "C" void GoalHit_Activate(GOALHIT *);
extern "C" void bevy_camera_follow_activity(CAM *, int, STEPGUARD *);
extern "C" void func_00154038(void *, void *, int);
void func_00179780(GOALHIT *goal)
{
    int index = func_001F78A0(goal->args.grfHit);
    ANIMREF *entry = &((STEPGUARD *)goal->pstep)->aarefA[index];
    goal->panimref = entry;
    if (entry->kind == -1)
        goal->panimref = 0;
    GoalHit_Activate(goal);
    bevy_camera_follow_activity(&B_002DEB30, 0x15, ((STEPGUARD *)goal->pstep));
    func_00154038(((STEPGUARD *)goal->pstep)->psensor, (void *)goal->args.arg, 2);
    LO *fx = ((STEPGUARD *)goal->pstep)->field_0xFEC;
    if (fx)
        fx->Add();
}
