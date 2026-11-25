#include "sly2.h"
#include "job.h"
#include "sw.h"
struct JOBSCOPE { JOB *job; TASK *task; int savedCause; int savedArg; };
extern SW B_003DD490;
extern "C" int FIsCurrentTask(TASK *);
extern "C" void LeaveTaskIfCurrent(TASK *);
extern "C" void EnterTask(TASK *);
void SwitchCurrentTask(TASK *task)
{
    if (FIsCurrentTask(task))
        return;
    TASK *old = B_003DD490.ptaskCurrent;
    if (old != 0) {
        JOBSCOPE scope;
        scope.job = 0;
        scope.task = old;
        int c = task->cause;
        int a = task->causeArg;
        scope.savedCause = old->cause;
        old->cause = c;
        scope.savedArg = scope.task->causeArg;
        scope.task->causeArg = a;
        LeaveTaskIfCurrent(B_003DD490.ptaskCurrent);
        if (scope.job != 0) {
            scope.job->cause = scope.savedCause;
            scope.job->causeArg = scope.savedArg;
        }
        if (scope.task != 0) {
            scope.task->cause = scope.savedCause;
            scope.task->causeArg = scope.savedArg;
        }
    }
    EnterTask(task);
}
