// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "job.h"
/* the comparator JobMenu_BuildList sorts its array of tasks with: group = jobDepthMax, priority = depthMax (VisitTaskInOrder), owner = the job */
extern "C" s32 func_00165C28(TASK **first, TASK **second) {
    TASK *taskFirst = *first;
    TASK *taskSecond = *second;
    s32 valueFirst = taskFirst->jobDepthMax;
    s32 valueSecond = taskSecond->jobDepthMax;
    if (valueFirst != valueSecond) {
        return valueFirst - valueSecond;
    }
    valueFirst = -1;
    if (taskFirst->job != 0) {
        valueFirst = taskFirst->job->oid;
    }
    valueSecond = -1;
    if (taskSecond->job != 0) {
        valueSecond = taskSecond->job->oid;
    }
    if (valueFirst != valueSecond) {
        return valueFirst - valueSecond;
    }
    valueFirst = taskFirst->depthMax;
    valueSecond = taskSecond->depthMax;
    if (valueFirst != valueSecond) {
        return valueFirst - valueSecond;
    }
    return taskFirst->oid - taskSecond->oid;
}
