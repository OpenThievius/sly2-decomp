/* SPDX-License-Identifier: GPL-3.0-or-later */
/* BOOTQ, the boot queue the title flow works through: a count of entries, sixteen 0x1C-byte entries, and the index of the
   next one to run (readers: FBootQueueHasEntries compares the two, StartBootQueue clears both, RunNextBootQueueEntry takes
   aentry[iEntryNext++]). C and C++. */
#ifndef SLY2_BOOTQ_H
#define SLY2_BOOTQ_H
#include "types.h"
/* One queued boot step: kind 0/1 a movie, 2 a transition, 3 a restart at a task oid, 5 the memory card menu. The words after kind
   are read per kind by RunNextBootQueueEntry. */
struct BOOTENTRY {
    /* 0x00 */ s32 kind;
    /* 0x04 */ s32 field_0x4;  /* kind 0 and 1: the movie */
    /* 0x08 */ s32 field_0x8;  /* kind 2: the target oid pointer */
    /* 0x0C */ s32 field_0xC;
    /* 0x10 */ s32 field_0x10;
    /* 0x14 */ s32 field_0x14; /* kind 3: restart arguments */
    /* 0x18 */ s32 field_0x18;
};
struct BOOTQ {
    /* 0x000 */ s32 cEntry;
    /* 0x004 */ struct BOOTENTRY aentry[16]; /* readers: RunNextBootQueueEntry takes aentry[iEntryNext++]; PentryAddBootQueue takes the next free one (a static dummy when full) and stores kind */
    /* 0x1C4 */ s32 iEntryNext;
};
#endif
