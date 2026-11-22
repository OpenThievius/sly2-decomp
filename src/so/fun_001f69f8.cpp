// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
#include "geom.h"
extern "C" {
void func_001F69F8(SO *pso, s32 oid) {
    for (s32 iglob = 0; iglob < pso->field_0xB8; iglob++) {
        GLOBENTRY *pglob = &pso->field_0xC0[iglob];
        if (pglob->oid == oid) {
            GEOM *pgeom = pglob->pgeom;
            pglob->grf |= 0x800;
            if (pgeom != 0) {
                pgeom->grf |= (0x8000UL << 0x23);
            }
        }
    }
}
}
