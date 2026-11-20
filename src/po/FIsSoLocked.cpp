#include "phys.h"
#include "so.h"
extern "C" int FIsSoLocked(SO *so)
{
    int result = 0;
    PHYS *phys = so->pphys;
    if (phys == 0 || (phys->ctForce == 3 && phys->ctTorque == 3))
        result = 1;
    return result;
}
