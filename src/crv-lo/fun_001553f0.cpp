// SPDX-License-Identifier: GPL-3.0-or-later
#include "alloc.h"
#include "goalpost.h"

extern "C" {
void *PvAllocSwClearImpl__Fi(ALLOCREQ *request);
void LoadStepFromBrx(STEPGUARD *pstep, s32 brxIndex);

/* LoadGuardPosts */
void func_001553F0(STEPGUARDPOSTS *pguard, s32 brxIndex)
{
    ALLOCREQ request;

    request.cb = 0x480;
    request.cbAlign = 0x10;
    pguard->apost = (POSTPAIR *)PvAllocSwClearImpl__Fi(&request);
    LoadStepFromBrx(pguard, brxIndex);
    pguard->tickPick = 0x7FFFFFFF;
}
}
