// SPDX-License-Identifier: GPL-3.0-or-later
#include "attach.h"
extern "C" {
void Carry_Init(u8 *pcarry);                         /* extern */
void func_0020B840(u8 *prun, SLY *pjt, s32 mode);    /* extern */
void InitAttach(ATTACH *pattach, SLY *pjt) {
    pattach->pjt = pjt;
    pattach->kind = -1;
    pattach->field_0x0C = -1;
    pattach->field_0x4FC = -1;
    func_0020B840(pattach->runA, pjt, 0x6F);
    func_0020B840(pattach->runB, pjt, 0x6F);
    Carry_Init(pattach->carry);
}
}
