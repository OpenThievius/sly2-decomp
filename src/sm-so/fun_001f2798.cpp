#include "sly2.h"
#include "so.h"
#include "phys.h"
extern "C" SO *func_001F2798(SO *pso) {
    SO *result = 0;
    for (; pso != 0; pso = result->psoParent) {
        result = pso;
        PHYS *pphys = pso->pphys;
        if (pphys != 0 && !(pphys->ctForce == 3 && pphys->ctTorque == pphys->ctForce))
            break;
        if (result->grfso & (u64)0x8000 << 19)
            break;
    }
    return result;
}
