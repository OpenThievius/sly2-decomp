// SPDX-License-Identifier: GPL-3.0-or-later
#include "cmpeg.h"
extern "C" void snd_PauseAllSoundsInGroup(unsigned int);
extern "C" void StopStream(void *);
extern "C" void func_00227788(void *);
extern "C" void snd_StopAllStreams(void);
extern "C" int snd_FlushSoundCommands(void);
extern "C" int snd_StreamSafeCheckCDIdle(int);
extern "C" int snd_StreamSafeCdSync(int);
extern "C" int snd_GetMasterVolume(int);
extern "C" void snd_SetMasterVolume(int, int);
extern "C" char B_003DD040;
extern "C" char B_004435F0;
extern CMpeg B_002F66B0;

void CMpegAudio::Init()
{
    snd_PauseAllSoundsInGroup(0xFFFFFFFFu);
    StopStream(&B_003DD040);
    func_00227788(&B_004435F0);
    snd_StopAllStreams();
    while (snd_FlushSoundCommands() != 0) {
    }
    snd_StreamSafeCheckCDIdle(1);
    snd_StreamSafeCdSync(0);
    volumeMovie = snd_GetMasterVolume(2);
    volumeMusic = snd_GetMasterVolume(0x10);
    snd_SetMasterVolume(2, 0x400);
    snd_SetMasterVolume(0x10, 0x400);
    state = 1;
    idStream = -1;
    qHeader.Init(0x28, header);
    qData.Init(0x18000, B_002F66B0.pbBuffer + 0x80000);
}
