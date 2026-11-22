// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
void *memmove(void *, const void *, unsigned int);
void RemoveGuardIgnoredClass(STEPGUARD *guard, int cid)
{
    int index;
    for (index = 0; index < guard->cignoredClass; index++) {
        int *list = guard->aignoredClass;
        if (list[index] == cid) {
            memmove(&list[index], &list[index + 1], (guard->cignoredClass - index) * 4 - 4);
            guard->cignoredClass -= 1;
        }
    }
}
