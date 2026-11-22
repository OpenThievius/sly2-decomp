/* SPDX-License-Identifier: GPL-3.0-or-later */
/* BOOTQ, the boot queue the title flow works through: a count of entries, sixteen 0x1C-byte entries, and the index of the
   next one to run (readers: FBootQueueHasEntries compares the two, StartBootQueue clears both, RunNextBootQueueEntry takes
   aentry[iEntryNext++]). C and C++. */
#ifndef SLY2_BOOTQ_H
#define SLY2_BOOTQ_H
#include "types.h"
struct BOOTQ {
    /* 0x000 */ s32 cEntry;
    u8 unknown_0x4[0x1C0];
    /* 0x1C4 */ s32 iEntryNext;
};
#endif
