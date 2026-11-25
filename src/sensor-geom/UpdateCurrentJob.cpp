// SPDX-License-Identifier: GPL-3.0-or-later
#include "job.h"
#include "sw.h"
extern "C" {
extern SW B_003DD490;
int CploFindSwObjectsByClass(SW *, int, int, int, int, JOB **);
int FTaskComplete(TASK *);
void StopJobIfCurrent(JOB *);
void SetCurrentJob(JOB *);
void UpdateCurrentJob()
{
    JOB *apjob[256];
    JOB *newJob = 0;
    int count = CploFindSwObjectsByClass(&B_003DD490, 5, 0x84, 0, 0x100, apjob);
    for (int index = 0; index < count; index++) {
        JOB *job = apjob[index];
        if (FTaskComplete(job->ptaskStart) && !FTaskComplete(job->ptaskEnd))
            newJob = job;
    }
    if (newJob != B_003DD490.pjobCurrent) {
        if (B_003DD490.pjobCurrent != 0)
            StopJobIfCurrent(B_003DD490.pjobCurrent);
        if (newJob != 0)
            SetCurrentJob(newJob);
    }
}
}
