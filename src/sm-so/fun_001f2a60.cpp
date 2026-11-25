#include "sly2.h"
#include "so.h"
#include "geom.h"
extern "C" void AddSoGeomToOxa(SO *, GEOM *);
extern "C" void func_001F2A60(SO *pso, GEOM *pgeom) {
    u64 grf = pgeom->grf;
    if (grf & (0x8000UL << 35)) {
        pgeom->grf = grf & ~(0x8000UL << 35);
        if ((int)(pso->grfo >> 0x3C) & 1) {
            AddSoGeomToOxa(pso, pgeom);
        }
    }
}
