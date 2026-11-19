// SPDX-License-Identifier: GPL-3.0-or-later
#include "vu0inline.h"
#include "sly2.h"
#include "xf.h"

extern "C" {
void GetXfLocalRateMatrix(MATRIX4 *pmat, XF *pxf);
void InvertMatrix4Affine(MATRIX4 *pmatOut, MATRIX4 *pmat);
void __ml__FRC7MATRIX4T0(MATRIX4 *pmatOut, const MATRIX4 *first, const MATRIX4 *second);
}

static inline void AddMatrix(MATRIX4 *sum, const MATRIX4 &first, const MATRIX4 &second)
{
    for (int row = 0; row < 4; row++)
        sum->row[row] = VectorAdd(first.row[row], second.row[row]);
}

extern "C" MATRIX4 *func_0022D148(MATRIX4 *pmatOut, XF *pxfFirst, XF *pxfEnd)
{
    MATRIX4 local;
    MATRIX4 rate;
    MATRIX4 sum;
    MATRIX4 product;
    MATRIX4 inverse;
    memset(pmatOut, 0, sizeof(MATRIX4));
    for (XF *pxf = pxfFirst; pxf != pxfEnd; pxf = pxf->pxfParent) {
        switch (pxf->kind) {
        case 0:
        case 3:
        case 10:
        case 12:
        case 15:
        case 19:
            break;
        default:
            GetXfLocalRateMatrix(&rate, pxf);
            local = rate;
            if (pxf->pxfParent != 0) {
                MATRIX4 *psum = &sum;
                __ml__FRC7MATRIX4T0(&product, &pxf->pxfParent->matWorld, &local);
                InvertMatrix4Affine(&inverse, &pxf->matWorld);
                __ml__FRC7MATRIX4T0(psum, &product, &inverse);
                AddMatrix(&rate, *pmatOut, *psum);
                memcpy(pmatOut, &rate, sizeof(MATRIX4));
            } else {
                MATRIX4 *psum = &sum;
                InvertMatrix4Affine(&product, &pxf->matWorld);
                __ml__FRC7MATRIX4T0(psum, &local, &product);
                AddMatrix(&rate, *pmatOut, *psum);
                memcpy(pmatOut, &rate, sizeof(MATRIX4));
            }
            break;
        }
    }
    if (pxfEnd != 0) {
        MATRIX4 *psum = &sum;
        MATRIX4 *prate = &rate;
        InvertMatrix4Affine(psum, &pxfEnd->matWorld);
        __ml__FRC7MATRIX4T0(prate, psum, pmatOut);
        memcpy(pmatOut, prate, sizeof(MATRIX4));
    }
    return pmatOut;
}
