/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

void InitXfm(void *);
void bevy_player_p6_182c70(struct MEMBER *);

void AttachCyl_Init(struct ATTACHCYL *attach) {
    InitXfm(attach);
    bevy_player_p6_182c70(&attach->member);
}
