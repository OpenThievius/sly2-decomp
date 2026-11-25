#include "sly2.h"
#include "job.h"
struct CAUSESCOPE {
    JOB *job;
    TASK *task;
    int cause;
    int arg;
    CAUSESCOPE(TASK *target, int newCause, int newArg)
    {
        job = 0;
        task = target;
        if (target) {
            cause = task->cause;
            task->cause = newCause;
            arg = task->causeArg;
            task->causeArg = newArg;
        }
    }
    CAUSESCOPE(JOB *target, int newCause, int newArg)
    {
        job = target;
        task = 0;
        if (target) {
            cause = job->cause;
            job->cause = newCause;
            arg = job->causeArg;
            job->causeArg = newArg;
        }
    }
    ~CAUSESCOPE()
    {
        if (job) {
            job->cause = cause;
            job->causeArg = arg;
        }
        if (task) {
            task->cause = cause;
            task->causeArg = arg;
        }
    }
};
extern "C" int FTaskPrerequisitesDone(TASK *);
extern "C" void SetTaskState(TASK *, int);
extern "C" void SwitchCurrentTask(TASK *);
extern "C" void LeaveTaskIfCurrent(TASK *);
void ForceTaskState(TASK *task, int request, int causeArg)
{
    CAUSESCOPE scopeTask(task, task->cause, causeArg);
    CAUSESCOPE scopeJob(task->job, task->cause, causeArg);
    if (request == -1)
        request = 4;
    if (task->state != -1) {
        switch (request) {
        case 4:
            if (task->state == 0 && FTaskPrerequisitesDone(task))
                SetTaskState(task, 1);
            SwitchCurrentTask(task);
            break;
        case 5:
            LeaveTaskIfCurrent(task);
            break;
        case 0: case 1: case 2: case 3:
            SetTaskState(task, request);
            break;
        }
    }
}
