#include "carrypart.h"
extern "C" void func_001CC1F8(CARRYPART *carry, float u, QW pos, void *unused, float *out);
extern "C" float Carry_SDistEndCurves(CARRYPROBE *pprobe, float u)
{
    float dist;
    func_001CC1F8(pprobe->pcarry, u, pprobe->posFlat, 0, &dist);
    return dist;
}
