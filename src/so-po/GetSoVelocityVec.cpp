// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
#include "xf.h"

extern "C" {
QW VelocityXfAtPos(XF *pxf, int arg1, QW pos);
extern QW g_2a2dd0;

QW GetSoVelocityVec(SO *pso) {
    XF *pxf = pso->pxfLinear;
    if (pxf == 0 || pxf->dof != 1) {
        return g_2a2dd0;
    }
    return VelocityXfAtPos(pxf, 0, pxf->matWorld.row[3]);
}
}
