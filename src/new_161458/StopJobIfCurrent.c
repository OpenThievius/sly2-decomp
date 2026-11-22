/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct JOB;

s32 FIsCurrentJob(struct JOB *pjob);
void StopJob(struct JOB *pjob);

void StopJobIfCurrent(struct JOB *pjob) {
    if (FIsCurrentJob(pjob) != 0) {
        StopJob(pjob);
    }
}
