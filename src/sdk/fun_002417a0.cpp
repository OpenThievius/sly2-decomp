/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "dmachannel.h"
extern "C" {
void func_00241368(DMACHANNEL *);
void func_002417A0(DMACHANNEL *channel) {
    func_00241368(channel);
    channel->quadwords = 0;
    channel->control = (((channel->control & ~0xC) | 4) & ~1) | 0x100;
}
}
