/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "job.h"

s32 FTaskComplete(struct TASK *ptask);

s32 FEndTaskComplete(struct JOB *pjob) {
    struct TASK *ptask;
    s32 fComplete;

    ptask = pjob->ptaskEnd;
    fComplete = 0;
    if (ptask != 0) {
        fComplete = FTaskComplete(ptask) != 0;
    }
    return fComplete;
}
