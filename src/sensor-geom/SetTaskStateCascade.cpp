// SPDX-License-Identifier: GPL-3.0-or-later
#include "job.h"
struct CAUSESAVE { JOB *job; TASK *task; int savedCause; int savedArg; };
extern "C" void ApplyTaskState(TASK *, int);
extern "C" void UpdateDependentTaskState(TASK *, int);
extern "C" void SetTaskStateCascade(TASK *task, int state)
{
    if (task->state == state)
        return;
    ApplyTaskState(task, state);
    for (int index = 0; index < task->cdep; index++) {
        TASK *dep = task->adep[index];
        CAUSESAVE scope;
        scope.job = 0;
        scope.task = dep;
        int c = task->cause;
        int a = task->causeArg;
        if (dep != 0) {
            scope.savedCause = dep->cause;
            dep->cause = c;
            scope.savedArg = scope.task->causeArg;
            scope.task->causeArg = a;
        }
        UpdateDependentTaskState(dep, task->state);
        if (scope.job != 0) {
            scope.job->cause = scope.savedCause;
            scope.job->causeArg = scope.savedArg;
        }
        if (scope.task != 0) {
            scope.task->cause = scope.savedCause;
            scope.task->causeArg = scope.savedArg;
        }
    }
}
