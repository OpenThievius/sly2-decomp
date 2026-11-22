// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
extern "C" {
/* one 0xB0-byte element of SO::ageom, as func_001F6BC8 reads it (GEOM, geom.h, does not name these words) */
struct GEOMTAG {
    u8 unknown_0x0[0xC];
    /* 0xC */ s32 id;
    u8 unknown_0x10[8];
    /* 0x18 */ s32 value;
    u8 unknown_0x1C[0x94];
};
void func_001F6BC8(SO *pso, s32 id, s32 value) {
    for (s32 igeom = 0; igeom < pso->cgeom; igeom++) {
        GEOMTAG *pgeom = &((GEOMTAG *)pso->ageom)[igeom];
        if (pgeom->id == id) {
            pgeom->value = value;
        }
    }
}
}
