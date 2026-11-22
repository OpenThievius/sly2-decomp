/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "dmachannel.h"
extern "C" {
void func_00241368(DMACHANNEL *);
s32 func_002417F0(DMACHANNEL *channel, s32 mode) {
    if (mode == 1) {
        return ((u32)channel->control >> 8) & 1;
    }
    func_00241368(channel);
    return 0;
}
}
