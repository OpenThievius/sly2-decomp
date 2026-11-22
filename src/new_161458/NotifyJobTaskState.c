/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "job.h"

struct SW;

void ActivateJobOfTask(struct JOB *pjob);
void BeginJobComplete(struct JOB *pjob);
s32 FJobRunning(struct JOB *pjob);
void SetSwRestartTask(struct SW *psw, struct TASK *ptask);
extern struct SW B_003DD490;

void NotifyJobTaskState(struct JOB *pjob, struct TASK *ptask) {
    if (FJobRunning(pjob) != 0) {
        if (ptask == pjob->ptaskStart) {
            ActivateJobOfTask(pjob);
        }
        if (ptask == pjob->ptaskEnd) {
            BeginJobComplete(pjob);
        }
        if (ptask->oidSpawn != -1) {
            SetSwRestartTask(&B_003DD490, ptask);
        }
    }
}
