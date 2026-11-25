#include "sly2.h"
#include "job.h"
extern "C" void VisitTaskInOrder_self(TASK *, int *, TASK **, int, int);
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
void VisitTaskInOrder(TASK *task, int *count, TASK **tasks, int depth, int jobDepth)
{
    int visits = task->cVisit + 1;
    int depthMax = task->depthMax;
    if (depthMax <= depth)
        depthMax = depth;
    int jobDepthMax = task->jobDepthMax;
    if (jobDepthMax <= jobDepth)
        jobDepthMax = jobDepth;
    task->depthMax = depthMax;
    task->jobDepthMax = jobDepthMax;
    task->cVisit = visits;
    if (visits < task->cprereq)
        return;
    int index = *count;
    tasks[index] = task;
    *count = index + 1;
    depth++;
    if (task->job != 0 && task->job->ptaskEnd == task)
        jobDepth++;
    for (int dependent = 0; dependent < task->cdep; dependent++) {
        TASK *next = task->adep[dependent];
        CAUSESCOPE scope(next, task->cause, task->causeArg);
        VisitTaskInOrder_self(next, count, tasks, depth, jobDepth);
    }
}
