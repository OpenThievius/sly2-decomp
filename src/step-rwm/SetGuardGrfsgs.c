/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

void func_001F1900(struct STEPGUARDVIEW *);

void SetGuardGrfsgs(struct STEPGUARDVIEW *pguard, u64 grfsgs) {
    pguard->grfsgs = grfsgs;
    func_001F1900(pguard);
}
