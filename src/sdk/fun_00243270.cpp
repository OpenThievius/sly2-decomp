/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "pad.h"
extern "C" {
void func_00234F48(char *, char *);
extern PADPORT B_004505D0[];
PADFRAME *func_00243270(s32 port, s32 slot) {
    PADFRAME *frames = B_004505D0[port].slot[slot].frames;
    func_00234F48((char *)frames, (char *)frames + 0xFF);
    s32 second = frames[0].counter < frames[1].counter;
    return frames + second;
}
}
