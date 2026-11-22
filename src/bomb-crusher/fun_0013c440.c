/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct LOOT_13C440 {
    u8 unknown_0x0[0x158];
    void *plootdefSel;
};

void func_0013C440(struct LOOT_13C440 *loot) {
    loot->plootdefSel = 0;
}
