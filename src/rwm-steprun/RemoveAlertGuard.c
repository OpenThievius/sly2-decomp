// SPDX-License-Identifier: GPL-3.0-or-later
#include "guard.h"

void CopyAb__FPvT0Ui(void *pvDest, void *pvSource, u32 cb);
s32 IndexOfAlertGuard(void);

void RemoveAlertGuard(struct ALERT *palert) {
    s32 index;
    s32 cguardNew;
    s32 cMoved;
    struct STEPGUARD **ppguard;

    index = IndexOfAlertGuard();
    cguardNew = palert->cguard - 1;
    ppguard = &palert->apguard[index];
    cMoved = cguardNew - index;
    palert->cguard = cguardNew;
    CopyAb__FPvT0Ui(ppguard, ppguard + 1, cMoved * 4);
}
