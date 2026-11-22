/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "geom.h"

void TransformGeom(struct MATRIX4 *pmatWorld, u8 *pblock78, u8 *pblock90);
void func_001F4BF8(struct SO *pso);

void func_001F38A8(struct GEOM *pgeom) {
    struct XF *pxf = pgeom->pxf;
    if (pgeom->generationBound != pxf->generation) {
        TransformGeom(&pxf->matWorld, pgeom->field_0x78, pgeom->field_0x90);
        pgeom->generationBound = pgeom->pxf->generation;
        func_001F4BF8(pgeom->pso);
    }
}
