/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
struct PART {
    u8 unknown_0x0[8];
    f32 field_0x8;
};
struct PARTOWNER {
    u8 unknown_0x0[0x24];
    struct PART *ppart;
};

f32 func_002562E0(struct PARTOWNER *owner) {
    return owner->ppart->field_0x8;
}
