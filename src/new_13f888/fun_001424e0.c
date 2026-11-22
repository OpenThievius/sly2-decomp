/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jtview.h"

void StartAttach(void *pvAttach, s32 kind, s32 ptarget, s32 pmember);

void func_001424E0(struct JTVIEW *pjt, s32 request, s32 ptarget, s32 sidDefault) {
    s32 field_0x9CC = request;
    if (field_0x9CC == 0) {
        field_0x9CC = pjt->field_0x9C8;
    }
    pjt->field_0x9CC = field_0x9CC;
    StartAttach(pjt->attach, 0xC, ptarget, 0);
    pjt->sidDefault = sidDefault;
}
