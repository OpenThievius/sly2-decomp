/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

void CloneAnimref(struct ANIMREF *);
void CloneAnimrefArray(struct STEPGUARDVIEW *, struct ANIMREF *);

void CloneGuardAnimrefs(struct STEPGUARDVIEW *pguard) {
    s32 ianim;
    struct GUARDANIM *panim;

    ianim = 0;
    if (pguard->canim > 0) {
        panim = pguard->aanim;
        do {
            ianim += 1;
            CloneAnimref(&panim->ref);
            panim += 1;
        } while (ianim < pguard->canim);
    }
    CloneAnimrefArray(pguard, pguard->aarefC);
    CloneAnimrefArray(pguard, pguard->aarefA);
    CloneAnimrefArray(pguard, pguard->aarefB);
}
