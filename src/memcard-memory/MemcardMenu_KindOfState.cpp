// SPDX-License-Identifier: GPL-3.0-or-later
#include "memcardmenu.h"

extern "C" s32 MemcardMenu_KindOfState(MEMCARDMENU *pmenu) {
    s32 state;

    state = pmenu->state;
    switch (state) {
    case 17:
    case 20:
    case 23:
    case 24:
    case 27:
    case 29:
    case 34:
    case 35:
    case 36:
    case 46:
        return 1;
    case 18:
    case 21:
    case 28:
    case 32:
        return 2;
    default:
        return 0;
    }
}
