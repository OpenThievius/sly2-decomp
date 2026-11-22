/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "job.h"

s32 FIsCurrentTask(struct TASK *task);
void LeaveTask(struct TASK *task);

void LeaveTaskIfCurrent(struct TASK *task) {
    if (FIsCurrentTask(task) != 0) {
        LeaveTask(task);
    }
}
