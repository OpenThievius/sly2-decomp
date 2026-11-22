/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

void InitSo();
void SetAloInteract(void *, s32, s32);

void InitStgSwitch(void *pstgswitch) {
    InitSo();
    SetAloInteract(pstgswitch, 0x03FFFFFF, 8);
    SetAloInteract(pstgswitch, 0x80001, 0);
}
