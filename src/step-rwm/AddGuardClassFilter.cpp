// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
void AddGuardClassFilter(STEPGUARD *guard, int value)
{
    unsigned count = guard->cclassFilter;
    if (count < 2) {
        guard->aclassFilter[count] = value;
        guard->cclassFilter = count + 1;
    }
}
