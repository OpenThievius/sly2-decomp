// SPDX-License-Identifier: GPL-3.0-or-later
/* the DMA methods are extern "C" under their retail names: cfont.h brings types.h, whose QW is a typedef, so they cannot be
   declared as methods whose mangling names a struct QW (P2QW) */
#include "cfont.h"
#include "frm.h"
extern "C" {
void EndDmaCnt__4DMAS(GIFS *);
void AddDmaRefs__4DMASiP2QW(GIFS *, int, QW *);
void AddDmaCnt__4DMAS(GIFS *);
extern GIFS B_002DEA00;
extern FRM *g_2dea4c;
int FEnsureLoaded__8CFontBrxP4GIFS(CFONT *pfont, GIFS *pgifs)
{
    int fLoad;
    if (pgifs == &B_002DEA00) {
        unsigned bit = 1u << pfont->fontk;
        unsigned loaded = g_2dea4c->grfFontLoaded;
        fLoad = (loaded & bit) == 0;
        g_2dea4c->grfFontLoaded = loaded | bit;
    } else
        fLoad = 1;
    if (fLoad) {
        EndDmaCnt__4DMAS(pgifs);
        AddDmaRefs__4DMASiP2QW(pgifs, pfont->cbBmp, (QW *)pfont->pqwBmp);
        AddDmaRefs__4DMASiP2QW(pgifs, pfont->cbBmp2, (QW *)pfont->pqwBmp2);
        if (pfont->cbClut != 0) {
            AddDmaRefs__4DMASiP2QW(pgifs, pfont->cbClut, (QW *)pfont->pqwClut);
            AddDmaRefs__4DMASiP2QW(pgifs, pfont->cbClut2, (QW *)pfont->pqwClut2);
        }
        AddDmaCnt__4DMAS(pgifs);
    }
    return fLoad;
}
}
