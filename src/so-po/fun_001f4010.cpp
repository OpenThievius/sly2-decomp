// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "so.h"
#include "xf.h"
#include "sw.h"
extern SW B_003DD490;
extern "C" {
MATRIX4 __ml__FRC7MATRIX4T0(const MATRIX4 &, const MATRIX4 &);
void RefreshAloIkLimbLengths(SO *);
}

void func_001F4010(SO *pso, const MATRIX4 &other)
{
    XF *pxf = pso->axf;
    pxf->mat = __ml__FRC7MATRIX4T0(other, pxf->mat);
    int generation = ++B_003DD490.generation;
    pso->axf->generation = generation;
    pso->UpdateXfWorldHierarchy();
    RefreshAloIkLimbLengths(pso);
}
