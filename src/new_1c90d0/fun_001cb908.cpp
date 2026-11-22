// SPDX-License-Identifier: GPL-3.0-or-later
#include "pipe.h"

extern "C" {
void InitCrv(CRV *);
void bevy_player_p6_182c70(MEMBER *);
}
void func_001CB908(CRV13 *ppipe)
{
    InitCrv(ppipe);
    bevy_player_p6_182c70(&ppipe->member);
    ppipe->field_0x1C4 = 1.0f;
    ppipe->field_0x1C0 = 1000.0f;
}
