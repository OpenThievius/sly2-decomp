/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
struct PART {
    u8 unknown_0x0[0x14];
    s16 field_0x14;
};
struct PARTOWNER {
    u8 unknown_0x0[0x24];
    struct PART *ppart;
};

s16 func_00256318(struct PARTOWNER *owner) {
    return owner->ppart->field_0x14;
}
