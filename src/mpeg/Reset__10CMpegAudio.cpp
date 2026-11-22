// SPDX-License-Identifier: GPL-3.0-or-later
#include "cmpeg.h"
extern "C" void snd_ResetMovieSound();

void CMpegAudio::Reset()
{
    if (state != 0) {
        snd_ResetMovieSound();
        state = 1;
        idStream = -1;
        qHeader.Reset();
        qData.Reset();
        qIop.Reset();
    }
}
