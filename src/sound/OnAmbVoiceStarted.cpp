// SPDX-License-Identifier: GPL-3.0-or-later
#include "amb.h"
extern "C" void OnAmbVoiceStarted(int voice, long arg)
{
    AMB *pamb = (AMB *)arg;
    pamb->voice = voice;
    pamb->fPending = 0;
    pamb->Release();
}
