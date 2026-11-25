// SPDX-License-Identifier: GPL-3.0-or-later
#include "loot.h"
extern "C" void SelectLootDef(LOOT *ploot, int id)
{
    for (int i = 0; i < ploot->clootdef; i++) {
        if (id == ploot->alootdef[i].id) {
            ploot->plootdefSel = &ploot->alootdef[i];
            return;
        }
    }
    ploot->plootdefSel = ploot->alootdef;
}
