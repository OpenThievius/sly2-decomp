#include "sly2.h"
#include "cfont.h"
#include "bmp.h"
struct FONTF { u8 unknown_0x0[4]; unsigned char dxChar; unsigned char dxSpace; unsigned char dy; unsigned char fontk; float rScale; unsigned short cglyff; };
struct FONTD { FONTF *pfontf; GLYPH *aglyff; BMP *pbmp; CLUT *pclut; };
struct GIFS { char data[0x30]; };
extern "C" void CFontBrx_Register(CFONT *);
extern "C" void __4GIFS(GIFS *);
extern "C" int AllocZpr(void *, int);
extern "C" void BuildBmpTex0__FP3BMPi(BMP *, int);
extern "C" void AllocStatic__4DMASiP2QW(GIFS *, int, void *);
extern "C" void BuildBmpGifs__FP3BMPiP4GIFS(BMP *, int, GIFS *);
extern "C" void Detach__4DMASPiPP2QW(GIFS *, int *, void **);
extern "C" void BuildClutTex2__FP4CLUTi(CLUT *, int);
extern "C" void BuildClutGifs__FP4CLUTiP4GIFS(CLUT *, int, GIFS *);
extern "C" void func_0015F710(CFONT *pfont, FONTD *pfontd, void *pzpr)
{
    FONTF *pfontf = pfontd->pfontf;
    pfont->fontk = pfontf->fontk;
    CFontBrx_Register(pfont);
    pfont->dxChar = pfontf->dxChar;
    pfont->dxSpace = pfontf->dxSpace;
    pfont->lineHeight = pfontf->dy;
    pfont->scaleX = pfontf->rScale;
    pfont->scaleY = pfontf->rScale;
    pfont->cglyff = pfontf->cglyff;
    pfont->aglyff = pfontd->aglyff;
    GIFS gifs;
    __4GIFS(&gifs);
    BMP *pbmp = pfontd->pbmp;
    CLUT *pclut = pfontd->pclut;
    int iblock = AllocZpr(pzpr, pbmp->iblock);
    BuildBmpTex0__FP3BMPi(pbmp, iblock);
    pfont->tex0 = pbmp->tex0;
    AllocStatic__4DMASiP2QW(&gifs, 6, pfont->packetBmp);
    BuildBmpGifs__FP3BMPiP4GIFS(pbmp, iblock, &gifs);
    Detach__4DMASPiPP2QW(&gifs, &pfont->cbBmp, &pfont->pqwBmp);
    pfont->cbBmp2 = pbmp->cqw;
    pfont->pqwBmp2 = pbmp->pvPixels;
    if (pclut != 0) {
        iblock = AllocZpr(pzpr, pclut->iblock);
        BuildClutTex2__FP4CLUTi(pclut, iblock);
        pfont->tex0 |= pclut->tex2;
        AllocStatic__4DMASiP2QW(&gifs, 6, pfont->packetClut);
        BuildClutGifs__FP4CLUTiP4GIFS(pclut, iblock, &gifs);
        Detach__4DMASPiPP2QW(&gifs, &pfont->cbClut, &pfont->pqwClut);
        pfont->cbClut2 = pclut->cb2;
        pfont->pqwClut2 = pclut->pqw2;
    }
}
