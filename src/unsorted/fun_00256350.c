/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
struct PART {
    u8 unknown_0x0[0x18];
    s32 field_0x18;
};
struct PARTOWNER {
    u8 unknown_0x0[0x24];
    struct PART *ppart;
};

s32 func_00256350(struct PARTOWNER *owner) {
    return owner->ppart->field_0x18;
}
