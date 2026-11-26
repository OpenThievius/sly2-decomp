#include "types.h"
#include "oxa.h"
#include "geom.h"
#include "so.h"
#include "guard.h"
extern "C" int FIsBasicDerivedFrom(void *, int);
int FFilterSensorSight(SENSOR *sensor, GEOM *geom)
{
    if ((geom->grf & (1UL << 48)) != 0)
        return 0;
    SO *pso = geom->pso;
    if ((pso->poxa->grf & 4) != 0)
        return 0;
    if (pso->proot == sensor->proot)
        return 0;
    SO *pobject = pso;
    while (pobject != 0 && !FIsBasicDerivedFrom(pobject, 0x33))
        pobject = pobject->psoParent;
    return pobject == 0;
}
