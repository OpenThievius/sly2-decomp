/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "xf.h"

struct VECTOR3 { f32 x, y, z; };

/* The source of the goal position: three floats at 4. */
struct XFSOURCE {
    u8 unknown_0x0[0x4];
    /* 0x4 */ VECTOR3 pos; /* func_0012B520 */
};

extern "C" void func_0012B520(XFSOURCE *psrc, XF *pxf)
{
    pxf->sub = 2;
    s32 *pvelGoal = (s32 *)&pxf->velGoal;
    pxf->tMax = 1.0f;
    s32 *paccel = pxf->accel;
    pxf->ptMin = &pxf->tMin;
    pxf->ptMax = &pxf->tMax;
    pxf->tMin = 0;
    *(VECTOR3 *)&pxf->posGoal = psrc->pos;
    *(QW *)pxf->unknown_0xE0 = pxf->posGoal;
    pvelGoal[2] = 0;
    pvelGoal[1] = 0;
    pvelGoal[0] = 0;
    paccel[2] = 0;
    paccel[1] = 0;
    paccel[0] = 0;
}
