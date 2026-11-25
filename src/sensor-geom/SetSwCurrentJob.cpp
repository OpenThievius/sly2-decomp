#include "job.h"
#include "sw.h"
extern "C" int B_002DEB40;
extern "C" void SetSwCurrentJob(SW *psw, JOB *pjob)
{
    psw->pjobCurrent = pjob;
    if (pjob)
        B_002DEB40 = pjob->oid;
    else
        B_002DEB40 = -1;
}
