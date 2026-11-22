// SPDX-License-Identifier: GPL-3.0-or-later
#include "geom.h"
#include "so.h"

extern "C" void func_001F3900(SO *pso)
{
    for (int index = 0; index < pso->cgeom; index++) {
        GEOM *pgeom = &pso->ageom[index];
        if (!(pgeom->grf & (1UL << 50))) {
            XF *pxf = pgeom->pxf;
            pgeom->matWorld.row[0] = pxf->matWorld.row[0];
            pgeom->matWorld.row[1] = pxf->matWorld.row[1];
            pgeom->matWorld.row[2] = pxf->matWorld.row[2];
            pgeom->matWorld.row[3] = pxf->matWorld.row[3];
            pgeom->generationMat = pxf->generation;
        }
    }
}
