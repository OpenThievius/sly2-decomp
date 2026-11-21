/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sw.h"

struct JOB;

/* A task: the job that runs it at 0x7C. */
struct TASK {
    u8 unknown_0x0[0x7C];
    /* 0x7C */ struct JOB *pjob; /* EndJob */
};

/* A job: the task it ends at 0x64. */
struct JOB {
    u8 unknown_0x0[0x64];
    /* 0x64 */ TASK *ptask; /* EndJob */
};

extern "C" {
void LeaveTaskIfCurrent(TASK *);
void ResetJob(JOB *);
void SetTaskState(TASK *, int);
void StopJobIfCurrent(JOB *);
void bevy_camera_follow_activity(void *, int, JOB *);
extern int B_002DEB30;
extern SW B_003DD490;
}

extern "C" void EndJob(JOB *pjob)
{
    ResetJob(pjob);
    SetTaskState(pjob->ptask, 1);
    if (B_003DD490.ptaskCurrent != 0 && B_003DD490.ptaskCurrent->pjob == pjob) {
        LeaveTaskIfCurrent(B_003DD490.ptaskCurrent);
    }
    bevy_camera_follow_activity(&B_002DEB30, 0x1F, pjob);
    StopJobIfCurrent(pjob);
}
