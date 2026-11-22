// SPDX-License-Identifier: GPL-3.0-or-later
#include "carrypart.h"

extern "C" void func_001CC2E8(CARRYPART *pcarry);

void Carry_UpdateReach_thunk(void *unused, CARRYPART *pcarry) {
    func_001CC2E8(pcarry);
}
