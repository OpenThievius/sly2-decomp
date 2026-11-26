#include "sly2.h"
#include "fbsprite.h"
struct SLOTHEAP;
struct Bis;
struct B4 { char b[4]; };
struct M3 { QW r[3]; };
/* the loader's own views of what a key holds (nothing else in the matched code reads them) */
struct SPRITEPLACE { unsigned short a, b, c; short d; u8 unknown_0x8[0x8]; float m[6]; u8 unknown_0x28[0x8]; unsigned char e, f; u8 unknown_0x32[0x2]; int g; u8 unknown_0x38[0x8]; };
struct SPRITEPAIR { int second; int first; };
struct SPRITEACTION { unsigned kind; int arg; };
extern "C" {
unsigned short U16Read__18CBinaryInputStream(Bis *);
unsigned char U8Read__18CBinaryInputStream(Bis *);
short S16Read__18CBinaryInputStream(Bis *);
unsigned U32Read__18CBinaryInputStream(Bis *);
int S32Read__18CBinaryInputStream(Bis *);
float F32Read__18CBinaryInputStream(Bis *);
void CBinaryInputStream_ReadMatrix(Bis *, M3 *);
void InitDepthSlot(SLOT *);
void *PvAllocSlotheapClearImpl__FP8SLOTHEAP(SLOTHEAP *, int, int);
}
void LoadMovieSprites(BLOT *pblot, Bis *pbis, BLOT *pmovie)
{
    pmovie->csprite = U16Read__18CBinaryInputStream(pbis);
    pmovie->asprite = (s32)PvAllocSlotheapClearImpl__FP8SLOTHEAP((SLOTHEAP *)pblot->palloc, pmovie->csprite * 0x30, 0x12);
    for (int isprite = 0; isprite < pmovie->csprite; isprite++) {
        SPRITE *psprite = (SPRITE *)pmovie->asprite + isprite;
        psprite->fRoot = isprite == 0;
        psprite->pmovie = (SPRITEMOVIE *)pmovie;
        psprite->cinstance = U16Read__18CBinaryInputStream(pbis);
        psprite->insts = (SPRITEINST *)PvAllocSlotheapClearImpl__FP8SLOTHEAP((SLOTHEAP *)pblot->palloc, psprite->cinstance * 0x18, 0x12);
        int cslot = U16Read__18CBinaryInputStream(pbis);
        for (int iinst = 0; iinst < psprite->cinstance; iinst++) {
            SPRITEINST *pinst = psprite->insts + iinst;
            pinst->t = 0.0f;
            pinst->ilabel = -1;
            pinst->ikeyNext = 0;
            pinst->fPaused = 0;
            pinst->cslot = cslot;
            pinst->aslot = (SLOT *)PvAllocSlotheapClearImpl__FP8SLOTHEAP((SLOTHEAP *)pblot->palloc, cslot * 0x70, 0x10);
            for (int islot = 0; islot < pinst->cslot; islot++)
                InitDepthSlot(pinst->aslot + islot);
        }
        psprite->clabel = U16Read__18CBinaryInputStream(pbis);
        psprite->labels = (SPRITELABEL *)PvAllocSlotheapClearImpl__FP8SLOTHEAP((SLOTHEAP *)pblot->palloc, psprite->clabel * 0x18, 0x12);
        psprite->ilabelPending = -1;
        for (int ilabel = 0; ilabel < psprite->clabel; ilabel++) {
            SPRITELABEL *plabel = psprite->labels + ilabel;
            plabel->pblot = pmovie;
            plabel->psprite = psprite;
            plabel->dt = F32Read__18CBinaryInputStream(pbis);
            plabel->id = S32Read__18CBinaryInputStream(pbis);
            plabel->ckey = U16Read__18CBinaryInputStream(pbis);
            plabel->akey = (SPRITEKEY *)PvAllocSlotheapClearImpl__FP8SLOTHEAP((SLOTHEAP *)pblot->palloc, plabel->ckey << 5, 0x12);
            for (int ikey = 0; ikey < plabel->ckey; ikey++) {
                SPRITEKEY *pkey = plabel->akey + ikey;
                pkey->t = F32Read__18CBinaryInputStream(pbis);
                pkey->cplace = U8Read__18CBinaryInputStream(pbis);
                pkey->aplace = (SPRITEPLACE *)PvAllocSlotheapClearImpl__FP8SLOTHEAP((SLOTHEAP *)pblot->palloc, pkey->cplace << 6, 0x12);
                for (int iplace = 0; iplace < pkey->cplace; iplace++) {
                    SPRITEPLACE *pplace = pkey->aplace + iplace;
                    pplace->a = U16Read__18CBinaryInputStream(pbis);
                    pplace->b = U16Read__18CBinaryInputStream(pbis);
                    pplace->c = U16Read__18CBinaryInputStream(pbis);
                    pplace->d = S16Read__18CBinaryInputStream(pbis);
                    pplace->e = U8Read__18CBinaryInputStream(pbis);
                    pplace->f = U8Read__18CBinaryInputStream(pbis);
                    pplace->g = S32Read__18CBinaryInputStream(pbis);
                    M3 mat;
                    CBinaryInputStream_ReadMatrix(pbis, &mat);
                    M3 mat2 = mat;
                    float *pf = pplace->m;
                    pf[0] = ((float *)&mat2)[0];
                    pf[1] = ((float *)&mat2)[1];
                    pf[2] = ((float *)&mat2)[4];
                    pf[3] = ((float *)&mat2)[5];
                    pf[4] = ((float *)&mat2)[8];
                    pf[5] = ((float *)&mat2)[9];
                }
                pkey->cpair = U8Read__18CBinaryInputStream(pbis);
                pkey->apair = (SPRITEPAIR *)PvAllocSlotheapClearImpl__FP8SLOTHEAP((SLOTHEAP *)pblot->palloc, pkey->cpair << 3, 0x12);
                for (int ipair = 0; ipair < pkey->cpair; ipair++) {
                    SPRITEPAIR *ppair = pkey->apair + ipair;
                    B4 first, second;
                    *(unsigned *)&first = U32Read__18CBinaryInputStream(pbis);
                    *(unsigned *)&second = U32Read__18CBinaryInputStream(pbis);
                    *(B4 *)&ppair->first = first;
                    *(B4 *)&ppair->second = second;
                }
                pkey->cclear = U8Read__18CBinaryInputStream(pbis);
                pkey->aclear = (u16 *)PvAllocSlotheapClearImpl__FP8SLOTHEAP((SLOTHEAP *)pblot->palloc, pkey->cclear << 1, 0x12);
                for (int ihalf = 0; ihalf < pkey->cclear; ihalf++)
                {
                    unsigned short *phalf = pkey->aclear + ihalf;
                    *phalf = U16Read__18CBinaryInputStream(pbis);
                }
                pkey->caction = U8Read__18CBinaryInputStream(pbis);
                pkey->aaction = (u8 *)PvAllocSlotheapClearImpl__FP8SLOTHEAP((SLOTHEAP *)pblot->palloc, pkey->caction, 0x12);
                for (int ibyte = 0; ibyte < pkey->caction; ibyte++)
                    pkey->aaction[ibyte] = U8Read__18CBinaryInputStream(pbis);
                pkey->cactionRec = U8Read__18CBinaryInputStream(pbis);
                pkey->aactionRec = (SPRITEACTION *)PvAllocSlotheapClearImpl__FP8SLOTHEAP((SLOTHEAP *)pblot->palloc, pkey->cactionRec << 3, 0x12);
                for (int iaction = 0; iaction < pkey->cactionRec; iaction++) {
                    pkey->aactionRec[iaction].kind = U8Read__18CBinaryInputStream(pbis);
                    if (pkey->aactionRec[iaction].kind < 2)
                        pkey->aactionRec[iaction].arg = S32Read__18CBinaryInputStream(pbis);
                    else
                        pkey->aactionRec[iaction].arg = S32Read__18CBinaryInputStream(pbis);
                }
            }
        }
    }
}
