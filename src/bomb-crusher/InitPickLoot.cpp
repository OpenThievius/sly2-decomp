// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "loot.h"
#include "sw.h"
extern "C" {
void InitSo();
extern const QW RO_002A2DE0;
void InitPickLoot(LOOT *loot) {
    InitSo();
    u32 flags = loot->grfSw;
    QW pos = RO_002A2DE0;
    loot->state = -1;
    loot->vHeld = pos;
    if ((flags ^ 1) & 1) {
        loot->pgrfentry->grf |= 2;
        return;
    }
    loot->grfSw = flags | 2;
}
}
