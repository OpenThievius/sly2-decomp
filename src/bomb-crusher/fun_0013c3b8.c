/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct LOOTDEF_13C3B8 {
    s32 id;
    s32 field_0x4;
    u8 unknown_0x8[0xC];
    s32 field_0x14;
    s32 field_0x18;
    s32 field_0x1C;
    u8 unknown_0x20[0xC];
};

struct LOOT_13C3B8 {
    u8 unknown_0x0[0x150];
    s32 clootdef;
    struct LOOTDEF_13C3B8 *alootdef;
    struct LOOTDEF_13C3B8 *plootdefSel;
};

void func_0013C440(struct LOOT_13C3B8 *loot);

void func_0013C3B8(struct LOOT_13C3B8 *loot, s32 id, s32 value4, s32 value14) {
    struct LOOTDEF_13C3B8 *def;
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
        def->field_0x1C = 0;
    }
}
