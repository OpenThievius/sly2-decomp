/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
struct FLAGOWNER {
    u8 unknown_0x0[0xFC];
    s32 flags;
};
struct JTFIELD1000 {
    u8 unknown_0x0[0x1000];
    s32 field_0x1000;
};

void func_00184028(struct FLAGOWNER *owner, struct JTFIELD1000 *jt) {
    owner->flags = owner->flags | jt->field_0x1000;
}
