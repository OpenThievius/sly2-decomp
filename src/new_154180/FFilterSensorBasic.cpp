#include "sly2.h"
#include "so.h"
#include "geom.h"
extern "C" int FFilterOxaBasic(void* pvSensor, GEOM* pgeom);
extern "C" int CidGetBasic(BASIC* pbasic);
extern "C" int FFilterSensorBasic(void* pvSensor, GEOM* pgeom);
int FFilterSensorBasic(void* pvSensor, GEOM* pgeom)
{
    if (!FFilterOxaBasic(pvSensor, pgeom))
        return 0;
    return CidGetBasic(pgeom->pso) == 0x31;
}
