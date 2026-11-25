#include "sly2.h"
#include "lo.h"
struct PLO : LO {
    u8 unknown_0x50[4];
    s32 unk54;
    u8 unknown_0x58[8];
    f32 unk60;
    f32 unk64;
    u8 unknown_0x68[4];
    s32 unk6c;
};
struct LEVEL { u8 unknown_0x0[0x3E60]; PLO *plo; };
extern "C" PLO *PloNew(int, int, int, int);

void func_0020E338(LEVEL *plevel)
{
    plevel->plo = PloNew(0x74, 0, -1, -1);
    plevel->plo->unk60 = 0.1f;
    plevel->plo->unk64 = 0.25f;
    plevel->plo->unk54 = 0x80200000;
    plevel->plo->unk6c = 1;
    plevel->plo->Remove();
}
