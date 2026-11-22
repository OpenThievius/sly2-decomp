/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "ambview.h"

void snd_PauseSound(s32 voice);

void PauseAmbVoice(struct AMBVIEW *pamb)
{
    snd_PauseSound(pamb->voice);
}
