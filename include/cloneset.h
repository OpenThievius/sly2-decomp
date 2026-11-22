/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CLONESET, one entry of the world's table of clone sets (SW::acloneset, SW::ccloneset in sw.h): 0x6C bytes, the stride
   InitCloneSets and InstantiateClone step by. Field names and meanings are ours, from those two readers: a set holds
   `cpalo` objects per clone (`apalo`, indexed clone * cpalo + object), `cclone` clones of which the first `icloneFree`
   are leased out, and `aoidClone` is the object ids InstantiateClone hands to each clone. C++ only. */
#ifndef SLY2_CLONESET_H
#define SLY2_CLONESET_H
#include "lo.h"
#include "sly2.h"

/* one clone's 0x50-byte lease record (CLONESET::axf is an array of them, indexed clone - icloneFree): the first four words are the
   lease's bookkeeping (zeroed by PvAllocSwClear), then InitCloneSets writes an identity matrix. IcloneFromLease divides a pointer
   difference by its size, PleaseFromIclone multiplies by it. */
struct CLONEPOOL;
struct CLONELEASE {
    /* 0x00 */ struct CLONEPOOL *ppool;  /* the pool that holds the lease (PpoolFromLoClone returns it); NGradeLease: 0 means free (grade 4) */
    /* 0x04 */ struct CLONELEASE *next; /* func_001CB360 walks the pool's leases through it */
    /* 0x08 */ s32 pinned;            /* LockLeaseOfPlo sets 1, UnlockLeaseOfPlo clears it; NGradeLease: grade 0 while set */
    u8 unknown_0xC[0x4];
    /* 0x10 */ f32 mat[16];           /* InitCloneSets: identity */
};

/* one object's 0x40-byte world matrix and position kept at CLONESET::amat: InitCloneSets copies PosLoWorld into pos and the
   three rows of PmatLoWorld, then normalizes the rows */
struct CLONEMAT {
    VECTOR pos;
    VECTOR row[3];
};

struct CLONESET {
    /* 0x00 */ s32 cpalo;           /* InitCloneSets, InstantiateClone: objects per clone */
    /* 0x04 */ struct LO **apalo;   /* the same */
    /* 0x08 */ s32 cclone;          /* InitCloneSets */
    /* 0x0C */ s32 icloneFree;      /* InitCloneSets, InstantiateClone */
    /* 0x10 */ s32 field_0x10;     /* func_001CB770 searches the sets for the one holding a given value here */
    /* 0x14 */ s32 value;           /* InitCloneSets */
    /* 0x18 */ s32 *aoidClone;      /* InitCloneSets, InstantiateClone */
    u8 unknown_0x1C[0x48];
    /* 0x64 */ struct CLONEMAT *amat;          /* InitCloneSets: matrices, 0x10-aligned */
    /* 0x68 */ struct CLONELEASE *axf;           /* InitCloneSets: transforms, 0x10-aligned */
};

#if defined(__mips__)
SLY2_SIZE_CHECK(CLONESET, 0x6C);
SLY2_OFFSET_CHECK(CLONESET, apalo, 0x04);
SLY2_OFFSET_CHECK(CLONESET, icloneFree, 0x0C);
SLY2_OFFSET_CHECK(CLONESET, aoidClone, 0x18);
SLY2_OFFSET_CHECK(CLONESET, amat, 0x64);
SLY2_OFFSET_CHECK(CLONESET, axf, 0x68);
#endif
#endif
