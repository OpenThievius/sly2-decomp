/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jt.h"

void ReleaseJtLookHold(JT *pjt);

void SetJtLookTarget(JT *pjt, int kind, LO *plo) {
    if ((plo != pjt->ploLook) || (kind != pjt->kindLook)) {
        pjt->kindLook = kind;
        pjt->ploLook = plo;
        if (plo != 0) {
            if (pjt->tGlance != 3.4028235e38f) {
                pjt->fGlance = 1;
                ReleaseJtLookHold(pjt);
            }
        }
    }
}
