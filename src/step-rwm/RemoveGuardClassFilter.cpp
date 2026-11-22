// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
void *memmove(void *, const void *, unsigned int);
void RemoveGuardClassFilter(STEPGUARD *guard, int cid)
{
    int index;
    for (index = 0; index < guard->cclassFilter; index++) {
        int *list = guard->aclassFilter;
        if (list[index] == cid) {
            memmove(&list[index], &list[index + 1], (guard->cclassFilter - index) * 4 - 4);
            guard->cclassFilter -= 1;
        }
    }
}
