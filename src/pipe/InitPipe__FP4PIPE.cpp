// SPDX-License-Identifier: GPL-3.0-or-later
#include "pipe.h"

extern "C" {
void InitCrv(CRV *);
void bevy_player_p6_182c70(MEMBER *);
extern QW g_2a2da0;

void InitPipe__FP4PIPE(PIPE *pipe) {
    InitCrv(pipe);
    bevy_player_p6_182c70(&pipe->member);
    pipe->field_0x1C0 = g_2a2da0;
    pipe->field_0x1D4 = 9;
    pipe->field_0x1D0 = 8;
    pipe->member.field_0x1C = 1;
}
}
