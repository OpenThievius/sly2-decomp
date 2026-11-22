// SPDX-License-Identifier: GPL-3.0-or-later
#include "job.h"

extern "C" {
s32 FTaskRunning(TASK *);

void SendTaskTimeLimit(TASK *task, s32 timeLimit) {
    s32 limit;
    s32 *args[1];

    limit = timeLimit;
    if (FTaskRunning(task) != 0) {
        args[0] = &limit;
        task->HandleSpliceEvent(0x17, 0, 1, (s32)args, 0);
    }
}
}
