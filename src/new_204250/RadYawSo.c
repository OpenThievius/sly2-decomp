/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "soview.h"
#include "xf.h"

float atan2f(float, float);

float RadYawSo(struct SOVIEW *pso) {
    struct XF *pxf = pso->pxfRoot;

    return atan2f(pxf->matWorld.mat[0][1], pxf->matWorld.mat[0][0]);
}
