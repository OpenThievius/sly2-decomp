// SPDX-License-Identifier: GPL-3.0-or-later
#include "job.h"

extern "C" {
void AddTaskAnim(TASK *task, s32 nState, s32 oid, s32 oidSel, s32 oidAnim, s32 fGated, s32 nLevelRow) {
    s32 count;
    ANIMREC *entry;

    if (task->field_0x50 == 0) {
        count = task->canim;
        if (count < 0x20) {
            task->canim = count + 1;
            entry = &task->aanim[count];
            entry->nState = nState;
            entry->oid = oid;
            entry->oidSel = oidSel;
            entry->oidAnim = oidAnim;
            entry->fGated = fGated;
            entry->nLevelRow = nLevelRow;
        }
    }
}
}
