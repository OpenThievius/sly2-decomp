#include "so.h"
#include "geom.h"
extern "C" void AddSoGeomToOxa(SO *, GEOM *);
extern "C" void AddSoGeomsToOxa(SO *pso) {
    for (int index = 0; index < pso->cgeom; index++) {
        GEOM *pgeom = &pso->ageom[index];
        if (!(pgeom->grf & 0x8000UL << 35))
            AddSoGeomToOxa(pso, pgeom);
    }
}
