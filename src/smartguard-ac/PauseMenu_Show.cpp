// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
extern "C" {
void CGc_PushScreen();
void SetClockRate(float *clocks, int index, float rate);
void SetHandsOff(SW *psw, int index);
void bevy_camera_follow_activity(void *pmgr, int event, void *parg);
extern char B_002DEB30;
extern SW B_003DD490;
extern float g_2dded0;

void PauseMenu_Show(void) {
    CGc_PushScreen();
    SetClockRate(&g_2dded0, 0, 0.0f);
    SetHandsOff(&B_003DD490, 0);
    bevy_camera_follow_activity(&B_002DEB30, 0x28, 0);
}

}
