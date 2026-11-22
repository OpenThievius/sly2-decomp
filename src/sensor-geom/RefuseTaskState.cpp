// SPDX-License-Identifier: GPL-3.0-or-later
#include "job.h"

/* the camera's follow manager: bevy_camera_follow_activity reads the argument of the event at 0x8 */
struct CAMERAFOLLOW {
    u8 unknown_0x0[0x8];
    /* 0x8 */ s32 arg;
};
extern "C" {
s32 FTaskRunning(TASK *);
s32 FJobRunning(JOB *);
void bevy_camera_follow_activity(CAMERAFOLLOW *, s32, LO *);
extern CAMERAFOLLOW B_002DEB30;
}

void RefuseTaskState(TASK *task, s32 state) {
    s32 local;
    void *args[1];

    local = state;
    args[0] = &local;
    if (FTaskRunning(task)) {
        B_002DEB30.arg = local;
        bevy_camera_follow_activity(&B_002DEB30, 0x27, task);
        task->HandleSpliceEvent(0x12, 0, 1, (s32)args, 0);
    }
    JOB *job = task->job;
    if (job != 0 && FJobRunning(job)) {
        task->job->HandleSpliceEvent(0x12, 0, 1, (s32)args, 0);
    }
}
