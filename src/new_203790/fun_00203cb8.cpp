// SPDX-License-Identifier: GPL-3.0-or-later
#include "step.h"
extern "C" {

void *PpartFindAlo(STEP *pstep, s32 key);
void func_00203D00(STEP *pstep, void *palo, s32 arg2);

void func_00203CB8(STEP *pstep, s32 key, s32 arg2) {
    void *palo;

    palo = PpartFindAlo(pstep, key);
    if (palo != 0) {
        func_00203D00(pstep, palo, arg2);
    }
}
}
