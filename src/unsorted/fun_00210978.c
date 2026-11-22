/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
struct OBJECT3EA8 {
    u8 unknown_0x0[0x3EA8];
    s32 field_0x3EA8;
};

struct OBJECT3EA8 *func_00210978(struct OBJECT3EA8 *object, s32 value) {
    if (value == 1) {
        object->field_0x3EA8 = value;
    }
    return object;
}
