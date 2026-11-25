#include "job.h"
void AddJobFailEvent(JOB *job, int event)
{
    int count = job->cevFail;
    if (count < 0x20) {
        job->aevFail[count] = event;
        job->cevFail = count + 1;
    }
}
