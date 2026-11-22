/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "lookat.h"
#include "xf.h"

QW GetXfDofValue(struct XF *pxf, struct MATRIX4 *pmat);

void func_0012CF30(struct LOOKAT *plookat, QW *ppos, s32 *pvec) {
    struct XF *pxf;

    if (ppos != 0) {
        pxf = plookat->pxf;
        *ppos = GetXfDofValue(pxf, &pxf->mat);
    }
    if (pvec != 0) {
        pvec[2] = 0;
        pvec[1] = 0;
        pvec[0] = 0;
    }
}
