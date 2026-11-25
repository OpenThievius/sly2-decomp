#include "so.h"
#include "geom.h"
extern "C" void RemoveSoGeomFromOxa(SO *, GEOM *);
extern "C" void RemoveSoGeomsFromOxa(SO *pso) {
    for (int index = 0; index < pso->cgeom; index++) {
        GEOM *pgeom = &pso->ageom[index];
        if (!(pgeom->grf & 0x8000UL << 35))
            RemoveSoGeomFromOxa(pso, pgeom);
    }
}
