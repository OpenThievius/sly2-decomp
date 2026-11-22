// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
#include "pausemenu.h"
extern "C" {
void CGc_PopScreen();
void ClearHandsOff(SW *psw, int index);
void SetClockRate(float *clocks, int index, float rate);
void bevy_camera_follow_activity(void *pmgr, int event, void *parg);
extern char B_002DEB30;
extern SW B_003DD490;
extern float g_2dded0;

void PauseMenu_Hide(PAUSEMENU *pmenu) {
    CGc_PopScreen();
    pmenu->depth = 0;
    SetClockRate(&g_2dded0, 0, 1.0f);
    ClearHandsOff(&B_003DD490, 0);
    bevy_camera_follow_activity(&B_002DEB30, 0x2C, 0);
}

}
