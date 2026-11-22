/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jtview.h"

void AdjustStepXps(struct JTVIEW *pjt);
void func_00199298(void *pvJmp);

void func_00140D70(struct JTVIEW *pjt) {
    AdjustStepXps(pjt);
    if (pjt->jmpState != -1) {
        func_00199298(pjt->jmp);
    }
}
