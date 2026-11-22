// SPDX-License-Identifier: GPL-3.0-or-later
#include "act.h"
#include "xf.h"

/* an act that holds its transform relative to another one (kind 6; func_0012DEF0 reads it) */
struct ACTREL {
    ACT act;
    /* 0x1C */ XF *pxfTarget;
    /* 0x20 */ MATRIX4 mat;
};

extern "C" ACT *PactNewForXf(int kind, ALO *palo, XF *pxf, int priority, int xfk);
extern "C" void InsertXfAct(ALO *, XF *, ACT *);

ACTREL *func_0012DDB0(ALO *palo, XF *pxf, int priority, int xfk, XF *pxfTarget, MATRIX4 *pmat)
{
    ACTREL *pact = (ACTREL *)PactNewForXf(6, palo, pxf, priority, xfk);
    pact->pxfTarget = pxfTarget;
    pact->mat = *pmat;
    InsertXfAct(palo, pxf, &pact->act);
    return pact;
}
