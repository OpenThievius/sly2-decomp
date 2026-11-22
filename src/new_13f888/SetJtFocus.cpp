/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jt.h"

extern "C" {
void func_001431D0(JT *pjt);

/* JT slot 95 (SetFocus) */
void SetJtFocus(JT *pjt, int prioNear, STEPGUARD *pguardNear, int prioBest, STEPGUARD *pguardBest) {
    if ((sptr)pguardNear != pjt->field_0x10DC) {
        func_001431D0(pjt);
    }
    pjt->field_0x10DC = (sptr)pguardNear;
    pjt->focusKind = prioNear;
    pjt->pguardBest = pguardBest;
    pjt->focusMode = prioBest;
}
}
