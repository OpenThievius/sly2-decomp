#include "job.h"
void AddJobCompleteEvent(JOB *job, int event)
{
    int count = job->cevComplete;
    if (count < 0x20) {
        job->aevComplete[count] = event;
        job->cevComplete = count + 1;
    }
}
