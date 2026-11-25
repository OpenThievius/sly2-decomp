#include "types.h"
// SPDX-License-Identifier: GPL-3.0-or-later
#include "stgswitch.h"
struct UL { u64 v; } __attribute__((packed));
extern const UL RO_002A7630;
extern char B_003DD490[];
void QueueSwCallbackOnce(void *, void *, u64, int);

void SetStgSwitchHitter(STGSWITCH *pstgswitch, LO *plo, int kind)
{
    pstgswitch->kind = kind;
    pstgswitch->ploHit = plo;
    QueueSwCallbackOnce(B_003DD490, pstgswitch, RO_002A7630.v, 0);
}
