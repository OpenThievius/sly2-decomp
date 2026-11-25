#include "bomb.h"
#include "sw.h"
extern "C" const float RO_002BC9C8;
extern "C" void InitSo(BOMB *);
extern "C" const float RO_002A4B08;

extern "C" void InitBomb(BOMB *pbomb)
{
    InitSo(pbomb);
    unsigned flags = pbomb->grfSw;
    pbomb->tDetonate = RO_002A4B08;
    pbomb->field_0x15C = RO_002BC9C8;
    pbomb->field_0x160 = RO_002BC9C8;
    pbomb->field_0x1E0 = 1;
    pbomb->field_0x150 = 0;
    pbomb->field_0x1EC = 0x100;
    pbomb->field_0x1F0 = -10;
    if ((flags ^ 1) & 1)
        pbomb->pgrfentry->grf |= 2;
    else
        pbomb->grfSw = flags | 2;
    pbomb->pbombOwner = pbomb;
}
