/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "bentleyview.h"

s32 FGadgetObjKept(struct GADGETOBJ *pgadget);
void UnlockLeaseOfPlo(void *ppool, void *plo);
void func_0018D698(void *pbentley, struct BENTLEYSLOTVIEW *pslot, void *plo);

void ReleaseBentleyGadget(struct BENTLEYVIEW *pbentley) {
    if (FGadgetObjKept(pbentley->ploGadget) != 0) {
        pbentley->ploGadget->powner = pbentley;
        func_0018D698(pbentley, pbentley->pslotActive, pbentley->ploGadget);
    }
    UnlockLeaseOfPlo(pbentley->pslotActive->ppool, pbentley->ploGadget);
    pbentley->ploGadget = 0;
    pbentley->pslotActive = 0;
}
