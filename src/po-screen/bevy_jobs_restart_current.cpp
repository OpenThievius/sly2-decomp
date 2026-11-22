// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
#include "blot.h"

extern "C" s32 func_002121C8();
extern "C" void UpdateBlotMovie(BLOT *);
extern "C" s32 CGc_FFindScreen(void *);
extern "C" s32 FJoyButtonPressed(void *, s32);
extern "C" void ClearHandsOff(SW *, s32);
extern "C" void bevy_jobs_162df8(JOB *);
extern "C" char B_002E6550[];
extern "C" char B_003DA4F0[];
extern "C" char B_002DFC00[];
extern "C" SW B_003DD490;
extern "C" s32 g_2dd318;
extern "C" f32 g_2ddf0c;

void bevy_jobs_restart_current(RESTARTBLOT *blot) {
    if (func_002121C8() != 0)
        return;
    UpdateBlotMovie(blot);
    if (blot->blots == 2 && g_2ddf0c - blot->time > 0.5f && CGc_FFindScreen(B_002E6550) == 0
        && CGc_FFindScreen(B_003DA4F0) == 0 && FJoyButtonPressed(B_002DFC00, 0xF0) != 0) {
        ClearHandsOff(&B_003DD490, 0);
        if (blot->field_0x114 == 0 && B_003DD490.pjobCurrent != 0) {
            g_2dd318 = g_2dd318 + 1;
            bevy_jobs_162df8(B_003DD490.pjobCurrent);
        }
        blot->Hide();
    }
    blot->field_0x110 = 1;
}
