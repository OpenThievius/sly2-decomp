/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "ambview.h"

void snd_ContinueSound(s32 voice);

void ContinueAmbVoice(struct AMBVIEW *pamb)
{
    snd_ContinueSound(pamb->voice);
}
