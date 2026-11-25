#include "so.h"
#include "oxa.h"
#include "geom.h"
extern "C" int IMax(int, int);
int FFilterOxa(OXA *ignore, GEOM *geom)
{
    OXA *oxa = geom->pso->poxa;
    if (geom->grf & 0x1000000000000UL) return 0;
    if (oxa->grf & 4) return 0;
    if (oxa == ignore) return 0;
    {
        int x = ignore->owner->FIgnoreIntersection(oxa->owner);
        int y = oxa->owner->FIgnoreIntersection(ignore->owner);
        int k = IMax(x, y);
        return k != 1 && k != 3;
    }
}
