/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
typedef void (*SoundCommandCallback)(int, u64);
void snd_SendIOPCommandNoWait(int command, int size, char *data, SoundCommandCallback callback, u64 argument);
extern "C" void snd_StopAllStreams(void) {
    snd_SendIOPCommandNoWait(0x18, 0, 0, 0, 0);
}
