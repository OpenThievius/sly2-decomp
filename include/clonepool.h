/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CLONEPOOL: the clone pool object of src/new_1c90d0 (ClonePool_AddLoGrfEntry slot 24, ClonePool_RemoveLoGrfEntry slot 23, and the
   lease functions PloLeaseCloneObject, PleaseFindBest, NGradeLease, ... that take it). An LO (an XFM: func_001CA788, its Init, starts it with InitXfm) with the clone set it leases from
   at 0xE0 (cloneset.h: its cpalo objects per clone, its apalo, its axf of leases). Names are ours, from what those functions do.
   C++ only. */
#ifndef SLY2_CLONEPOOL_H
#define SLY2_CLONEPOOL_H
#include "cloneset.h"

struct CLONEPOOL : LO {
    u8 unknown_0x50[0x90];
    /* 0xE0 */ CLONESET *set;      /* every lease function reads it: the set's cpalo, apalo, cclone, icloneFree, axf */
    /* 0xE4 */ s32 fixed;          /* ClonePool_AddLoGrfEntry (queues its callback while 0), NGradeLease's caller PleaseFindBest */
    /* 0xE8 */ CLONELEASE *head;   /* the lease the pool holds now: PleaseFindBest, PloLeased, func_001CB360 (walks it), ClonePool_RemoveLoGrfEntry */
};

#if defined(__mips__)
SLY2_OFFSET_CHECK(CLONEPOOL, set, 0xE0);
SLY2_OFFSET_CHECK(CLONEPOOL, head, 0xE8);
#endif
#endif
