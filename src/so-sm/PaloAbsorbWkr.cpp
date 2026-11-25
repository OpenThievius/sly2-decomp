// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "sw.h"
#include "so.h"
#include "dl.h"
#include "wkr.h"


extern "C" {
SO *func_001A5BF0(LO *);
int GrficFromAlo(SO *, int);
void *PvAllocSlotheapImpl(SLOTHEAP *);
void AppendDlEntry(DL *, void *);
void ClearDle__FP3DLE(DLE *);
extern SLOTHEAP B_003E15A8;
extern DL B_003E15C0;
extern float g_2dded0;

}
inline void *operator new(unsigned int cb, SLOTHEAP *pslotheap)
{
    return PvAllocSlotheapImpl(pslotheap);
}
extern "C" {
SO *PaloAbsorbWkr(WKR *pwkr)
{
    VECTOR vecUnused; // frame: retail has an untouched 16-byte slot at sp+0
    void *aargs[3];
    void *aargs2[2];
    SO *palo = func_001A5BF0(pwkr->ploTarget);
    while (palo != 0) {
        WKR *pwkrOther = (WKR *)B_003E15C0.head;
        while (pwkrOther != 0) {
            if (pwkrOther->psoSource == pwkr->psoSource && pwkrOther->ppartSource == pwkr->ppartSource && pwkrOther->grftak == pwkr->grftak && pwkrOther->psoAbsorbed == palo)
                return 0;
            pwkrOther = (WKR *)pwkrOther->dle.next;
        }
        pwkr->flags = GrficFromAlo(palo, pwkr->grftak);
        if (palo->FAbsorbWkr(pwkr) != 0) {
            pwkr->psoAbsorbed = palo;
            WKR *pwkrCopy = new (&B_003E15A8) WKR(*pwkr);
            pwkrCopy->tAbsorb = g_2dded0;
            ClearDle__FP3DLE(&pwkrCopy->dle);
            AppendDlEntry(&B_003E15C0, pwkrCopy);
            if (pwkr->flags & 0xF8) {
                aargs[0] = palo;
                aargs[1] = pwkr->psoSource;
                aargs[2] = pwkr;
                palo->PostMessage(0xB, aargs);
                pwkr->psoSource->PostMessage(0xB, aargs);
                aargs2[0] = &palo;
                aargs2[1] = &pwkr->grftak;
                pwkr->psoSource->HandleSpliceEvent(0xA, 1, 2, (sptr)aargs2, 0);
                aargs2[0] = pwkr;
                palo->HandleSpliceEvent(0xB, 1, 2, (sptr)aargs2, 0);
            }
            return palo;
        }
        palo = palo->psoParent;
    }
    return 0;
}
}
