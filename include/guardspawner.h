/* SPDX-License-Identifier: GPL-3.0-or-later */
/* GUARDSPAWNER, the object that keeps guards spawned around the player: an LO subclass (its Update is func_00173A68, which starts
   with UpdateLo), class not recovered. It holds the spawn points the level lists (GUARDSPAWNPOINT, 0x1C bytes each), the slots of
   the guards it keeps alive (GUARDSPAWNSLOT, 0x30 each) and the delays it waits. C++ only. The class is certain (its methods read
   the fields below), so one reader is enough here, as in lo.h; each field names its readers. */
#ifndef SLY2_GUARDSPAWNER_H
#define SLY2_GUARDSPAWNER_H
#include "types.h"
#include "lo.h"

struct STEPGUARD;
struct ALERT;

/* one spawn point, 0x1C bytes: func_001733F8 fills the object ids in (PostLoad), func_00173A68 and func_00173928 mark it busy */
struct GUARDSPAWNPOINT {
    /* 0x0 */ s32 kind;            /* func_001733F8: 1 also leases a script object, 0 and 2 only find the object */
    /* 0x4 */ s32 oid;             /* func_001733F8 */
    /* 0x8 */ struct LO *plo;      /* func_001733F8: PloFindSwObject of oid */
    /* 0xC */ void *ploAux;        /* func_001733F8: the script object it makes for kind 1 */
    /* 0x10 */ void *auxData;      /* func_001733F8: that object's data pointer (at its 0x54) */
    /* 0x14 */ s32 fBusy;          /* func_00173A68 sets it with a guard, func_00173928 clears it */
    /* 0x18 */ f32 tReady;         /* func_00173928: the time the point may be used again */
};

/* one slot of a guard, 0x30 bytes: func_00173E78 picks one, func_00173A68 fills it, func_00173928 releases it */
struct GUARDSPAWNSLOT {
    /* 0x0 */ struct STEPGUARD *pactor; /* func_00173A68, func_00173928, func_00173E78 (as a void pointer), func_001746B8 */
    /* 0x4 */ f32 tSpawn;          /* func_00173A68, func_00173E78 */
    /* 0x8 */ f32 tFree;           /* func_00173928, func_00173E78 */
    /* 0xC */ struct GUARDSPAWNPOINT *ppoint; /* func_00173A68, func_00173928 */
    /* 0x10 */ s32 kind;           /* func_00173928 */
    u8 unknown_0x14[0xC];
    /* 0x20 */ QW posRelease;      /* func_00173928 */
};

struct GUARDSPAWNER : LO {
    /* 0x50 */ s32 count;          /* the spawn points: func_001733F8, func_001731B8 */
    /* 0x54 */ struct GUARDSPAWNPOINT *points; /* func_001733F8, func_001731B8 */
    /* 0x58 */ s32 cSlot;          /* slots in use: func_00173928, func_00173A68 */
    /* 0x5C */ s32 cSlotMax;       /* the slots: func_001733F8, func_00173A68, func_001746B8, func_00173E78 */
    /* 0x60 */ struct GUARDSPAWNSLOT *slots; /* func_001733F8, func_001746B8, func_00173E78 */
    u8 unknown_0x64[0xC];
    /* 0x70 */ QW posLast;         /* func_00173A68: where the player was at the last spawn */
    u8 unknown_0x80[0x10];
    /* 0x90 */ s32 clo;            /* the guard templates it clones: func_00174490 */
    /* 0x94 */ struct LO **aplo;   /* their array: func_00174490 reads it, func_001731B8 stores it */
    /* 0x98 */ s32 offsetCount;    /* AddSpawnerOffset, func_001731B8 */
    /* 0x9C */ QW *offsets;        /* AddSpawnerOffset */
    /* 0xA0 */ f32 dtFree;         /* func_00173928: how long a released slot waits (kind 1) */
    /* 0xA4 */ f32 dtReady;        /* func_00173928: how long its spawn point waits (kind 1) */
    /* 0xA8 */ f32 tNext;          /* func_00173A68: when it spawns next */
    /* 0xAC */ s32 mode;           /* func_00173A68: 0 never, 1 within a time of an alert, 2 and 3 always */
};

#if defined(__mips__)
SLY2_OFFSET_CHECK(GUARDSPAWNER, count, 0x50);
SLY2_OFFSET_CHECK(GUARDSPAWNER, cSlot, 0x58);
SLY2_OFFSET_CHECK(GUARDSPAWNER, slots, 0x60);
SLY2_OFFSET_CHECK(GUARDSPAWNER, posLast, 0x70);
SLY2_OFFSET_CHECK(GUARDSPAWNER, offsetCount, 0x98);
SLY2_OFFSET_CHECK(GUARDSPAWNER, dtFree, 0xA0);
SLY2_OFFSET_CHECK(GUARDSPAWNER, mode, 0xAC);
SLY2_SIZE_CHECK(GUARDSPAWNPOINT, 0x1C);
SLY2_SIZE_CHECK(GUARDSPAWNSLOT, 0x30);
#endif
#endif
