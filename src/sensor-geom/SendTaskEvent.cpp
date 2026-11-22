// SPDX-License-Identifier: GPL-3.0-or-later
#include "job.h"

extern "C" {
s32 FTaskRunning(TASK *);

void SendTaskEvent(TASK *task, s32 first, s32 second) {
    s32 *args[2];
    s32 values[2];

    values[0] = first;
    values[1] = second;
    if (FTaskRunning(task)) {
        args[0] = &values[0];
        args[1] = &values[1];
        task->HandleSpliceEvent(0x11, 0, 2, (s32)args, 0);
    }
}
}
