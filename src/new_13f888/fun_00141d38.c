/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jtview.h"

void SetJmpState(void *pvJmp, s32 state, s32 arg2, s32 arg3);
void SpendJtGadgetPower(struct JTVIEW *pjt, s32 gadget);
void StartAttach(void *pvAttach, s32 kind, s32 ptarget, s32 pmember);

void func_00141D38(struct JTVIEW *pjt, s32 gadget) {
    switch (gadget) {
    case 14:
    case 21:
    case 23:
        pjt->field_0x9BC = gadget;
        StartAttach(pjt->attach, 0xB, 0, 0);
        return;
    case 12:
        SpendJtGadgetPower(pjt, 0xC);
        SetJmpState(pjt->jmp, 0x11, 0, 0);
        return;
    }
}
