/* SPDX-License-Identifier: GPL-3.0-or-later */
/* LOOT, a collectable the guards and Jt carry (Crfodb_SpawnLoot, GiveJtLoot, UpdatePickLoot): a subclass of SO. Its size and class
   number are not known; the fields below start at SO's size 0x150. Local to the sources that use it until a header is agreed. */
#ifndef SLY2_LOOT_H
#define SLY2_LOOT_H
#include "so.h"

struct LOOT : SO {
    u8 unknown_0x150[0xC];
    /* 0x15C */ void *pguard;   /* Crfodb_SpawnLoot sets it to the guard that carries it; Crfodb_OnGrab, GiveJtLoot */
    u8 unknown_0x160[0x24];
    /* 0x184 */ s32 state;      /* AdjustLootNewXp (tests 5); HandleLootMessage, UpdatePickLoot */
};
#endif
