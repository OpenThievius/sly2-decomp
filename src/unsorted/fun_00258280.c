/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
struct JTVIEW {
    u8 unknown_0x0[0xE00];
    s32 *field_0xE00;
};

s32 func_00258280(struct JTVIEW *jt) {
    return *jt->field_0xE00;
}
