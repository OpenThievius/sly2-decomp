// SPDX-License-Identifier: GPL-3.0-or-later
#include "act.h"
struct ACTADJ { ACT act; ACT *pactBase; };
extern "C" void InvalidateXfSegment(void *, void *);
extern "C" void ReselectActadj(ACTADJ *pactadj) {
    if (pactadj->pactBase != pactadj->act.pactNext) {
        InvalidateXfSegment(pactadj->act.palo, pactadj->act.pxf);
        ACT *pactOld = pactadj->pactBase;
        if (pactOld != 0) {
            CallActSlot2(pactOld);
        }
        ACT *pactNew = pactadj->act.pactNext;
        pactadj->pactBase = pactNew;
        if (pactNew != 0) {
            CallActSlot1(pactNew);
        }
    }
}
