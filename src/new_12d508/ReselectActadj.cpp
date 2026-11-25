// SPDX-License-Identifier: GPL-3.0-or-later
#include "act.h"
struct ACTADJ { ACT act; ACT *pactBase; };
extern "C" void InvalidateXfSegment(void *, void *);
extern "C" void ReselectActadj(ACTADJ *pactadj) {
    if (pactadj->pactBase != pactadj->act.pactNext) {
        InvalidateXfSegment(pactadj->act.palo, pactadj->act.pxf);
        ACT *pactOld = pactadj->pactBase;
        if (pactOld != 0) {
            ACTVTENTRY *pentry = &((ACTVT *)pactOld->vtable)->slot2;
            pentry->fn((char *)pactOld + pentry->delta);
        }
        ACT *pactNew = pactadj->act.pactNext;
        pactadj->pactBase = pactNew;
        if (pactNew != 0) {
            ACTVTENTRY *pentry = &((ACTVT *)pactNew->vtable)->slot1;
            pentry->fn((char *)pactNew + pentry->delta);
        }
    }
}
