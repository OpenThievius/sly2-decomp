#include "job.h"
extern "C" void CollectTaskPrerequisites(TASK *ptask, int nState, int *pctask, TASK **aptask) __attribute__((weak));
extern "C" void CollectTaskPrerequisites(TASK *ptask, int nState, int *pctask, TASK **aptask)
{
    for (int i = 0; i < ptask->cprereq; i++) {
        TASK *prereq = ptask->aprereq[i];
        int nStatePrereq = nState;
        if (nState == 2) {
            JOB *job = prereq->job;
            if (job == 0) goto three;
            if (job != ptask->job) {
                if (job->field_0x78 == 0) {
                three:
                    nStatePrereq = 3;
                }
            }
        }
        CollectTaskPrerequisites(prereq, nStatePrereq, pctask, aptask);
    }
    if (ptask->pending == -1 && ptask->state < nState) {
        int n = *pctask;
        aptask[n] = ptask;
        *pctask = n + 1;
        ptask->pending = nState;
    }
}
