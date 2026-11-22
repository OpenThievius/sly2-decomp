// SPDX-License-Identifier: GPL-3.0-or-later
#include "act.h"
extern "C" {
ACT *PactNew(s32 kind);                                    /* extern */
ACT *PactNewForXf(s32 kind, ALO *palo, XF *pxf, s32 priority, s32 xfk) {
    ACT *pact;
    pact = PactNew(kind);
    pact->palo = palo;
    pact->pxf = pxf;
    pact->priority = priority;
    pact->xfk = xfk;
    return pact;
}
}
