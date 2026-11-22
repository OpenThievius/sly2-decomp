/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

void CreateSharedSlotheaps_1befb8(s32 initializeP, s32 priority);

void CreateSharedSlotheaps_1befb8_thunk(void) {
    CreateSharedSlotheaps_1befb8(1, 0xFFFF);
}
