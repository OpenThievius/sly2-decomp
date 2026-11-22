// SPDX-License-Identifier: GPL-3.0-or-later
#include "stgswitch.h"
extern "C" {
void *PvAllocStackImpl__Fi(void *);

void AddStgSwitchStage(STGSWITCH *pstgswitch, s32 id) {
    struct StkParams_1BB950 { s32 size; s32 align; } sp;
    s32 istage;
    STGNODE *pnode;
    istage = pstgswitch->cstage;
    if (istage < 0x20) {
        pstgswitch->istage = istage;
        pstgswitch->cstage = istage + 1;
        pnode = pstgswitch->anode + istage;
        pnode->id = id;
        pnode->fForward = 1;
        sp.size = 0x200;
        sp.align = 0x10;
        pnode->ents = PvAllocStackImpl__Fi(&sp);
    }
}
}
