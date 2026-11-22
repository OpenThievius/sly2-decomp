/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "mpeg.h"
void func_00254898(u32);
void func_00254910(u32);
void func_00254988(IPUSTATE *state) {
    func_00254910(1);
    state->toIpuAddress = *(volatile s32 *)0x1000B410;
    state->toIpuTag = *(volatile s32 *)0x1000B430;
    state->toIpuCount = *(volatile s32 *)0x1000B420;
    state->toIpuControl = *(volatile s32 *)0x1000B400;
    while (*(volatile s32 *)0x10002010 & 0xF0) {
    }
    func_00254898(0);
    state->fromIpuAddress = *(volatile s32 *)0x1000B010;
    state->fromIpuCount = *(volatile s32 *)0x1000B020;
    state->fromIpuControl = *(volatile s32 *)0x1000B000;
    state->bitPosition = *(volatile s32 *)0x10002020;
    state->control = *(volatile s32 *)0x10002010;
}
