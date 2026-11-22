// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"
extern "C" void InitCrv(void *);
extern "C" void bevy_player_p6_182c70(MEMBER *);

void AttachCrv_Init(ATTACHCRV *attach)
{
    InitCrv(attach);
    bevy_player_p6_182c70(&attach->member);
    attach->field_0x1BC = 3;
}
