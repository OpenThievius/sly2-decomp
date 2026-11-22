// SPDX-License-Identifier: GPL-3.0-or-later
#include "lo.h"
#include "frm.h"
extern char B_003E1518, B_003E1530;
extern "C" {
void ClearDl__FP2DL(DL *);
int FIsDlEmpty__FP2DL(DL *);
void FreeSlotheapPv(void *, void *);
void RemoveDlEntry(DL *, void *);
}
extern "C" void ClearPendingFrame__FP3FRM(FRM *frm)
{
    if (!FIsDlEmpty__FP2DL(&frm->dlBlipg)) {
        DLI iter;
        PushDli(&iter, &frm->dlBlipg);
        for (BASIC *entry = (BASIC *)PvStep(&iter); entry; entry = (BASIC *)PvStep(&iter)) {
            RemoveDlEntry(&frm->dlBlipg, entry);
            entry->Slot2();
        }
        ClearDl__FP2DL(&frm->dlBlipg);
        PopDli(&iter);
    }
    if (!FIsDlEmpty__FP2DL(&frm->dlBlip)) {
        DLI iter;
        PushDli(&iter, &frm->dlBlip);
        for (FRMBLIP *entry = (FRMBLIP *)PvStep(&iter); entry; entry = (FRMBLIP *)PvStep(&iter)) {
            if (entry->extra)
                FreeSlotheapPv(&B_003E1530, entry->extra);
            RemoveDlEntry(&frm->dlBlip, entry);
            FreeSlotheapPv(&B_003E1518, entry);
        }
        ClearDl__FP2DL(&frm->dlBlip);
        PopDli(&iter);
    }
}
