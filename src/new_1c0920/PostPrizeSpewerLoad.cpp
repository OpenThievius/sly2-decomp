// SPDX-License-Identifier: GPL-3.0-or-later
#include "prizespewer.h"
#include "soproperty.h"

extern "C" {
void PostSoLoad(PrizeSpewer *pspewer);
void SetSoProperties(PrizeSpewer *pspewer, s32 cprop, const SOPROPERTY *aprop);
void func_001F1448(struct SM *psm, SO *proot, s32 oid, s32 grf, struct SMA **ppsma);
extern unsigned int D_002C0CB0[12]; /* as src/data/new_1c0920.cpp defines it: SetSoProperties reads it as 4 SOPROPERTY records */

void PostPrizeSpewerLoad(PrizeSpewer *pspewer) {
    PostSoLoad(pspewer);
    SetSoProperties(pspewer, 4, (const SOPROPERTY *)D_002C0CB0);
    func_001F1448(pspewer->psm, pspewer, -1, 0, &pspewer->psma);
}

}
