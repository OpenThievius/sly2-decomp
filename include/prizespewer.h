/* SPDX-License-Identifier: GPL-3.0-or-later */
/* PrizeSpewer: the SO that holds a prize object and spews it (class vtable at 0x2D5450: InitSo, PostPrizeSpewerLoad at slot 15,
   RenderPrizeSpewer at slot 18). 0x150 to 0x158 are set by SetPrizeSpewerObject and cleared by ClearPrizeSpewer; 0x15C to 0x168
   are the loaded properties of the table D_002C0CB0 that PostPrizeSpewerLoad registers (offsets 0x168, 0x15C, 0x160, 0x164).
   Readers are the class's own methods, so the fields are certain. C++ only. */
#ifndef SLY2_PRIZESPEWER_H
#define SLY2_PRIZESPEWER_H
#include "so.h"

struct SM;
struct SMA;

struct PrizeSpewer : SO {
    /* 0x150 */ struct XF *pxf;        /* RenderPrizeSpewer draws the prize at its +0x40; SetPrizeSpewerObject sets it (func_001F4C58) */
    /* 0x154 */ void *ploTemplate; /* SetPrizeSpewerObject, ClearPrizeSpewer */
    /* 0x158 */ void *ploPrize;    /* SetPrizeSpewerObject, ClearPrizeSpewer, RenderPrizeSpewer */
    u8 unknown_0x15C[0xC];         /* loaded properties 0x15C, 0x160, 0x164 of D_002C0CB0 */
    /* 0x168 */ struct SM *psm;    /* loaded property; PostPrizeSpewerLoad applies it to the spewer */
    /* 0x16C */ struct SMA *psma;  /* PostPrizeSpewerLoad: what func_001F1448 stores the applied animation in */
};

#if defined(__mips__)
SLY2_OFFSET_CHECK(PrizeSpewer, pxf, 0x150);
SLY2_OFFSET_CHECK(PrizeSpewer, psm, 0x168);
SLY2_OFFSET_CHECK(PrizeSpewer, psma, 0x16C);
#endif
#endif
