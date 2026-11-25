#include "sly2.h"
struct TNFN { u8 unknown_0x0[0x70]; f32 x, y, z; };
struct TN { u8 unknown_0x0[0x118]; TNFN *pstepCur; };
extern "C" void func_00221960(TN *ptn, float g)
{
    ptn->pstepCur->x = ptn->pstepCur->y = g;
    ptn->pstepCur->z = 1.0f;
}
