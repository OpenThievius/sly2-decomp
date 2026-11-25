#include "sly2.h"
#include "sw.h"
#include "job.h"
extern "C" SW B_003DD490;
extern "C" int FJobRunning(JOB *);
extern "C" int FSwLoadBusy(SW *);
extern "C" void bevy_jobs_162dd0(JOB *);
extern "C" void bevy_jobs_162e38(JOB *);
extern "C" void bevy_jobs_162df8(JOB *);
void OnJobEvent(JOB *job, int event, int arg)
{
    int eventValue = event;
    int argValue = arg;
    if (FJobRunning(job)) {
        void *args[2];
        args[0] = &eventValue;
        args[1] = &argValue;
        job->HandleSpliceEvent(0x11, 0, 2, (sptr)args, 0);
        for (int index = 0; index < job->cevFail; index++) {
            if (eventValue == job->aevFail[index]) {
                bevy_jobs_162dd0(job);
                break;
            }
        }
        for (int index = 0; index < job->cevComplete; index++) {
            if (eventValue == job->aevComplete[index]) {
                bevy_jobs_162e38(job);
                break;
            }
        }
    } else {
        if (eventValue == 0x10 && job->disabled != 0 && FSwLoadBusy(&B_003DD490) == 0)
            bevy_jobs_162df8(job);
    }
}
