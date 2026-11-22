/* SPDX-License-Identifier: GPL-3.0-or-later */
/* C views of the blip classes (BLIP: one marker of the radar, 0x10C0 bytes; BLIPG: a group of them, 0x460 bytes, derived from LO) for the
   sources of src/blip written in C. The C++ sources use blip.h. Only the words a function reads, with its readers. C only. */
#ifndef SLY2_BLIPVIEW_H
#define SLY2_BLIPVIEW_H
#ifdef __cplusplus
#error "blipview.h is the C view of blip.h: include blip.h in C++"
#endif
#include "types.h"
#include "dl.h"

/* LO (lo.h): the word SubscribeBlipgObject copies */
struct LOVIEW {
    u8 unknown_0x0[0x38];
    /* 0x38 */ f32 field_0x38; /* LO::field_0x38 */
};

struct BLIPGVIEW {
    u8 unknown_0x0[0x38];
    /* 0x38 */ f32 field_0x38;              /* LO::field_0x38: SubscribeBlipgObject copies the subscribed object's */
    u8 unknown_0x3C[0xA4];
    /* 0xE0 */ struct LOVIEW *ploSource;    /* SubscribeBlipgObject: the subscribed object (class 29 and up) */
    u8 unknown_0xE4[0x364];
    /* 0x448 */ struct DL dlBlips;          /* the group's blips (ibDle 0x1090): InitBlipg, RemoveBlip, PblipNew */
};

struct BLIPVIEW {
    u8 unknown_0x0[0x1088];
    /* 0x1088 */ void *psp;                 /* PblipNew: the sprite data of a blip of mode 2 */
    /* 0x108C */ struct BLIPGVIEW *pblipg;  /* PblipNew, RemoveBlip: the group */
};

#if defined(__mips__)
typedef char check_BLIPGVIEW_dlBlips[((unsigned int)&((struct BLIPGVIEW *)0)->dlBlips == 0x448) ? 1 : -1];
typedef char check_BLIPVIEW_pblipg[((unsigned int)&((struct BLIPVIEW *)0)->pblipg == 0x108C) ? 1 : -1];
#endif
#endif
