/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
extern int func_0023AFE8(unsigned int, void *, int, int, int, int);
s32 func_00236F98(s32 unused_first, s32 unused_second, s32 unused_third, void *request) {
    return (func_0023AFE8(0x80000008, request, 0x40, 0, 0, 0) != 0) ? 0 : 0x800;
}
}
