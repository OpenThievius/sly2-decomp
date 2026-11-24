#include "sly2.h"
#include "tank.h"
extern "C" void ClonePo();

void CloneTank(TANK *ptank, TANK *ptankBase)
{
    ClonePo();
    if (ptank->field_0x1D0 == ptankBase)
        ptank->field_0x1D0 = ptank;
}
