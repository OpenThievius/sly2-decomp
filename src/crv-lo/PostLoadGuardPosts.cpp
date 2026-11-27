// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "goalpost.h"
extern "C" {
extern char B_003DD490;
void PostGuardLoad(STEPGUARDPOSTS *);
LO *PloFindSwObject_thunk(char *, int, int, STEPGUARDPOSTS *);
void PostLoadGuardPosts(STEPGUARDPOSTS *pguard)
{
    int ipost = 0;
    PostGuardLoad(pguard);
    for (; ipost < pguard->cpost; ipost++) {
        POSTPAIR *ppost = &pguard->apost[ipost];
        ppost->ploA = PloFindSwObject_thunk(&B_003DD490, 4, ppost->oidA, pguard);
        ppost->pvolumeA = PloFindSwObject_thunk(&B_003DD490, 4, ppost->oidVolumeA, pguard);
        ppost->ploB = PloFindSwObject_thunk(&B_003DD490, 4, ppost->oidB, pguard);
        ppost->pvolumeB = PloFindSwObject_thunk(&B_003DD490, 4, ppost->oidVolumeB, pguard);
    }
}
}
