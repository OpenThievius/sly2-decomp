// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
extern "C" {
s32 FIsGuardInSgs(STEPGUARD *, s32);
GOAL *func_00205458(STEPGUARD *, s32);

s32 CHitClingingGuard(STEPGUARD *pguard) {
    if (FIsGuardInSgs(pguard, 0x17) != 0) {
        return ((GOALGRAB *)func_00205458(pguard, 0xB1))->chit;
    }
    return 0;
}
}
