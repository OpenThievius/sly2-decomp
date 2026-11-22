/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "script.h"

struct STEPGUARD;
void func_00171CF8(struct STEPGUARD *pguard, s32 arg);

void RunGuardScriptIfActor(s32 arg, struct STEPGUARD *pguard) {
    if (pguard != 0) {
        func_00171CF8(pguard, arg);
    }
}
