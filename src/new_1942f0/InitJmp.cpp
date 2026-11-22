// SPDX-License-Identifier: GPL-3.0-or-later
#include "jmp.h"
extern "C" {
extern QW D_002BF740;

void InitJmp(JMP *pjmp, JT *pjt) {
    pjmp->pjt = pjt;
    pjmp->kind = -1;
    pjmp->state = -1;
    pjmp->vecF0 = D_002BF740;
    pjmp->field_0x108 = -60.0f;
    pjmp->field_0x10C = -50.0f;
    pjmp->field_0x114 = 50.0f;
    pjmp->field_0x110 = 75.0f;
    pjmp->field_0x11C = 75.0f;
    pjmp->field_0x118 = -150.0f;
    pjmp->field_0x164 = 1.0f;
}

}
