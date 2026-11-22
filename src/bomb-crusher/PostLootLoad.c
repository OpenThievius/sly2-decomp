/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

void PostSoLoad();
void SetLootState(void *, s32);

void PostLootLoad(void *loot) {
    PostSoLoad();
    SetLootState(loot, 0);
}
