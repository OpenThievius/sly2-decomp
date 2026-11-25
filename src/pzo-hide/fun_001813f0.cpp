// 0x1813F0 Chaser_SetSpeedGain
#include "pzo_hide.h"
extern "C" const float D_FLT_002BE87C;

void func_001813F0(CHASER* pchaser, float fparg0)
{
    float f0 = fparg0 * D_FLT_002BE87C;
    pchaser->speedGain = f0;
}
