// SPDX-License-Identifier: GPL-3.0-or-later
#include "job.h"

struct SW;
struct CAMERAFOLLOW;
struct HUD;
extern "C" {
extern SW B_003DD490;
extern CAMERAFOLLOW B_002DEB30;
extern HUD B_003DA0C0;
void SetSwCurrentTask(SW *, TASK *);
s32 FTaskRunning(TASK *);
void bevy_camera_follow_activity(CAMERAFOLLOW *, s32, LO *);
void ApplyTaskToggles(TASK *, s32, s32, void *);
void ApplyTaskAnims(TASK *, s32, s32, ANIMREC *, s32);
void ClearHudLabel(HUD *, s32);

void LeaveTask(TASK *task) {
    SetSwCurrentTask(&B_003DD490, 0);
    if (FTaskRunning(task)) {
        bevy_camera_follow_activity(&B_002DEB30, 0x24, task);
        ApplyTaskToggles(task, 5, task->ctoggle, task->atoggle);
        ApplyTaskAnims(task, 5, task->canim, task->aanim, task->field_0xF4);
        if (task->labelId != -1 && task->labelFlag != 0)
            ClearHudLabel(&B_003DA0C0, task->labelId);
        task->HandleSpliceEvent(0x14, 0, 0, 0, 0);
    }
}
}
