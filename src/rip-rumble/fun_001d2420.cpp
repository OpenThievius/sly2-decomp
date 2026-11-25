#include "types.h"
#include "ps2inline.h"
struct ELEMENT { float x, y, z, w; };
struct TABLE { u8 unknown_0x0[0xE8]; int count; u8 unknown_0xEC[8]; ELEMENT *pelements; };
struct HOLDER { u8 unknown_0x0[0x5AC]; TABLE *ptable; int field_0x5B0; };
extern "C" QW PosLoWorld(void *);
void func_001D2420(HOLDER *pholder)
{
    pholder->field_0x5B0 = 0;
    QW pos = PosLoWorld(pholder);
    for (int index = 0; index < pholder->ptable->count; index++)
        pholder->ptable->pelements[index].z = FloatFromWord(LaneWordZ(pos));
}
