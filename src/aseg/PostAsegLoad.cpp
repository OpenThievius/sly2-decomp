// SPDX-License-Identifier: GPL-3.0-or-later
#include "asega.h"
#include "sw.h"

struct UL { unsigned long v; } __attribute__((packed));
extern "C" {
void PostLoLoad();
void QueueSwCallback(SW *, ASEG *, unsigned long, int);
extern SW B_003DD490;
extern const UL RO_002A46C8;
void PostAsegLoad(ASEG *paseg)
{
    PostLoLoad();
    int count = paseg->field_0xB0;
    if (count != 0) {
        QueueSwCallback(&B_003DD490, paseg, RO_002A46C8.v, count);
    }
}
}
