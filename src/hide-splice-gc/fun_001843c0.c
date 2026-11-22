/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

void InitXfm(struct ATTACHZONE *);
void bevy_player_p6_182c70(struct MEMBER *);

void func_001843C0(struct ATTACHZONE *zone) {
    InitXfm(zone);
    bevy_player_p6_182c70(&zone->member);
}
