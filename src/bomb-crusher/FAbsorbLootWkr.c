/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct LOOT_13C368 {
    u8 unknown_0x0[0x184];
    s32 state;
};

s32 FAbsorbSoWkr();
void SetLootState(struct LOOT_13C368 *, s32);

s32 FAbsorbLootWkr(struct LOOT_13C368 *loot) {
    if ((FAbsorbSoWkr() == 0) || (loot->state != 5)) {
        return 0;
    }
    SetLootState(loot, 0);
    return 1;
}
