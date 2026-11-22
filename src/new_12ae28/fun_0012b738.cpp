// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "acr.h"
extern "C" {
int IkeyFindAcrb(ACRB *, float);
int FFloatsNear__Ffff(float, float, float);
}
extern QW g_2a2dd0;
#include "ps2inline.h"
static inline int Near(float a, float b) { return FFloatsNear__Ffff(a, b, 0.0001f); }
static inline int Near3(QW p, QW q)
{
    return Near(LaneX(p), LaneX(q)) && Near(LaneYInGeneralRegister(p), LaneYInGeneralRegister(q)) &&
           Near(LaneZInGeneralRegister(p), LaneZInGeneralRegister(q));
}
extern "C" void func_0012B738(ACRB *pacrb, XF *pxf)
{
    int index = IkeyFindAcrb(pacrb, *pxf->ptMin);
    pxf->tMin = pacrb->akey[index - 1].t;
    *(VECTOR3 *)&pxf->posGoal = pacrb->akey[index - 1].pos;
    pxf->velGoal = pacrb->akey[index - 1].out;
    pxf->tMax = pacrb->akey[index].t;
    *(VECTOR3 *)&pxf->field_0xE0 = pacrb->akey[index].pos;
    *(QW *)pxf->accel = pacrb->akey[index].in;
    int ok = 0;
    int same = Near3(pxf->posGoal, pxf->field_0xE0);
    if (same) {
        int second = Near3(g_2a2dd0, pxf->velGoal);
        if (second) {
            ok = Near3(g_2a2dd0, *(QW *)pxf->accel);
        }
    }
    pxf->sub = ok ? 2 : 1;
}
