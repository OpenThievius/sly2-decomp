// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "types.h"

extern int *B_003DD018;

extern void AddToIdTableB_1ed560(s32 *entry)
{
    s32 index;
    int *slot;
    index = *entry % 16381;
    slot = &B_003DD018[index];
    goto test;
next:
    index = (index + 1) % 16381;
    slot = &B_003DD018[index];
test:
    if (*slot != 0)
        goto next;
    *slot = (int)entry;
}
