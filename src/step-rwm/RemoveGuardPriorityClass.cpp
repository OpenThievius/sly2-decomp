// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
void *memmove(void *, const void *, unsigned int);
void RemoveGuardPriorityClass(STEPGUARD *guard, int cid)
{
    int index;
    for (index = 0; index < guard->cgroup; index++) {
        int *list = guard->agroup;
        if (list[index] == cid) {
            memmove(&list[index], &list[index + 1], (guard->cgroup - index) * 4 - 4);
            guard->cgroup -= 1;
        }
    }
}
