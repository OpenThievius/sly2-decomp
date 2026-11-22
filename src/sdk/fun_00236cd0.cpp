/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
struct FLAGGEDOBJECT {
    u8 unknown_0x0[0x10];
    u32 flags;
    u8 unknown_0x14[4];
    s32 field_0x18;
};
void func_00236CD0(FLAGGEDOBJECT *object) {
    object->field_0x18 = 0;
    object->flags = object->flags & 0xFFFFFFFE;
}
}
