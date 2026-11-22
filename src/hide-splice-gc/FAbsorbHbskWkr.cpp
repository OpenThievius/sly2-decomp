// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "hbsk.h"
#include "jt.h"
extern "C" int FAbsorbSoWkr(SO *, WKR *);
extern "C" char B_003DD490;
extern "C" QW PosLoWorld(HBSK *);
extern "C" void SpawnSwHitFx(void *, int, QW, HBSK *);
extern "C" void SetBinocState(void *, int);
extern "C" void SetHbskHbsks(HBSK *, int);
int FAbsorbHbskWkr(HBSK *phbsk, WKR *pwkr)
{
    if (FAbsorbSoWkr(phbsk, pwkr) == 0)
        return 0;
    if (phbsk->hbsks != 3) {
        if ((pwkr->flags & 8) != 0) {
            SpawnSwHitFx(&B_003DD490, 0, PosLoWorld(phbsk), phbsk);
            JT *pjt = phbsk->pjt;
            if (pjt != 0) {
                SetBinocState(pjt->PvBinoc(), -1);
                JT *pjt2 = phbsk->pjt;
                pjt2->SetMode(0);
            }
            SetHbskHbsks(phbsk, 3);
            void *args[2];
            args[0] = pwkr;
            args[1] = &pwkr->grftak;
            phbsk->HandleSpliceEvent(0xB, 0, 2, (int)args, 0);
        }
    }
    return 1;
}
