/* SPDX-License-Identifier: GPL-3.0-or-later */
/* LOOT, a collectable the guards and Jt carry (Crfodb_SpawnLoot, GiveJtLoot, UpdatePickLoot): a subclass of SO. Its size and class
   number are not known; the fields below start at SO's size 0x150. Local to the sources that use it until a header is agreed. */
#ifndef SLY2_LOOT_H
#define SLY2_LOOT_H
#include "so.h"

/* one 0x2C-byte definition of the table at LOOT::alootdef: SelectLootDef reads the id, func_0013C3B8 fills the entry (its other words
   are in that function's own view: one reader) */
struct LOOTDEF {
    /* 0x0 */ s32 id;             /* SelectLootDef compares it, func_0013C3B8 sets it */
    u8 unknown_0x4[0x28];
};

struct LOOT : SO {
    /* 0x150 */ s32 clootdef;           /* SelectLootDef (count), func_0013C3B8 (appends while below 0x20) */
    /* 0x154 */ struct LOOTDEF *alootdef; /* the same two functions */
    /* 0x158 */ struct LOOTDEF *plootdefSel; /* SelectLootDef, func_0013C440 (clears), LootId (reads its id), UpdatePickLoot, ReturnLootToGuard */
    /* 0x15C */ void *pguard;   /* Crfodb_SpawnLoot sets it to the guard that carries it; Crfodb_OnGrab, GiveJtLoot */
    u8 unknown_0x160[0x10];
    /* 0x170 */ QW vHeld;       /* InitPickLoot (from RO_002A2DE0), RenderLoot (scale source) */
    u8 unknown_0x180[0x4];
    /* 0x184 */ s32 state;      /* AdjustLootNewXp (tests 5); HandleLootMessage, UpdatePickLoot */
    /* 0x188 */ f32 tState;     /* UpdatePickLoot (time since state 5 began), RenderLoot (time since state 4 began) */
};
#endif
