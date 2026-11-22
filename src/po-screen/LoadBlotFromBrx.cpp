// SPDX-License-Identifier: GPL-3.0-or-later
#include "blot.h"
#include "alloc.h"

struct BIS;
extern "C" void LoadLoFromBrx(BLOT *, BIS *);
extern "C" int S8Read__18CBinaryInputStream(BIS *);
extern "C" float F32Read__18CBinaryInputStream(BIS *);
extern "C" unsigned U32Read__18CBinaryInputStream(BIS *);
extern "C" void *PvAllocSwClearImpl__Fi(ALLOCREQ *);
extern "C" void func_00118458(BIS *, BLOTSTREAM *);
extern "C" void AppendSlEntry(void *, void *);
extern "C" void LoadMovieDictionary(void *, BIS *, void *, void *, void *);
extern "C" void LoadMovieSprites(void *, BIS *, void *);
extern "C" char B_003E1C70[], B_003E106C[], B_003E1C80[];

void LoadBlotFromBrx(BLOT *blot, BIS *stream) {
    blot->labelVisible = 0x310;
    blot->labelAppear = 0x30F;
    blot->labelDisappear = 0x311;
    LoadLoFromBrx(blot, stream);
    int streamed = S8Read__18CBinaryInputStream(stream);
    blot->dwell = F32Read__18CBinaryInputStream(stream);
    blot->height = U32Read__18CBinaryInputStream(stream);
    blot->width = U32Read__18CBinaryInputStream(stream);
    blot->field_0xBC = U32Read__18CBinaryInputStream(stream);
    if (streamed) {
        blot->blots = 0;
        ALLOCREQ request;
        request.cb = 0x50;
        request.cbAlign = 0x10;
        blot->palloc = B_003E1C70;
        BLOTSTREAM *pstream = (BLOTSTREAM *)PvAllocSwClearImpl__Fi(&request);
        blot->pstream = pstream;
        pstream->pblot = blot;
        func_00118458(stream, blot->pstream);
        AppendSlEntry(B_003E106C, blot->pstream);
    } else {
        blot->blots = 1;
        blot->palloc = B_003E1C80;
        LoadMovieDictionary(blot, stream, blot, &blot->field_0x50, &blot->field_0x54);
        LoadMovieSprites(blot, stream, blot);
    }
    blot->cur = -1;
}
