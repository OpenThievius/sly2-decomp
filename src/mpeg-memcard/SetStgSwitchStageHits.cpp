// SPDX-License-Identifier: GPL-3.0-or-later
#include "stgswitch.h"
extern "C" {
STGNODE *PstageStgSwitchCur(STGSWITCH *, const char *);

void SetStgSwitchStageHits(STGSWITCH *pstgswitch, s32 hits) {
    STGNODE *pnode;

    if (pstgswitch->istage != -1) {
        pnode = PstageStgSwitchCur(pstgswitch, "LOOP");
        if ((pnode != 0) && (hits != 0)) {
            pnode->fForward = hits;
        }
    }
}
}
