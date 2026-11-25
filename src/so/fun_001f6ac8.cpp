#include "geom.h"
#include "so.h"
extern "C" void func_001F2A60(SO *, GEOM *);

extern "C" void func_001F6AC8(SO *so, int alo)
{
    for (int index = 0; index < so->cgeom; index++) {
        GEOM *geom = &so->ageom[index];
        if (geom->alo == alo)
            func_001F2A60(so, geom);
    }
}
