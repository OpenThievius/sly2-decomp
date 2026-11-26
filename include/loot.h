/* SPDX-License-Identifier: GPL-3.0-or-later */
/* LOOT, a collectable the guards and Jt carry (Crfodb_SpawnLoot, GiveJtLoot, UpdatePickLoot): a subclass of SO. Its size and class
   number are not known; the fields below start at SO's size 0x150. Local to the sources that use it until a header is agreed. */
#ifndef SLY2_LOOT_H
#define SLY2_LOOT_H
#ifdef __cplusplus
#include "so.h"
#else
#include "types.h"
#endif

/* one 0x2C-byte definition of the table at LOOT::alootdef: SelectLootDef reads the id, func_0013C3B8 fills the entry (its other words
   are in that function's own view: one reader) */
struct LOOTDEF {
    /* 0x0 */ s32 id;             /* SelectLootDef compares it, func_0013C3B8 sets it */
    /* 0x4 */ s32 field_0x4;       /* func_0013C3B8 sets it (its third argument): one reader, a record of LOOT's own table */
    u8 unknown_0x8[0x4];
    /* 0xC */ s32 timed;           /* UpdatePickLoot (its own view): one reader */
    u8 unknown_0x10[0x4];
    /* 0x14 */ s32 field_0x14;     /* func_0013C3B8 sets it (its last argument): one reader */
    /* 0x18 */ s32 field_0x18;     /* func_0013C3B8 sets -1: one reader */
    /* 0x1C */ u32 cslot;          /* func_0013C448 reads it as the count of the slots at 0x20, func_0013C3B8 clears it: two readers agree */
    u8 unknown_0x20[0xC];          /* func_0013C448 reads three words here (one reader: its own view) */
};

#ifdef __cplusplus
struct LOOT : SO {
    /* 0x150 */ s32 clootdef;           /* SelectLootDef (count), func_0013C3B8 (appends while below 0x20) */
    /* 0x154 */ struct LOOTDEF *alootdef; /* the same two functions */
    /* 0x158 */ struct LOOTDEF *plootdefSel; /* SelectLootDef, func_0013C440 (clears), LootId (reads its id), UpdatePickLoot, ReturnLootToGuard */
    /* 0x15C */ void *pguard;   /* Crfodb_SpawnLoot sets it to the guard that carries it; Crfodb_OnGrab, GiveJtLoot */
    /* 0x160 */ s32 idThief;   /* UpdatePickLoot (a LOOT method) passes it to DropJtLoot; guess: the id of the thief that carries it */
    u8 unknown_0x164[0xC];
    /* 0x170 */ QW vHeld;       /* InitPickLoot (from RO_002A2DE0), RenderLoot (scale source) */
    u8 unknown_0x180[0x4];
    /* 0x184 */ s32 state;      /* AdjustLootNewXp (tests 5); HandleLootMessage, UpdatePickLoot */
    /* 0x188 */ f32 tState;     /* UpdatePickLoot (time since state 5 began), RenderLoot (time since state 4 began) */
    /* 0x18C */ void *psender;  /* HandleLootMessage (LOOT's message handler): the sender of message 8 it acts on; guess */
};
#else
/* the C view: the three words func_0013C3B8 reads past SO's 0x150 bytes */
struct LOOT {
    u8 unknown_0x0[0x150];
    s32 clootdef;
    struct LOOTDEF *alootdef;
    struct LOOTDEF *plootdefSel;
};
#endif
#endif
