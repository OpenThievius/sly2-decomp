// SPDX-License-Identifier: GPL-3.0-or-later
#include "job.h"

struct SW;
extern "C" {
s32 FSwLoadBusy(SW *);
extern SW B_003DD490;

s32 FTaskRunning(TASK *task) {
    s32 state;

    if (task->field_0x50 != 0) {
        return 0;
    }
    state = task->cause;
    if (state == 2) {
        return 0;
    }
    if (state == 3) {
        return 0;
    }
    return FSwLoadBusy(&B_003DD490) == 0;
}
}
