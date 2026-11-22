// SPDX-License-Identifier: GPL-3.0-or-later
#include "cref.h"
#include "blot.h"

struct LIST;

extern "C" {
CRef func_002013D8(LIST *plist, s32 otyp, s32 unused, s32 *pcArg, s32 *apvArg);

void SetBlotLabelListFromRef(BLOT *blot, LIST *plist) {
    {
        s32 clabel;
        CRef ref = func_002013D8(plist, 0x10, 0xA, &clabel, blot->alabel);
    }
    blot->Select(-1);
}
}
