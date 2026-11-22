/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"
#include "jtview.h"

s32 func_001841F0(struct ATTACHPT *attach, struct JTVIEW *jt) {
    return (attach->member.field_0x1C & jt->field_0x1000) != 0;
}
