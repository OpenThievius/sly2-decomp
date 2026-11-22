// SPDX-License-Identifier: GPL-3.0-or-later
#include "job.h"

struct CAMERAFOLLOW;
struct AUTOSAVE;

extern "C" {
void SetTaskState(TASK *ptask, s32 state);
void StopJobIfCurrent(JOB *pjob);
void TryAutosave(AUTOSAVE *pautosave, s32 arg1);
void bevy_camera_follow_activity(CAMERAFOLLOW *pmanager, s32 event, JOB *pjob);
extern CAMERAFOLLOW B_002DEB30;
extern AUTOSAVE B_002E65E0;

void PublishJobEnd(JOB *pjob) {
    if (pjob->field_0x78 == 0) {
        SetTaskState(pjob->ptaskEnd, 3);
    }
    bevy_camera_follow_activity(&B_002DEB30, 0x20, pjob);
    StopJobIfCurrent(pjob);
    if (pjob->field_0x78 == 0) {
        TryAutosave(&B_002E65E0, 0);
    }
}

}
