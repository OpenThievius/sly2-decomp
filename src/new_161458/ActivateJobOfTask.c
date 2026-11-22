/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct BASIC;
struct CAMERAFOLLOW;
struct JOB;
struct JT;
struct PO;
struct SW;

void DropJtLoot(struct JT *pjt);
s32 FIsBasicDerivedFrom(struct BASIC *pbasic, s32 index);
s32 FIsCurrentJob(struct JOB *pjob);
struct PO *PpoSwFocusBase(struct SW *psw);
void SetCurrentJob(struct JOB *pjob);
void bevy_camera_follow_activity(struct CAMERAFOLLOW *pmanager, s32 event, struct JOB *pjob);
extern struct CAMERAFOLLOW B_002DEB30;
extern struct SW B_003DD490;

void ActivateJobOfTask(struct JOB *pjob) {
    struct PO *ppoFocus;

    if (FIsCurrentJob(pjob) == 0) {
        bevy_camera_follow_activity(&B_002DEB30, 0x1C, pjob);
        ppoFocus = PpoSwFocusBase(&B_003DD490);
        if ((ppoFocus != 0) && (FIsBasicDerivedFrom((struct BASIC *)ppoFocus, 0x34) != 0)) {
            DropJtLoot((struct JT *)ppoFocus);
        }
        SetCurrentJob(pjob);
    }
}
