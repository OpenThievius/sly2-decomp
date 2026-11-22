// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "rip.h"
struct SLOTHEAP;
extern "C" void FreeSlotheapPv(SLOTHEAP *heap, void *item);
extern SLOTHEAP B_003E1144;
extern SLOTHEAP B_003E14E4;

void ReleaseRip(RIP *rip)
{
    int cref = rip->cref - 1;
    rip->cref = cref;
    if (cref != 0)
        return;
    rip->Release();
    RIPSUB *sub = rip->psub;
    if (sub != 0) {
        do {
            LO *lo = sub->plo;
            lo->HandleMessage(8, rip);
            RIPSUB *next = sub->psubNext;
            FreeSlotheapPv(&B_003E1144, sub);
            sub = next;
        } while (sub != 0);
    }
    rip->psub = 0;
    FreeSlotheapPv(&B_003E14E4, rip);
}
