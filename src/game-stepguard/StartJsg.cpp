// SPDX-License-Identifier: GPL-3.0-or-later
#include "jsg.h"

extern "C" {
void AddSeqRecordEndThread(JSG *);
void *PseqnodeNew(JSG *, int, int);
void RunSeqnode(void *);
int FIsDlEmpty__FP2DL(DL *);
void StopJsg(JSG *);
void func_001A6CA8(JSG *, int);
}

void StartJsg(JSG *pjsg, int psoSubject)
{
    if (pjsg->fRunning != 0)
        return;
    pjsg->psoSubject = psoSubject;
    pjsg->fRunning = 1;
    pjsg->fLatched = 0;
    pjsg->HandleSpliceEvent(5, 0, 0, 0, 0);
    if (pjsg->fRunning == 0)
        return;
    if (pjsg->fPendingCut != 0) {
        AddSeqRecordEndThread(pjsg);
        pjsg->fPendingCut = 0;
    }
    RunSeqnode(PseqnodeNew(pjsg, pjsg->ajsge, 0));
    if (pjsg->fRunning == 0)
        return;
    if (FIsDlEmpty__FP2DL(&pjsg->dlSeqnode) != 0) {
        StopJsg(pjsg);
        return;
    }
    unsigned grf = pjsg->grfSw;
    if (((grf ^ 1) & 1) != 0)
        grf = pjsg->pgrfentry->grf;
    if ((grf & 2) == 0) {
        func_001A6CA8(pjsg, 1);
        unsigned grf2 = pjsg->grfSw;
        if (((grf2 ^ 1) & 1) != 0)
            pjsg->pgrfentry->grf |= 2;
        else
            pjsg->grfSw = grf2 | 2;
        pjsg->fLatched = 1;
    }
}
