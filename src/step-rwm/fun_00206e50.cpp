// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
extern "C" {
void RemoveGuardIgnoredClass(STEPGUARD *, s32);
extern s32 D_002C3D10[5];

void func_00206E50(STEPGUARD *pguard) {
    s32 *pcid;
    s32 cid;
    u32 icid;

    icid = 0;
    pcid = D_002C3D10;
    do {
        cid = *pcid;
        icid += 1;
        pcid += 1;
        RemoveGuardIgnoredClass(pguard, cid);
    } while (icid < 5U);
}

}
