#include "shd.h"
#include "types.h"
struct GIFS { u8 unknown_0x0[0x30]; };
void *memset(void *, int, unsigned int);
extern "C" s64 func_001EA6C8(TEX *, int, int);
extern "C" void PackAD__4GIFSll(GIFS *, s64, s64);
struct TEX1 { u64 lcm : 1; u64 unknown_bits1 : 4; u64 mmag : 1; u64 mmin : 3; };
struct CLAMP { u64 wms : 2; u64 wmt : 2; };
extern "C" void func_001EA750(TEX *pref, int pass, GIFS *pgifs)
{
    TEX1 tex1;
    CLAMP clamp;
    SHD *pmat = pref->owner;
    for (int itex = pmat->cframe - 1; itex >= 0; itex--)
        PackAD__4GIFSll(pgifs, 6, func_001EA6C8(pref, itex, pass));
    memset(&tex1, 0, 8);
    tex1.lcm = 1;
    if (pass == 2) {
        tex1.mmag = 0;
        tex1.mmin = 0;
    } else {
        tex1.mmag = 1;
        tex1.mmin = 1;
    }
    PackAD__4GIFSll(pgifs, 0x14, *(s64 *)&tex1);
    memset(&clamp, 0, 8);
    if (pref->flags & 1)
        clamp.wms = 1;
    if (pref->flags & 2)
        clamp.wmt = 1;
    PackAD__4GIFSll(pgifs, 8, *(s64 *)&clamp);
}
