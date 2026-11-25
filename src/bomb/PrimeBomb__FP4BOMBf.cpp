// 0x13B5C8 PrimeBomb__FP4BOMBf
#include "bomb.h"

extern "C" float g_2dded0;

void PrimeBomb(BOMB* arg0, float dt)
{
    float tDetonate = arg0->tDetonate;
    float tPrimed = g_2dded0 + dt;
    arg0->tDetonate = (tDetonate < tPrimed) ? tDetonate : tPrimed;
}
