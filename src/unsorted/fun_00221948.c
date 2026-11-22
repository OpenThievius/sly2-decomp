/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
struct FOCUSOWNER {
    u8 unknown_0x0[0x118];
    s32 *pfocus;
};

s32 func_00221948(struct FOCUSOWNER *owner) {
    return *owner->pfocus;
}
