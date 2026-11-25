#include "geom.h"
#include "so.h"
extern "C" GEOM *PpartFindAlo(SO *so, int alo)
{
    for (int index = 0; index < so->cgeom; index++) {
        if (so->ageom[index].alo == alo)
            return &so->ageom[index];
    }
    return 0;
}
