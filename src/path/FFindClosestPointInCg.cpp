// SPDX-License-Identifier: GPL-3.0-or-later
#include "cg.h"

extern "C" {
/* retail's call leaves its fourth word (the flags) as it finds it: PcgtPointInCgSafe takes (CG *, CGE *, QW, int) */
void *PcgtPointInCgSafe(CG *pcg, CGE *pcgeFirst, QW point);
QW PosClosestOnCgt(void *pcgt, QW point);

int FFindClosestPointInCg(CG *pcg, QW point, QW *ppos) {
    void *pcgt;

    pcgt = PcgtPointInCgSafe(pcg, pcg->acge, point);
    if (pcgt == 0) {
        return 0;
    }
    *ppos = PosClosestOnCgt(pcgt, point);
    return 1;
}
}
