// SPDX-License-Identifier: GPL-3.0-or-later
#include "jsg.h"

extern "C" {
void StopSeqnode(void *);
void func_001E0120(JSG *);
void func_001A6CA8(JSG *, int);
}

// Retail reads the list's ibDle once (lw v0,8(a0)) and takes the first node
// through the iterator's own cursor, which starts at the list head: the loop
// is the PvStep-first form of OnRipgRemove (src/rip/), with no separate
// "first" helper re-reading pdl->ibDle.
void StopJsg(JSG *pjsg)
{
    if (pjsg->fRunning == 0)
        return;
    pjsg->psoSubject = 0;
    pjsg->tRun = 0.0f;
    pjsg->fRunning = 0;
    DLI dli;
    PushDli(&dli, &pjsg->dlSeqnode);
    void *pseqnode;
    for (pseqnode = PvStep(&dli); pseqnode != 0; pseqnode = PvStep(&dli))
        StopSeqnode(pseqnode);
    func_001E0120(pjsg);
    if (pjsg->fLatched != 0) {
        func_001A6CA8(pjsg, 2);
        unsigned grf = pjsg->grfSw;
        if (((grf ^ 1) & 1) != 0)
            pjsg->pgrfentry->grf = (int)pjsg->pgrfentry->grf & -3;
        else
            pjsg->grfSw = (int)grf & -3;
    }
    pjsg->HandleSpliceEvent(6, 0, 0, 0, 0);
    PopDli(&dli);
}
