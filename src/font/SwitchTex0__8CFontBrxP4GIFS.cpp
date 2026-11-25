#include "sly2.h"
#include "cfont.h"
extern "C" void AddPrimPack__4GIFSiiUl(GIFS *, int, int, u64);
extern "C" void PackAD__4GIFSll(GIFS *, s64, s64);
extern "C" void AddPrimList__4GIFSiUl(GIFS *, int, u64);
extern "C" int FEnsureLoaded__8CFontBrxP4GIFS(CFONT *, GIFS *);

extern "C" void SwitchTex0__8CFontBrxP4GIFS(CFONT *pfont, GIFS *pgifs)
{
    int fLoaded = FEnsureLoaded__8CFontBrxP4GIFS(pfont, pgifs);
    AddPrimPack__4GIFSiiUl(pgifs, 6, 1, 0xE);
    if (fLoaded)
        PackAD__4GIFSll(pgifs, 0x3F, 0);
    PackAD__4GIFSll(pgifs, 6, pfont->tex0);
    PackAD__4GIFSll(pgifs, 0, 0x1D6);
    AddPrimList__4GIFSiUl(pgifs, 5, 0x43431);
}
