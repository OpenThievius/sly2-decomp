// SPDX-License-Identifier: GPL-3.0-or-later
#include "job.h"

extern "C" {
void InitLo(LO *plo);
void InitSl(SLLIST *psllist, s32 ibLink);

void InitJob(JOB *pjob) {
    InitLo(pjob);
    pjob->field_0x9C = 480.0f;
    pjob->field_0xA0 = 720.0f;
    pjob->field_0x6C = -1;
    pjob->field_0x70 = -1;
    pjob->field_0xAC = -1;
    pjob->field_0xB0 = -1;
    pjob->field_0xB4 = -1;
    InitSl(&pjob->sllist, 0x84);
}

}
