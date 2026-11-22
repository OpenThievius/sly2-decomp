/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jt.h"

extern "C" {
int FIsPoSwFocusBase(PO *ppo);
int ZapFInvulnerable(void *pvZap, int grf);
extern PO *B_003D4A54;

/* JT slot 76 (FInvulnerable) */
int FInvulnerableJt(JT *pjt, int grf) {
    if (pjt->binocPhase == 1) return 1;
    if (pjt->jmpState == 0x15) return 1;
    if (B_003D4A54 != 0 && FIsPoSwFocusBase(B_003D4A54)) return 1;
    return ZapFInvulnerable(pjt->PvZap(), grf);
}
}
