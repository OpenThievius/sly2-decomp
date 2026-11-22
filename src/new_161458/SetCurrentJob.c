/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct JOB;

s32 FIsCurrentJob(struct JOB *pjob);
void StartJob(struct JOB *pjob);
void StopJobIfCurrent(struct JOB *pjob);
extern struct JOB *B_003E0F9C;

void SetCurrentJob(struct JOB *pjob) {
    if (FIsCurrentJob(pjob) == 0) {
        if (B_003E0F9C != 0) {
            StopJobIfCurrent(B_003E0F9C);
        }
        StartJob(pjob);
    }
}
