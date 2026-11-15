/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
#include "ps2inline.h"
void CalculateSinCos(float rad, float *psin, float *pcos);
extern "C" QW SetVectorSphere(float radPan, float radTilt, float sRadius)
{
    struct { QW vec; float gSinPan; float gCosPan; float gSinTilt; float gCosTilt; } l;
    CalculateSinCos(radPan, &l.gSinPan, &l.gCosPan);
    CalculateSinCos(radTilt, &l.gSinTilt, &l.gCosTilt);
    l.vec = VectorFromFloats3(l.gCosTilt * l.gCosPan * sRadius, l.gCosTilt * l.gSinPan * sRadius, l.gSinTilt * sRadius);
    return l.vec;
}
