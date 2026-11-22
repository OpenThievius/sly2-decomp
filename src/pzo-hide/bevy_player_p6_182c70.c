/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

void func_001A6CA8(void *, s32);

void bevy_player_p6_182c70(struct MEMBER *member) {
    const struct MEMBERVT *vt;
    s16 delta;

    member->field_0x14 = -1;
    member->field_0x8 = 3.4028235e38f;
    vt = member->vt;
    member->field_0x1C = 7;
    delta = vt->delta;
    func_001A6CA8(vt->fn((char *)member + delta), 3);
}
