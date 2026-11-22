/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "job.h"

void RestartAtTask(struct TASK *ptask);
extern struct TASK *B_003E0FA4;

void bevy_jobs_162df8(struct JOB *pjob) {
    if (B_003E0FA4 != 0) {
        RestartAtTask(B_003E0FA4);
        return;
    }
    RestartAtTask(pjob->ptaskStart);
}
