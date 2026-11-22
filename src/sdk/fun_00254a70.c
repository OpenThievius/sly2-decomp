/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "mpeg.h"
void func_00254898(u32);
void func_00254910(u32);
void func_00254A70(IPUSTATE *state) {
    u32 bitPosition;
    s32 toAddressWord;
    s32 toAddress;
    s32 toCount;
    s32 fifoQuadwords;
    s32 fromAddress;
    s32 bits;
    bitPosition = state->bitPosition;
    bits = bitPosition & 0x7F;
    toAddressWord = state->toIpuAddress;
    fifoQuadwords = ((bitPosition >> 0x10) & 3) + ((bitPosition >> 8) & 0xF);
    fromAddress = state->fromIpuAddress;
    toCount = state->toIpuCount + fifoQuadwords;
    toAddress = toAddressWord - fifoQuadwords * 0x10;
    if (fromAddress != 0 && state->fromIpuCount != 0) {
        *(volatile s32 *)0x1000B010 = fromAddress;
        *(volatile s32 *)0x1000B020 = state->fromIpuCount;
        func_00254898(state->fromIpuControl | 0x100);
    }
    while (*(volatile s32 *)0x10002010 < 0) {
    }
    *(volatile s32 *)0x10002000 = bits;
    while (*(volatile s32 *)0x10002010 < 0) {
    }
    if (toAddress != 0 && toCount != 0) {
        *(volatile s32 *)0x1000B410 = toAddress;
        *(volatile s32 *)0x1000B430 = state->toIpuTag;
        *(volatile s32 *)0x1000B420 = toCount;
        func_00254910(state->toIpuControl | 0x100);
    }
}
