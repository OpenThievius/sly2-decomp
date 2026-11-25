// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
extern "C" {
int FIsBasicDerivedFrom(int, int);
int func_00208B38(STEPGUARD *self, int cls) {
    int index;
    for (index = 0; index < self->cclassFilter; index++) {
        if (FIsBasicDerivedFrom(cls, self->aclassFilter[index]) != 0) return 1;
    }
    return 0;
}
}
