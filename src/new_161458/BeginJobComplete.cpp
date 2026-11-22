// SPDX-License-Identifier: GPL-3.0-or-later
#include "job.h"

extern "C" {
void AdvanceAfterJobEnd(JOB *pjob);
void PublishJobEnd(JOB *pjob);
void SetJobEndSequence(JOB *pjob, s32 sequence);

void BeginJobComplete(JOB *pjob) {
    if (pjob->field_0xB8 != 0) {
        SetJobEndSequence(pjob, 1);
        return;
    }
    PublishJobEnd(pjob);
    AdvanceAfterJobEnd(pjob);
}

}
