// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "sw.h"
#include "so.h"
#include "dl.h"

struct WKR {
    SO *plo;
    int field4;
    int idAlo;
    int field0C;
    char pad10[0x44 - 0x10];
    int grfic;
    SO *ploAbsorbed;
    float field4C;
    DLE dle;
    char pad58[0x60 - 0x58];
} __attribute__((aligned(16)));

extern "C" {
SO *func_001A5BF0(int);
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
    SO *palo = func_001A5BF0(pwkr->idAlo);
    while (palo != 0) {
        WKR *pwkrOther = (WKR *)B_003E15C0.head;
        while (pwkrOther != 0) {
            if (pwkrOther->plo == pwkr->plo && pwkrOther->field4 == pwkr->field4 && pwkrOther->field0C == pwkr->field0C && pwkrOther->ploAbsorbed == palo)
                return 0;
            pwkrOther = (WKR *)pwkrOther->dle.next;
        }
        pwkr->grfic = GrficFromAlo(palo, pwkr->field0C);
        if (palo->FAbsorbWkr(pwkr) != 0) {
            pwkr->ploAbsorbed = palo;
            WKR *pwkrCopy = new (&B_003E15A8) WKR(*pwkr);
            pwkrCopy->field4C = g_2dded0;
            ClearDle__FP3DLE(&pwkrCopy->dle);
            AppendDlEntry(&B_003E15C0, pwkrCopy);
            if (pwkr->grfic & 0xF8) {
                aargs[0] = palo;
                aargs[1] = pwkr->plo;
                aargs[2] = pwkr;
                palo->PostMessage(0xB, aargs);
                pwkr->plo->PostMessage(0xB, aargs);
                aargs2[0] = &palo;
                aargs2[1] = &pwkr->field0C;
                pwkr->plo->HandleSpliceEvent(0xA, 1, 2, (sptr)aargs2, 0);
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
