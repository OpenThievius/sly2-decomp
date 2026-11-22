// SPDX-License-Identifier: GPL-3.0-or-later
#include "job.h"

void SetJobCompleteAseg(JOB *pjob, int arg1, int arg2, int arg3)
{
    pjob->field_0xAC = arg1;
    pjob->field_0xB0 = arg2;
    pjob->field_0xB4 = arg3;
}
