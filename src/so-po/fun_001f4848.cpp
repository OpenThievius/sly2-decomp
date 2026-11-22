// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
#include "xf.h"

extern "C" {
void ConvertXfVec(XF *pxfParent, XF *pxfRoot, QW vec);

void func_001F4848(SO *pso) {
    XF *pxf = pso->pxfLinear;
    ConvertXfVec(pxf->pxfParent, pso->pxfRoot, pxf->vel);
}
}
