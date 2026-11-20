// SPDX-License-Identifier: GPL-3.0-or-later
#include "dl.h"
struct VT { char pad[0x10]; short delta; short index; void (*fn)(void *); };
struct FRM { char pad[0x34]; DL dlA; DL dlB; };
struct ENTRY { char pad[0xC]; VT *vptr; char pad2[0x1088 - 0x10]; void *extra; };
extern char B_003E1518, B_003E1530;
extern "C" {
void ClearDl__FP2DL(DL *);
int FIsDlEmpty__FP2DL(DL *);
void FreeSlotheapPv(void *, void *);
void RemoveDlEntry(DL *, void *);
}
extern "C" void ClearPendingFrame__FP3FRM(FRM *frm)
{
    if (!FIsDlEmpty__FP2DL(&frm->dlA)) {
        DLI iter;
        PushDli(&iter, &frm->dlA);
        for (ENTRY *entry = (ENTRY *)PvStep(&iter); entry; entry = (ENTRY *)PvStep(&iter)) {
            RemoveDlEntry(&frm->dlA, entry);
            entry->vptr->fn((char *)entry + entry->vptr->delta);
        }
        ClearDl__FP2DL(&frm->dlA);
        PopDli(&iter);
    }
    if (!FIsDlEmpty__FP2DL(&frm->dlB)) {
        DLI iter;
        PushDli(&iter, &frm->dlB);
        for (ENTRY *entry = (ENTRY *)PvStep(&iter); entry; entry = (ENTRY *)PvStep(&iter)) {
            if (entry->extra)
                FreeSlotheapPv(&B_003E1530, entry->extra);
            RemoveDlEntry(&frm->dlB, entry);
            FreeSlotheapPv(&B_003E1518, entry);
        }
        ClearDl__FP2DL(&frm->dlB);
        PopDli(&iter);
    }
}
