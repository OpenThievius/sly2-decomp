/* SPDX-License-Identifier: GPL-3.0-or-later */
/* A DMA channel's register block as the SDK's DMA functions see it (func_00241368 polls the control word's busy bit 8):
   control word at 0x00, memory address 0x10, quadword count 0x20, tag address 0x30. Names are ours, from the EE's public
   hardware layout (source:hardware) and what func_00241728, func_002417A0 and func_002417F0 write. Retail's code reads and
   writes these without volatile. s32 on purpose: u32 changes the mask constants. C and C++. */
#ifndef SLY2_DMACHANNEL_H
#define SLY2_DMACHANNEL_H
#include "types.h"
typedef struct DMACHANNEL {
    s32 control;      /* 0x00 */
    u8 unknown_0x4[0xC];
    s32 address;      /* 0x10 */
    u8 unknown_0x14[0xC];
    s32 quadwords;    /* 0x20 */
    u8 unknown_0x24[0xC];
    s32 tagAddress;   /* 0x30 */
} DMACHANNEL;
#endif
