/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

s32 SignalSema(s32);                               /* extern */
s32 WaitSema(s32);                                 /* extern */
extern s32 B_003D3A40;
extern s32 B_003D3A44;
extern s32 g_2dd314;

void StopLoadingLogo(void) {
    SignalSema(B_003D3A40);
    WaitSema(B_003D3A44);
    g_2dd314 = 0;
}
