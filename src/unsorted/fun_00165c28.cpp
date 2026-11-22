// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
/* a task of the job menu (JobMenu_BuildList sorts an array of them with this comparator) */
struct TASKINFO {
    u8 unknown_0x0[0x18];
    s32 oid;
    u8 unknown_0x1C[0x60];
    TASKINFO *owner;
    u8 unknown_0x80[0x80];
    s32 priority;
    s32 group;
};
extern "C" s32 func_00165C28(TASKINFO **first, TASKINFO **second) {
    TASKINFO *taskFirst = *first;
    TASKINFO *taskSecond = *second;
    s32 valueFirst = taskFirst->group;
    s32 valueSecond = taskSecond->group;
    if (valueFirst != valueSecond) {
        return valueFirst - valueSecond;
    }
    valueFirst = -1;
    if (taskFirst->owner != 0) {
        valueFirst = taskFirst->owner->oid;
    }
    valueSecond = -1;
    if (taskSecond->owner != 0) {
        valueSecond = taskSecond->owner->oid;
    }
    if (valueFirst != valueSecond) {
        return valueFirst - valueSecond;
    }
    valueFirst = taskFirst->priority;
    valueSecond = taskSecond->priority;
    if (valueFirst != valueSecond) {
        return valueFirst - valueSecond;
    }
    return taskFirst->oid - taskSecond->oid;
}
