// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "loot.h"
extern "C" {
s32 FIsLoInWorld(void *);
void SetLootState(LOOT *, s32);
void ReturnLootToGuard(LOOT *loot) {
    if (loot->state == 5) {
        void *pguard = loot->pguard;
        loot->pguard = 0;
        LOOTDEF *plootdefSel = loot->plootdefSel;
        SetLootState(loot, 0);
        if ((pguard != 0) && (FIsLoInWorld(pguard) != 0)) {
            loot->pguard = pguard;
            loot->plootdefSel = plootdefSel;
            SetLootState(loot, 1);
        }
    }
}
}
