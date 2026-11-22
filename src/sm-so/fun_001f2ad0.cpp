// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
#include "geom.h"
extern "C" {
void RemoveSoGeomFromOxa(SO *, GEOM *);
void func_001F2AD0(SO *pso, GEOM *pgeom) {
    u64 flag = 1UL << 50;
    u64 grf = pgeom->grf;
    if (!(grf & flag)) {
        pgeom->grf = grf | flag;
        s64 bit = (pso->grfo >> 0x3C) & 1;
        if (bit) {
            RemoveSoGeomFromOxa(pso, pgeom);
        }
    }
}
}
