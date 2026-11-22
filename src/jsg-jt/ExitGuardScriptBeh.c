/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardscriptbeh.h"

void Goal_Deactivate(struct GUARDSCRIPTBEH *beh);
void RemoveGuardSgs(struct STEPGUARD *pguard, s32 sgs);
void SetGuardScript(struct GUARDSCRIPTBEH *beh, struct SCRIPT *pscript, s32 flag, void *resume);
void func_001EF038(struct GUARDSCRIPTBEH *beh);

void ExitGuardScriptBeh(struct GUARDSCRIPTBEH *beh) {
    Goal_Deactivate(beh);
    func_001EF038(beh);
    SetGuardScript(beh, 0, 0, 0);
    RemoveGuardSgs(beh->pguard, 0x21);
}
