// SPDX-License-Identifier: GPL-3.0-or-later
#include "blip.h"
extern "C" void *PvAllocSlotheapImpl(SLOTHEAP *);
extern "C" void FreeSlotheapPv(SLOTHEAP *, void *);
extern "C" void AppendDlEntry(DL *, void *);
extern "C" BLIP *PblipNew__FP5BLIPG(SW *psw, BLIPG *pblipg)
{
    BLIP *pblip = (BLIP *)PvAllocSlotheapImpl(&psw->slotheapBlip);
    if (pblip == 0)
        return 0;
    if (pblipg->mode == 2) {
        void *psp = PvAllocSlotheapImpl(&psw->slotheapBlipSp);
        pblip->psp = psp;
        if (psp == 0) {
            FreeSlotheapPv(&psw->slotheapBlip, pblip);
            return 0;
        }
    }
    pblip->pblipg = pblipg;
    AppendDlEntry(&pblipg->dlBlips, pblip);
    return pblip;
}
