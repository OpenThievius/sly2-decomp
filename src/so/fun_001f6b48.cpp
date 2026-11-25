#include "geom.h"
#include "so.h"
extern "C" void func_001F2AD0(SO *, GEOM *);

extern "C" void func_001F6B48(SO *so, int alo)
{
    for (int index = 0; index < so->cgeom; index++) {
        GEOM *geom = &so->ageom[index];
        if (geom->alo == alo)
            func_001F2AD0(so, geom);
    }
}
