// SPDX-License-Identifier: GPL-3.0-or-later
#include "rumble.h"

extern "C" {
void SetRumbleRums__FP6RUMBLE4RUMS(RUMBLE *, s32);

void InitRumble__FP6RUMBLEii(RUMBLE *rumble, s32 port, s32 slot) {
    if (rumble->rums == 0) {
        SetRumbleRums__FP6RUMBLE4RUMS(rumble, 1);
    } else {
        SetRumbleRums__FP6RUMBLE4RUMS(rumble, 3);
    }
    rumble->nPort = port;
    rumble->nSlot = slot;
}
}
