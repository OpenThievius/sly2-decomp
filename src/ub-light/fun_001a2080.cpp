// SPDX-License-Identifier: GPL-3.0-or-later
#include "jtzap.h"
extern "C" {
void SetJmpState(void *, s32, s32, s32);
void SetJtZapState(JTZAP *, s32);
void WarpZapToSafePoint(JTZAP *);

void func_001A2080(JTZAP *pzap) {
    if (*pzap->phealth > 0) {
        SO *ptarget = pzap->ptarget;
        if (ptarget != 0 && (ptarget->grfso & (1UL << 33))) {
            WarpZapToSafePoint(pzap);
        } else {
            SetJmpState(pzap->pjt->PvJmp(), 0xB, 0, 0);
        }
        return;
    }
    SetJtZapState(pzap, 8);
}
}
