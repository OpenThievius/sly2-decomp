/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "blipview.h"

s32 FIsBasicDerivedFrom(void *pbasic, s32 cid);
void SubscribeLoObject(void *plo, void *plo2);

void SubscribeBlipgObject__FP5BLIPGP2LO(struct BLIPGVIEW *pblipg, struct LOVIEW *plo) {
    SubscribeLoObject(pblipg, plo);
    if (FIsBasicDerivedFrom(plo, 0x1D) != 0) {
        pblipg->ploSource = plo;
        pblipg->field_0x38 = plo->field_0x38;
    }
}
