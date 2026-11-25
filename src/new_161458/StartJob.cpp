#include "sly2.h"
#include "sw.h"
#include "job.h"
extern "C" SW B_003DD490;
extern char B_002DEB30[];
extern "C" void SetSwCurrentJob(SW *, JOB *);
extern "C" int FJobRunning(JOB *);
extern "C" void SaveJobVariables(JOB *);
extern "C" void bevy_camera_follow_activity(void *, int, JOB *);
extern "C" void ApplyTaskToggles(JOB *, int, int, void *);
extern "C" void ApplyTaskAnims(JOB *, int, int, void *, int);
void StartJob(JOB *job)
{
    SetSwCurrentJob(&B_003DD490, job);
    if (FJobRunning(job)) {
        job->count = job->count + 1;
        SaveJobVariables(job);
        bevy_camera_follow_activity(B_002DEB30, 0x21, job);
        ApplyTaskToggles(job, 4, job->ctoggle, job->atoggle);
        ApplyTaskAnims(job, 4, job->canim, job->aanim, job->cause);
        job->HandleSpliceEvent(0x13, 0, 0, 0, 0);
    }
}
