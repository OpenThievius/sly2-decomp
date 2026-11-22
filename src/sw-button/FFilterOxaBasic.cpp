// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "so.h"
#include "geom.h"
#include "oxa.h"
extern "C" {

s32 FFilterOxaBasic(OXA *poxaIgnore, GEOM *pgeom) {
    s32 fAccept;
    OXA *poxa;

    fAccept = 0;
    if (!(pgeom->grf & (0x8000L << 0x21))) {
        poxa = pgeom->pso->poxa;
        if (!(poxa->grf & 4)) {
            fAccept = poxa != poxaIgnore;
        }
    }
    return fAccept;
}
}
