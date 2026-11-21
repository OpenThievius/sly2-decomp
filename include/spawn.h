/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SPAWN, a spawn point: class 0x2A of retail's class table, derived from LO (include/lo.h). The fields are read by its own
   functions (PloFindSpawn, ActivateSpawn, Spawn_AddRsmg, Spawn_AddTask: the PloFindSpawn file, 0x227FE8). C++ only. */
#ifndef SLY2_SPAWN_H
#define SLY2_SPAWN_H
#include "lo.h"

/* A spawn point: class 0x2A. Its own id at 0x18, its resume messages and task requests (a count and four entries each),
   links between objects, and the ids of the spawn groups it answers to from 0x16C. */
struct SPAWNLINK {
    int oidObject;  /* ActivateSpawn: the object that takes its position from the other */
    int oidSource;
};

struct SPAWN : LO {
    u8 unknown_0x50[0xE0 - 0x50];
    /* 0x0E0 */ int crsmg;           /* Spawn_AddRsmg, ActivateSpawn */
    /* 0x0E4 */ u8 arsmg[0x40];      /* four entries */
    /* 0x124 */ int ctask;           /* Spawn_AddTask, ActivateSpawn */
    /* 0x128 */ u8 atask[0x20];      /* four entries */
    /* 0x148 */ int clink;           /* ActivateSpawn */
    /* 0x14C */ SPAWNLINK alink[4];  /* ActivateSpawn */
    /* 0x16C */ int coid;            /* PloFindSpawn */
    /* 0x170 */ int aoid[1];         /* PloFindSpawn */
};

#if defined(__mips__)
SLY2_OFFSET_CHECK(SPAWN, crsmg, 0xE0);
SLY2_OFFSET_CHECK(SPAWN, clink, 0x148);
SLY2_OFFSET_CHECK(SPAWN, coid, 0x16C);
#endif
#endif
