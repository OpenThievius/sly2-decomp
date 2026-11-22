// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "lo.h"
#include "rsmg.h"
extern "C" int CploFindSwObjects_thunk(void *, int, int, int, int, void **);
extern "C" int FIsBasicDerivedFrom(void *, int);
extern "C" BASIC *PsmaFindAlo(void *, int);
extern "C" void SubscribeLoObject(void *, void *);
extern "C" void SnapSmaToGoal(void *, int);
extern "C" void SetSmaGoal__FP3SMA3OID(void *, int);
void TriggerRsmgEntry(void *sw, RSMG *prsmg, int context, int flags, void *subscriber, void **out)
{
    void *roots[4];
    if (out)
        *out = 0;
    if (CploFindSwObjects_thunk(sw, 0x204, prsmg->oidRoot, context, 1, roots) != 1)
        return;
    if (!FIsBasicDerivedFrom(roots[0], 0x30))
        return;
    BASIC *psma = PsmaFindAlo(roots[0], prsmg->oidSM);
    if (!psma)
        return;
    int oidGoal = (flags & 1) ? prsmg->oidTriggerGoal : prsmg->oidUntriggerGoal;
    if (oidGoal == -1)
        return;
    if (subscriber) {
        *out = psma;
        psma->OnAdd();
        SubscribeLoObject(psma, subscriber);
    }
    if (flags & 2)
        SnapSmaToGoal(psma, oidGoal);
    else
        SetSmaGoal__FP3SMA3OID(psma, oidGoal);
}
