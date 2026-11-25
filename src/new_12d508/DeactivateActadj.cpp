// SPDX-License-Identifier: GPL-3.0-or-later
#include "act.h"
struct ACTADJ { u8 unknown_0x0[0x10]; ACT *pactNext; u8 unknown_0x14[8]; ACT *pactBase; };

extern "C" void DeactivateActadj(ACTADJ *pactadj)
{
    ACT *pact = pactadj->pactBase;
    if (pact != 0) {
        ACTVTENTRY *pentry = &((ACTVT *)pact->vtable)->slot2;
        pentry->fn((char *)pact + pentry->delta);
        pactadj->pactBase = 0;
    }
}
