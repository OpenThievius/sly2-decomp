// SPDX-License-Identifier: GPL-3.0-or-later
#include "job.h"
#include "cref.h"

extern "C" {
CRef RefGetGameSaveValue(void *, int *);
extern int B_003D4A60;

s32 FTaskComplete(TASK *task) {
    if (task->state == -1) {
        if (task->pathSave[0] != 0) {
            return RefGetGameSaveValue(task->pathSave, &B_003D4A60).m_tag.m_n;
        }
    }
    return task->state >= 2;
}
}
