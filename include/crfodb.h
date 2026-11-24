/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CRFODB, the crate that carries a loot (class 37 of retail's class table: 0x1A0 bytes, parent 35 of 0x180 bytes, which derives from
   class 3 (ALO, 0xE0 bytes); config/recovered/class_method_pairs.tsv pairs InitCrfodb with Sly 1's CRFODB). The fields here are the
   ones past the parent's 0x180 bytes; the parent's are unknown, so they are padded from LO's size. C++ only. */
#ifndef SLY2_CRFODB_H
#define SLY2_CRFODB_H
#include "lo.h"

struct LOOT;

struct CRFODB : LO {
    u8 unknown_0x50[0x134];
    /* 0x184 */ s32 idLootDefault; /* IdlootCrfodb: the loot id the crate carries when the save has none */
    /* 0x188 */ s32 kind;       /* Crfodb_OnGrab (compared with the held loot's kind) */
    /* 0x18C */ f32 field_0x18C; /* reader: InitCrfodb (sets 15.0f) */
    /* 0x190 */ s32 fAlert;     /* Crfodb_OnGrab */
    /* 0x194 */ struct LOOT *ploot; /* Crfodb_SpawnLoot, Crfodb_OnGrab: the loot it carries */
    u8 unknown_0x198[0x8];
};
#endif
