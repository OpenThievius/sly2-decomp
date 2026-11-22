/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

void InitXfm(struct ATTACHPT *);
void bevy_player_p6_182c70(struct MEMBER *);

void func_00183F08(struct ATTACHPT *attach) {
    InitXfm(attach);
    bevy_player_p6_182c70(&attach->member);
    attach->member.field_0x10 = 1;
    attach->field_0x110 = 200.0f;
    attach->member.field_0x1C = 0;
}
