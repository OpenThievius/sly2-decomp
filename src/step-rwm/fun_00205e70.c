/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct LO *PloNew(s32, struct SO *, s32, s32);
extern struct LO *B_003DD48C;

void func_00205E70(void) {
    if (B_003DD48C == 0) {
        B_003DD48C = PloNew(0x7D, 0, 0x656, -1);
    }
}
