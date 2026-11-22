/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
struct OBJECT90 {
    u8 unknown_0x0[0x90];
    s128 field_0x90;
};

s128 func_00256298(struct OBJECT90 *object) {
    return object->field_0x90;
}
