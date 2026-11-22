// SPDX-License-Identifier: GPL-3.0-or-later
#include "amb.h"
extern "C" {
void SetAmbGrf(AMB *, s32, s32);
void StopAmb(AMB *, f32);
void OnAmbVoicePolled(s32 finished, s64 arg)
{
    AMB *pamb = (AMB *)(s32)arg;
    if (finished == 0) {
        StopAmb(pamb, 0.0f);
    } else {
        SetAmbGrf(pamb, 0x400, 0x400);
    }
    pamb->Release();
}
}
