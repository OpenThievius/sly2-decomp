// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
struct SW;
#include "job.h"
extern SW B_003DD490;
// The camera-follow object (EnterTask passes it to bevy_camera_follow_activity); the three ids at 0x10 are the ones SetSwCurrentJob,
// SetSwCurrentTask and SetSwRestartTask store (retail reaches them from B_002DEB30, not from three symbols).
struct CAMERAFOLLOW {
    u8 unknown_0x0[0x10];
    /* 0x10 */ s32 oidJob;
    /* 0x14 */ s32 oidTask;
    /* 0x18 */ s32 oidRestart;
};
extern CAMERAFOLLOW B_002DEB30;
extern "C" TASK *PloFindSwObject_thunk(SW *, int, int, int);
extern "C" void SetSwRestartTask(SW *, TASK *);
extern "C" void RestartAtTask(TASK *);
extern "C" void RequestTransition(SW *, void *, int, int, int, int);
void RestartAtTaskOid(void *unused, void *desc, int oid)
{
    TASK *task = PloFindSwObject_thunk(&B_003DD490, 0x105, oid, 0);
    if (task) {
        SetSwRestartTask(&B_003DD490, task);
        RestartAtTask(task);
    } else {
        B_002DEB30.oidJob = -1;
        B_002DEB30.oidTask = -1;
        B_002DEB30.oidRestart = oid;
        RequestTransition(&B_003DD490, desc, 0x189, -1, 8, -1);
    }
}
