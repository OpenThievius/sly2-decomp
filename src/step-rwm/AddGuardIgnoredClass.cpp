// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
void AddGuardIgnoredClass(STEPGUARD *guard, int value)
{
    unsigned count = guard->cignoredClass;
    if (count < 5) {
        guard->aignoredClass[count] = value;
        guard->cignoredClass = count + 1;
    }
}
