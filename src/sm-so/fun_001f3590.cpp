#include "phys.h"
#include "so.h"
extern "C" void func_001F3590(SO *so)
{
    float *gravity = so->pphys->gravity;
    gravity[0] = 0.0f;
    gravity[2] = -1750.0f;
    gravity[1] = 0.0f;
    so->pphys->ctForce = 3;
    so->pphys->ctTorque = 3;
}
