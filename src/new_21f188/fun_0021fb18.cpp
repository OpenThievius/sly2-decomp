// SPDX-License-Identifier: GPL-3.0-or-later
#include "geom.h"
#include "oxa.h"

extern "C" {
int FFilterOxa(OXA *poxaIgnore, GEOM *pgeom);
int FIsBasicDerivedFrom(void *pbasic, int cid);

int func_0021FB18(OXA *poxaIgnore, GEOM *pgeom) {
    if (FIsBasicDerivedFrom(pgeom->pso, 0x59) != 0) {
        return 1;
    }
    return FFilterOxa(poxaIgnore, pgeom);
}
}
