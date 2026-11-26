// SPDX-License-Identifier: GPL-3.0-or-later
#include "geom.h"
#include "so.h"
extern "C" {
void func_001F6BC8(SO *pso, s32 id, s32 value) {
    for (s32 igeom = 0; igeom < pso->cgeom; igeom++) {
        GEOM *pgeom = &pso->ageom[igeom];
        if (pgeom->alo == id) {
            pgeom->grftak = value;
        }
    }
}
}
