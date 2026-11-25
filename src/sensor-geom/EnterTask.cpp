// SPDX-License-Identifier: GPL-3.0-or-later
#include "job.h"
#include "sw.h"

struct SW;
struct CAMERAFOLLOW;
struct HUD;
extern "C" {
extern SW B_003DD490;
extern CAMERAFOLLOW B_002DEB30;
extern HUD B_003DA0C0;
void SetSwCurrentTask(SW *, TASK *);
void SetSwRestartTask(SW *, TASK *);
s32 FIsCurrentJob(JOB *);
void ActivateJobOfTask(JOB *);
s32 FTaskRunning(TASK *);
void SaveTaskVariables(TASK *);
void bevy_camera_follow_activity(CAMERAFOLLOW *, s32, LO *);
void ApplyTaskToggles(TASK *, s32, s32, void *);
void ApplyTaskAnims(TASK *, s32, s32, ANIMREC *, s32);
void ShowHudLabel(f32, HUD *, s32);
void Warp_Start(LO *);
}

void EnterTask(TASK *task) {
    SetSwCurrentTask(&B_003DD490, task);
    if (task->oidSpawn != -1)
        SetSwRestartTask(&B_003DD490, task);
    if (task->job != 0 && !FIsCurrentJob(task->job))
        ActivateJobOfTask(task->job);
    if (!FTaskRunning(task))
        return;
    task->cEnter = task->cEnter + 1;
    SaveTaskVariables(task);
    bevy_camera_follow_activity(&B_002DEB30, 0x23, task);
    ApplyTaskToggles(task, 4, task->ctoggle, task->atoggle);
    ApplyTaskAnims(task, 4, task->canim, task->aanim, task->cause);
    if (task->labelId != -1 && task->labelFlag != 0)
        ShowHudLabel(-1.0f, &B_003DA0C0, task->labelId);
    task->HandleSpliceEvent(0x13, 0, 0, 0, 0);
    if (task->plo != 0) {
        if (!(task->plo->grfSw & 1))
            task->plo->pgrfentry->grf |= 0x100;
        else
            task->plo->grfSw |= 0x100;
        Warp_Start(task->plo);
    }
}
