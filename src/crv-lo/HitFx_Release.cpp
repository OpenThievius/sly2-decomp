// SPDX-License-Identifier: GPL-3.0-or-later
#include "hitfx.h"
#include "sw.h"
extern "C" {
void Basic_FreeSubscribers(BASIC *);
void CFramePtr_Assign(void *, int);
void FreeSlotheapPv(SLOTHEAP *, void *);
void SidebagPtr_Assign(CSidebag **, int);
extern SLOTHEAP B_003E1498;

void HitFx_Release(HITFX *pfx)
{
    s32 cRef;

    cRef = pfx->cRef - 1;
    pfx->cRef = cRef;
    if (cRef <= 0) {
        CFramePtr_Assign(pfx, 0);
        SidebagPtr_Assign(&pfx->psidebag, 0);
        Basic_FreeSubscribers(pfx);
        FreeSlotheapPv(&B_003E1498, pfx);
    }
}
}
