// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
extern "C" {
s32 FIsGuardInSgs(STEPGUARD *, s32);
void func_0017A8C8(GOAL *, s32);
GOAL *func_00205458(STEPGUARD *, s32);
void func_00209FB8(STEPGUARD *pguard) {
    if ((FIsGuardInSgs(pguard, 0x16) != 0) || (FIsGuardInSgs(pguard, 0x13) != 0)) {
        func_0017A8C8(func_00205458(pguard, 0xB0), 3);
    }
}
}
