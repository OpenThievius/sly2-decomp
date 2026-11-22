/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

void BindAnimref(struct ANIMREF *, struct STEPGUARDVIEW *);
void BindAnimrefArray(struct STEPGUARDVIEW *, struct ANIMREF *);

void BindGuardAnimrefs(struct STEPGUARDVIEW *pguard) {
    s32 ianim;
    struct GUARDANIM *panim;

    ianim = 0;
    if (pguard->canim > 0) {
        panim = pguard->aanim;
        do {
            BindAnimref(&panim->ref, pguard);
            ianim += 1;
            panim += 1;
        } while (ianim < pguard->canim);
    }
    BindAnimrefArray(pguard, pguard->aarefC);
    BindAnimrefArray(pguard, pguard->aarefA);
    BindAnimrefArray(pguard, pguard->aarefB);
}
