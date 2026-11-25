// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
void AddGuardPriorityClass(STEPGUARD *guard, int value)
{
    unsigned count = guard->cgroup;
    if (count < 3) {
        int *slot = &guard->agroup[count];
        guard->cgroup = count + 1;
        *slot = value;
    }
}
