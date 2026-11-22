// SPDX-License-Identifier: GPL-3.0-or-later
#include "coin.h"

extern "C" {
void func_001C7A08(COIN *coin);

void func_001C7988(COIN *coin, s32 id, s32 lootkc) {
    func_001C7A08(coin);
    s32 iloot = coin->cloot;
    if (iloot < 0x20) {
        coin->cloot = iloot + 1;
        COINLOOTDEF *ploot = &coin->aloot[iloot];
        coin->cur = ploot;
        ploot->lootkc = lootkc;
        ploot->cmesh = 0;
        ploot->field_0x14 = -1;
        ploot->field_0x18 = -1;
        ploot->id = id;
    }
}

}
