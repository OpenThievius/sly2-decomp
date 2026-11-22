// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "loot.h"
extern "C" int FIsBasicDerivedFrom(void *, int);
extern "C" int FIgnoreSoIntersection(void *, void *);

struct XP_13C278 { u8 unknown_0x0[0x14]; void **pplo; };

int FIgnoreLootIntersection(LOOT *loot, XP_13C278 *pxp) {
    if (loot->state == 5) {
        if (FIsBasicDerivedFrom(*pxp->pplo, 0x34)) {
            return 3;
        }
    }
    return FIgnoreSoIntersection(loot, pxp);
}
