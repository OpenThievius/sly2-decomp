#include "sly2.h"
struct GIFS { u8 unknown_0x0[0x30]; };
extern "C" void __4GIFS(GIFS *);
extern "C" void AllocStatic__4DMASiP2QW(GIFS *, int, QW **);
extern "C" void AddPrimPack__4GIFSiiUl(GIFS *, int, int, u64);
extern "C" void PackAD__4GIFSll(GIFS *, s64, s64);
extern "C" void AddPrimBulk__4GIFSiiiUlPP2QW(GIFS *, int, int, int, u64, QW **);
extern "C" void EndDmaCnt__4DMAS(GIFS *);

extern "C" void BuildBlipAqwGifs__FiPP2QW(int ialpha, QW **aqw)
{
    GIFS gifs;
    __4GIFS(&gifs);
    AllocStatic__4DMASiP2QW(&gifs, 4, aqw);
    AddPrimPack__4GIFSiiUl(&gifs, 0, 1, 0xE);
    PackAD__4GIFSll(&gifs, 0x47, 0x7180B);
    PackAD__4GIFSll(&gifs, 0x42, ((s64)ialpha << 2) | 0x40);
    AddPrimBulk__4GIFSiiiUlPP2QW(&gifs, 0x54, 0, 10, 0x424242412EUL, 0);
    EndDmaCnt__4DMAS(&gifs);
}
