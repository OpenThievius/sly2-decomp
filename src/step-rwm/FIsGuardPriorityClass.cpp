// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
extern "C" {
int FIsBasicDerivedFrom(int, int);
int FIsGuardPriorityClass(STEPGUARD *self, int cls) {
    int index;
    for (index = 0; index < self->cgroup; index++) {
        if (FIsBasicDerivedFrom(cls, self->agroup[index]) != 0) return 1;
    }
    return 0;
}
}
