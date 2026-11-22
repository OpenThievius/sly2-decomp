// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "so.h"
#include "geom.h"
#include "oxa.h"
extern "C" {
int FFilterOxaBasic(OXA *poxaIgnore, GEOM *pgeom);

int FFilterHitTestDefault(OXA *poxaIgnore, GEOM *pgeom) {
    if (!FFilterOxaBasic(poxaIgnore, pgeom)) return 0;
    return pgeom->pso->FIsLocked();
}
}
