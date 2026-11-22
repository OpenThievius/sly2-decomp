/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardscriptbeh.h"

void AddGuardSgs(struct STEPGUARD *pguard, s32 sgs);
void func_001EEF68(struct GUARDSCRIPTBEH *beh);

void InitGuardScriptBeh(struct GUARDSCRIPTBEH *beh) {
    func_001EEF68(beh);
    AddGuardSgs(beh->pguard, 0x21);
}
