// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "acr.h"
extern "C" {
int FFloatsNear__Ffff(float, float, float);
int func_0012C708(ACRAXIS *, float);
}
extern QW g_2a2dd0;
#include "ps2inline.h"
static inline int Near(float a, float b) { return FFloatsNear__Ffff(a, b, 0.0001f); }
static inline int Near3(QW p, QW q)
{
    return Near(LaneX(p), LaneX(q)) && Near(LaneYInGeneralRegister(p), LaneYInGeneralRegister(q)) &&
           Near(LaneZInGeneralRegister(p), LaneZInGeneralRegister(q));
}
extern "C" void func_0012C768(ACRAXIS *pacr, XF *pxf) {
    int index;
    if (pacr->ckey != 0) {
        index = func_0012C708(pacr, *pxf->ptMin);
        pxf->tMin = pacr->atime[index - 1];
        pxf->tMax = pacr->atime[index];
    } else {
        pxf->ptMin = &pxf->tMin;
        pxf->tMax = 1.0f;
        pxf->ptMax = &pxf->tMax;
        pxf->tMin = 0;
    }
    unsigned int axis = 0;
    int offset = index * 8;
    int previousOffset = offset - 8;
    float *outD = (float *)pxf->accel;
    float *outC = (float *)&pxf->field_0xE0;
    float *outB = (float *)&pxf->velGoal;
    float *outA = (float *)&pxf->posGoal;
    do {
        char *base = (char *)pacr->aaxis[axis];
        if (base != 0) {
            char *previous = base + previousOffset;
            char *current = base + offset;
            *outA = *(float *)previous;
            *outB = *(float *)(previous + 4);
            *outC = *(float *)current;
            *outD = *(float *)(current + 4);
        } else {
            *outA = pacr->adefault[axis];
            *(int *)outB = 0;
            *outC = pacr->adefault[axis];
            *(int *)outD = 0;
        }
        outD++;
        outC++;
        outB++;
        outA++;
        axis++;
    } while (axis < 3U);
    int ok = 0;
    if (Near3(pxf->posGoal, pxf->field_0xE0)) {
        if (Near3(g_2a2dd0, pxf->velGoal)) {
            ok = Near3(g_2a2dd0, *(QW *)pxf->accel);
        }
    }
    pxf->sub = ok ? 2 : 1;
}
