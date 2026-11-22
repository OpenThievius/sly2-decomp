// SPDX-License-Identifier: GPL-3.0-or-later
#include "amb.h"
extern "C" {
void snd_AutoVol(s32 voice, s32 volume, s32 ticks, s32 mode);
void snd_StopSound(s32 voice);
void StopSound__FP3AMBi(AMB *pamb)
{
    f32 fadeSeconds;
    fadeSeconds = pamb->fadeSeconds;
    if (fadeSeconds > 0.0f) {
        snd_AutoVol(pamb->voice, -4, (s32)(fadeSeconds * 240.0f), 2);
        return;
    }
    snd_StopSound(pamb->voice);
}
}
