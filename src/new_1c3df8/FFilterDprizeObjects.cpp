// SPDX-License-Identifier: GPL-3.0-or-later
#include "geom.h"
#include "so.h"
#include "oxa.h"

extern "C" {
int FIsBasicDerivedFrom(void *, int);

/* a sensor filter: GEOM bit 48 rejects the shape, an owner of class 0x32 or 0x4F is not taken */
int FFilterDprizeObjects(void *psensor, GEOM *pgeom) {
    if (pgeom->grf & (1UL << 48)) {
        return 0;
    }
    SO *psoOwner = pgeom->pso->poxa->owner;
    /* the two goto exits are what keeps retail's branch layout (plain returns or an if/else chain score 5 and 14) */
    int fTaken;
    if (FIsBasicDerivedFrom(psoOwner, 0x32) != 0) {
        fTaken = 0;
        goto done;
    }
    if (FIsBasicDerivedFrom(psoOwner, 0x4F) != 0) {
        return 0;
    }
    fTaken = 1;
    goto done;
done:
    return fTaken;
}
}
