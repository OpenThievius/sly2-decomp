/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "targetholder.h"

void func_001F4BF8(void *owner);

void func_002562B8(TARGETHOLDER *holder, f32 value) {
    holder->values->field_0x8 = value;
    func_001F4BF8(holder->owner);
}
