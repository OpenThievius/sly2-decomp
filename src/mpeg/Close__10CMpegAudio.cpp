// SPDX-License-Identifier: GPL-3.0-or-later
#include "cmpeg.h"
extern "C" void snd_CloseMovieSound();
extern "C" void snd_ContinueAllSoundsInGroup(u32);
extern "C" void snd_SetMasterVolume(int, int);

void CMpegAudio::Close()
{
    state = 0;
    snd_CloseMovieSound();
    snd_SetMasterVolume(2, volumeMovie);
    snd_SetMasterVolume(0x10, volumeMusic);
    snd_ContinueAllSoundsInGroup(0xFFFFFFFFu);
}
