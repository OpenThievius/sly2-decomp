// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
// 0x1C7A40 GetCoinLootDefId
struct LOOTHOLDER {
    u8 unknown_0x0[0x244];
    s32 *pdefId;
};
int func_001C7A40(LOOTHOLDER *holder)
{
    int defId = -1;
    if (holder->pdefId != 0) {
        defId = *holder->pdefId;
    }
    return defId;
}
