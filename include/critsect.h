/* SPDX-License-Identifier: GPL-3.0-or-later */
/* CRITSECT, a re-entrant critical section on an EE semaphore: InitCritSect (0x21F028) creates the semaphore, EnterCritSect
   (0x21F060) waits on it unless the calling thread already holds it and counts the entries, LeaveCritSect (0x21F0C0) signals
   it when the count drops to 0. The GS code guards its frame swap with one (B_002DFB40: SyncVBlank file). C++ only: the three
   functions have C++ names (InitCritSect__FP8CRITSECT). */
#ifndef SLY2_CRITSECT_H
#define SLY2_CRITSECT_H
#include "types.h"

struct CRITSECT {
    /* 0x0 */ s32 cEnter; /* EnterCritSect, LeaveCritSect */
    /* 0x4 */ s32 thread; /* the holder's thread id, -1 when free: InitCritSect, EnterCritSect, LeaveCritSect */
    /* 0x8 */ s32 sema;   /* InitCritSect, EnterCritSect, LeaveCritSect */
};

void InitCritSect(CRITSECT *pcritsect);
void EnterCritSect(CRITSECT *pcritsect);
void LeaveCritSect(CRITSECT *pcritsect);

#if defined(__mips__)
typedef char check_CRITSECT_size[(sizeof(CRITSECT) == 0xC) ? 1 : -1];
#endif
#endif
