#include "sly2.h"
#include "bmp.h"
/* the ZPR (BlendDisplayOnBufferMismatch_file.cpp) as far as the upload reads it: its cursor at 4 (InitZpr, FlushZprPage) and the word at 8 it is compared with */
struct Ctl { u8 unknown_0x0[4]; int cur; int f8; };
/* the GIFS' DMAS cursor at 0xC (DMAS::pbCur: StartupDma_file.cpp, __4GIFS_file.cpp) */
struct Ctx { u8 unknown_0x0[0xC]; u8 *pbCur; };
extern "C" {
void AddDmaRefs__4DMASiP2QW(Ctx *, int, int);
void AddToIdTableA_1ed470(BMP *);
void AddToIdTableB_1ed560(CLUT *);
int AllocZpr(Ctl *, int);
void BuildBmpGifs__FP3BMPiP4GIFS(BMP *, int, Ctx *);
void BuildBmpTex0__FP3BMPi(BMP *, int);
void BuildClutGifs__FP4CLUTiP4GIFS(CLUT *, int, Ctx *);
void BuildClutTex2__FP4CLUTi(CLUT *, int);
BMP *PidFindInIdTableA_1ed4e0(int);
CLUT *PidFindInIdTableB_1ed5d0(int);
extern int B_003DCFF0;
extern BMP *B_003DCFF4;
extern int B_003DCFF8;
extern CLUT *B_003DCFFC;
}
extern "C" int FBuildUploadBitmapGifs__FiP3GSBP4GIFS(int mask, Ctl *b, Ctx *c)
{
    u8 *saved;
    if (c != 0) {
        saved = c->pbCur;
    } else {
        saved = 0;
    }
    for (int i = 0; i < B_003DCFF8; i++) {
        CLUT *e = &B_003DCFFC[i];
        if (mask == e->group) {
            CLUT *found = PidFindInIdTableB_1ed5d0(e->oid);
            if (found != 0) {
                e->tex2 = found->tex2;
            } else {
                int v = AllocZpr(b, e->iblock);
                BuildClutTex2__FP4CLUTi(e, v);
                if (c != 0 && b->cur <= b->f8) {
                    BuildClutGifs__FP4CLUTiP4GIFS(e, v, c);
                    AddDmaRefs__4DMASiP2QW(c, e->cb2, (int)e->pqw2);
                }
                AddToIdTableB_1ed560(e);
            }
        }
    }
    for (int i = 0; i < B_003DCFF0; i++) {
        BMP *e = &B_003DCFF4[i];
        if (mask == e->bmpk) {
            BMP *found = PidFindInIdTableA_1ed4e0(e->oid);
            if (found != 0) {
                e->tex0 = found->tex0;
            } else {
                if (e->field_0xC == 0) {
                    int rem = b->cur & 0x1F;
                    if (rem != 0)
                        AllocZpr(b, 0x20 - rem);
                }
                int v = AllocZpr(b, e->iblock);
                BuildBmpTex0__FP3BMPi(e, v);
                if (c != 0 && b->cur <= b->f8) {
                    BuildBmpGifs__FP3BMPiP4GIFS(e, v, c);
                    AddDmaRefs__4DMASiP2QW(c, e->cqw, (int)e->pvPixels);
                }
                AddToIdTableA_1ed470(e);
            }
        }
    }
    if (c == 0)
        return 0;
    return c->pbCur != saved;
}
