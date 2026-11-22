// SPDX-License-Identifier: GPL-3.0-or-later
#include "slyview.h"

void SubscribeLoObject(struct LO *plo, struct LO *ploSubscriber);
void UnsubscribeLoObject(struct LO *plo, struct LO *ploSubscriber);

void func_0018D698(struct LO *ploSubscriber, struct GADGETSLOTVIEW *pslot, struct LO *plo) {
    struct LO *ploOld;

    ploOld = pslot->plo;
    if (ploOld != 0) {
        UnsubscribeLoObject(ploOld, ploSubscriber);
        pslot->plo = 0;
    }
    if (plo != 0) {
        pslot->plo = plo;
        SubscribeLoObject(plo, ploSubscriber);
    }
}
