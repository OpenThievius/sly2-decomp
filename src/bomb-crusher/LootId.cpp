// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "loot.h"
extern "C" int LootId(LOOT *loot)
{
    LOOTDEF *plootdef = loot->plootdefSel;
    int id = -1;
    if (plootdef != 0) {
        id = plootdef->id;
    }
    return id;
}
