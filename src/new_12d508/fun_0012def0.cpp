// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "act.h"

/* an act that holds its transform relative to another one (func_0012DDB0 creates it, kind 6) */
struct ACTREL {
    /* 0x00 */ ACT act;
    /* 0x1C */ XF *pxfTarget;
    /* 0x20 */ MATRIX4 mat;
};

extern "C" MATRIX4 InvertMatrix4Affine(const MATRIX4 *);
extern "C" QW GetXfDofValue(XF *, MATRIX4);
extern QW g_2a2dd0;
MATRIX4 operator*(const MATRIX4 &, const MATRIX4 &);

extern "C" void func_0012DEF0(ACTREL *pact)
{
    MATRIX4 mat;
    XF *pxfParent = pact->act.pxf->pxfParent;
    if (pxfParent != 0) {
        mat = InvertMatrix4Affine(&pxfParent->matWorld) * pact->pxfTarget->matWorld * pact->mat;
    } else {
        mat = pact->pxfTarget->matWorld * pact->mat;
    }
    XF *pxf = pact->act.pxf;
    pxf->posGoal = GetXfDofValue(pxf, mat);
    pact->act.pxf->velGoal = g_2a2dd0;
    pact->act.pxf->sub = 3;
}
