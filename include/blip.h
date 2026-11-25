/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The blip classes (BLIPG: a group of radar markers, 0x460 bytes, derived from LO: its vtable at 0x2CB5D8 holds LO's slots, PblipgNew
   calls slots 7, 11 and 15; BLIP: one marker, 0x10C0 bytes, the slot size of SW::slotheapBlip). Only the words matched functions read. C++ */
#ifndef SLY2_BLIP_H
#define SLY2_BLIP_H
#include "sw.h"

struct BLIPG : LO {
    u8 unknown_0x50[0x90];
    /* 0xE0 */ LO *ploSource;   /* SubscribeBlipgObject: the subscribed object */
    u8 unknown_0xE4[0x7C];
    /* 0x160 */ s32 mode;       /* PblipNew: a blip of a group in mode 2 gets sprite data */
    u8 unknown_0x164[0x3C];
    /* 0x1A0 */ s32 cqwTexture; /* PropagateBlipgShader: the quadwords of the texture packets, a power of two up to 16; reader: PropagateBlipgShader (a BLIPG method, guess) */
    u8 unknown_0x1A4[0xC];
    /* 0x1B0 */ QW aqw[0x20];   /* PropagateBlipgShader fills one 16-byte packet per shader frame (duplicated up to cqwTexture) */
    /* 0x3B0 */ s32 hasColor;   /* PropagateBlipgShader: set once the colour is taken from the shader */
    /* 0x3B4 */ u8 color[4];    /* PropagateBlipgShader: half the shader's colour, rounded up */
    u8 unknown_0x3B8[0x80];
    /* 0x438 */ void *pgifs;    /* PropagateBlipgShader: the shader's GIF packet template, picked by the shader's flag 1 */
    u8 unknown_0x43C[0xC];
    /* 0x448 */ DL dlBlips;     /* InitBlipg: InitDl with ibDle 0x1090; PblipNew appends, RemoveBlip, OnBlipgRemove */
    u8 unknown_0x454[0xC];
};

struct BLIP {
    u8 unknown_0x0[0x1088];
    /* 0x1088 */ void *psp;     /* PblipNew: sprite data from SW::slotheapBlipSp */
    /* 0x108C */ BLIPG *pblipg; /* PblipNew, RemoveBlip */
    /* 0x1090 */ DLE dle;       /* the entry in BLIPG::dlBlips */
    u8 unknown_0x1098[0x28];
};

#if defined(__mips__)
SLY2_SIZE_CHECK(BLIPG, 0x460);
SLY2_SIZE_CHECK(BLIP, 0x10C0);
SLY2_OFFSET_CHECK(BLIPG, mode, 0x160);
SLY2_OFFSET_CHECK(BLIPG, dlBlips, 0x448);
SLY2_OFFSET_CHECK(BLIP, pblipg, 0x108C);
SLY2_OFFSET_CHECK(BLIP, dle, 0x1090);
#endif
#endif
