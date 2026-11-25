// SPDX-License-Identifier: GPL-3.0-or-later
/* no cfont.h: it brings types.h, whose QW is a typedef, and the DMA methods below mangle a struct QW (P2QW) */
struct QW;
struct DMAS { void AddDmaCnt(); void AddDmaRefs(int, QW *); void EndDmaCnt(); };
struct GIFS : DMAS {};
/* the bitmap font: fontk (CFONT's first field), then the DMA blocks FEnsureLoaded sends (read by this method only) */
struct CFontBrx {
    /* 0x00 */ int fontk;
    unsigned char unknown_0x4[0x58 - 4];
    /* 0x58 */ int cbBmp; QW *pqwBmp;
    unsigned char unknown_0x60[0xC0 - 0x60];
    /* 0xC0 */ int cbBmp2; QW *pqwBmp2;
    /* 0xC8 */ int cbClut; QW *pqwClut;
    unsigned char unknown_0xD0[0x130 - 0xD0];
    /* 0x130 */ int cb3; QW *pqw3;
    int FEnsureLoaded(GIFS *);
};
/* the frame being built (FRM, frm.h): FEnsureLoaded keeps a bit per font loaded into it at 0x2C (one reader, so a view) */
struct FRMFONTS { unsigned char unknown_0x0[0x2C]; unsigned fontsLoaded; };
extern GIFS B_002DEA00;
extern "C" FRMFONTS *g_2dea4c;
int CFontBrx::FEnsureLoaded(GIFS *pgifs)
{
    int fLoad;
    if (pgifs == &B_002DEA00) {
        unsigned bit = 1u << fontk;
        unsigned loaded = g_2dea4c->fontsLoaded;
        fLoad = (loaded & bit) == 0;
        g_2dea4c->fontsLoaded = loaded | bit;
    } else
        fLoad = 1;
    if (fLoad) {
        pgifs->EndDmaCnt();
        pgifs->AddDmaRefs(cbBmp, pqwBmp);
        pgifs->AddDmaRefs(cbBmp2, pqwBmp2);
        if (cbClut != 0) {
            pgifs->AddDmaRefs(cbClut, pqwClut);
            pgifs->AddDmaRefs(cb3, pqw3);
        }
        pgifs->AddDmaCnt();
    }
    return fLoad;
}
