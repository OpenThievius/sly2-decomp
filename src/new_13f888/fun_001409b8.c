/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct SW;

s32 FSwHandsOff(struct SW *psw);
extern struct SW B_003DD490;

s32 func_001409B8(void) {
    return (FSwHandsOff(&B_003DD490) != 0) ? 0 : -1;
}
