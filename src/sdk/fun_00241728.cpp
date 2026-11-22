/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "dmachannel.h"
extern "C" {
void func_00241368(DMACHANNEL *);
s32 func_002413E0(s32);
void func_00241728(DMACHANNEL *channel, s32 tagAddress) {
    s32 translated;
    translated = func_002413E0(tagAddress);
    func_00241368(channel);
    if (channel->tagAddress != 0xFFFFFFFF) {
        channel->tagAddress = translated;
    }
    channel->quadwords = 0;
    channel->control = (channel->control & ~0xC) | 0x105;
}
}
