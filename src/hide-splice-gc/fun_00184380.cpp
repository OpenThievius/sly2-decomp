// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"
extern "C" {
s32 func_001A6AF8(struct ATTACHPT *, s32);

s32 func_00184380(struct LIFTPT *lift, struct ATTACHPT *other) {
    if (other->member.field_0x14 != lift->oidLast) {
        return 1;
    }
    return func_001A6AF8(other, lift->field_0x180);
}
}
