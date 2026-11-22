/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
s32 sceCdGetDiskType();
s32 func_00242AB8(void) {
    s32 diskType;
    diskType = sceCdGetDiskType();
    return (diskType == -1) ? 0 : diskType;
}
}
