/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct JOB;
struct CAMERAFOLLOW;

void bevy_camera_follow_activity(struct CAMERAFOLLOW *pmanager, s32 event, struct JOB *pjob);
extern struct CAMERAFOLLOW B_002DEB30;

void bevy_jobs_162dd0(struct JOB *pjob) {
    bevy_camera_follow_activity(&B_002DEB30, 0x1D, pjob);
}
