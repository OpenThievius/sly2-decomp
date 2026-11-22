/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "rip.h"
#include "crefboxes.h"

extern struct SLOTHEAP B_003E1144;

void SubscribeRipObject(struct RIP *rip, struct LO *plo) {
    struct RIPSUB *psub = PvAllocSlotheapImpl(&B_003E1144);
    psub->plo = plo;
    psub->psubNext = rip->psub;
    rip->psub = psub;
}
