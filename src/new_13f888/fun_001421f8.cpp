/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jt.h"

extern "C" {
void StartAttach(void *pvAttach, int kind, int ptarget, int pmember);
void func_001CD308(void *pvCarry, int ptarget);

void func_001421F8(JT *pjt, int ptarget) {
    if (ptarget != 0) {
        StartAttach(pjt->PvAttach(), 5, ptarget, 0);
        func_001CD308(pjt->PvAttachCarry(), ptarget);
    } else if (pjt->attachKind == 5) {
        pjt->SetMode(0);
    }
}
}
