/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "loot.h"

void func_0013C440(struct LOOT *loot);

void func_0013C3B8(struct LOOT *loot, s32 id, s32 value4, s32 value14) {
    struct LOOTDEF *def;
    s32 count;

    func_0013C440(loot);
    count = loot->clootdef;
    if (count < 0x20) {
        loot->clootdef = count + 1;
        def = loot->alootdef + count;
        loot->plootdefSel = def;
        def->id = id;
        def->field_0x4 = value4;
        def->field_0x14 = value14;
        def->field_0x18 = -1;
        def->cslot = 0;
    }
}
