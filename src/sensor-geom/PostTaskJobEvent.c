/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "job.h"

struct CAMERAFOLLOW;
void bevy_camera_follow_activity(struct CAMERAFOLLOW *pmanager, s32 event, struct JOB *pjob);
extern struct CAMERAFOLLOW B_002DEB30;

void PostTaskJobEvent(struct TASK *task) {
    bevy_camera_follow_activity(&B_002DEB30, 0x1E, task->job);
}
