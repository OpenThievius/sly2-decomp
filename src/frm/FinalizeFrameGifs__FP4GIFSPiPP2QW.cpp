// SPDX-License-Identifier: GPL-3.0-or-later
#include "frm.h"

extern "C" {
void AddDmaEnd__4DMAS(GIFS *);
void AddPrimEnd__4GIFS(GIFS *);
void AddPrimPack__4GIFSiiUl(GIFS *, int, int, unsigned long);
void Detach__4DMASPiPP2QW(GIFS *, int *, QW **);
void PackAD__4GIFSll(GIFS *, long, long);

void FinalizeFrameGifs__FP4GIFSPiPP2QW(GIFS *gifs, int *pcqw, QW **ppqw) {
    AddPrimPack__4GIFSiiUl(gifs, 0, 1, 0xE);
    PackAD__4GIFSll(gifs, 0x61, 0);
    AddPrimEnd__4GIFS(gifs);
    AddDmaEnd__4DMAS(gifs);
    Detach__4DMASPiPP2QW(gifs, pcqw, ppqw);
}
}
