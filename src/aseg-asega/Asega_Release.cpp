// SPDX-License-Identifier: GPL-3.0-or-later
#include "asega.h"
#include "sw.h"

extern "C" {
void Basic_FreeSubscribers(ASEGA *);
void CFramePtr_Assign(void *, void *);
void FreeSlotheapPv(SLOTHEAP *, void *);
void SidebagPtr_Assign(void *, void *);
extern SLOTHEAP B_003E1224;

void Asega_Release(ASEGA *pasega)
{
    s32 cref = pasega->cref - 1;
    pasega->cref = cref;
    if (cref <= 0) {
        CFramePtr_Assign(pasega, 0);
        SidebagPtr_Assign(&pasega->psidebag, 0);
        Basic_FreeSubscribers(pasega);
        FreeSlotheapPv(&B_003E1224, pasega);
    }
}
}
