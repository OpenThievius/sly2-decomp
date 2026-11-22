// SPDX-License-Identifier: GPL-3.0-or-later
#include "coin.h"

extern "C" void func_001C7A10(COIN *coin, int meshShown)
{
    COINLOOTDEF *ploot = coin->cur;
    unsigned cmesh = ploot->cmesh;
    if (cmesh < 3) {
        ploot->ameshShown[cmesh] = meshShown;
        ploot->cmesh = cmesh + 1;
    }
}
