/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
struct FOCUSOWNER {
    u8 unknown_0x0[0x118];
    struct FOCUS *pfocus;
};

s32 func_00221958(struct FOCUSOWNER *owner) {
    return (s32)owner->pfocus;
}
