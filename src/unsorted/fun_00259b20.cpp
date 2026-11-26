// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "so.h"
#include "phys.h"
/* the region link PHYS::plink points at: only the word at 0x10 is read here */
struct LINK {
    u8 unknown_0x0[0x10];
    s32 field_0x10;
};
extern "C" s32 func_00259B18(SO *owner) {
    PHYS *holder = owner->pphys;
    LINK *chain = 0;
    if (holder != 0) {
        chain = holder->plink;
    }
    s32 result = 0;
    if (chain != 0) {
        result = chain->field_0x10;
    }
    return result;
}
