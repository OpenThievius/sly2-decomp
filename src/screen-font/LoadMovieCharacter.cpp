#include "sly2.h"
#include "bis.h"
typedef CBinaryInputStream Bis;
struct SLOTHEAP;
#include "blot.h"
struct B4 { char b[4]; };
struct M3 { float mat[3][4]; } __attribute__((aligned(16)));
#include "alloc.h"
struct PRIM { int w0; int w4; int colour; unsigned char cvtx; char p0[3]; int cslot; unsigned char b14; char p1[3]; short *axy; unsigned char hasBytes; char p2[3]; unsigned char *abyte; };
struct BATCH { int cprim; int cslot; int cvtx; PRIM *pfirst; PRIM *pend; };
struct CHAR { int id; int kind; void *owner; u8 unknown_0xC[4]; union { struct { unsigned short cprim; unsigned short cbatch; int cvtxTotal; int cqw; int pk; } shape; float f[13]; int i[13]; } u; };
struct SVEC { short x, y; };
struct B8 { char b[8]; };
struct PL { long v; } __attribute__((packed));
struct GIFSX { u8 unknown_0x0[4]; char *ab; u8 unknown_0x8[4]; char *pb; u8 unknown_0x10[0x20]; };
class CStackFrame {
public:
    CStackFrame();
    ~CStackFrame();
};
struct VIFSX { u8 unknown_0x0[0x30]; } __attribute__((aligned(16)));
extern "C" {
void CBinaryInputStream_Read_thunk(Bis *, int, void *);
void *PvAllocSlotheapClearImpl__FP8SLOTHEAP(SLOTHEAP *, int, int);
void *PvAllocStackClearImpl__Fi(ALLOCREQ *);
void LoadMovieDictionary(BLOT *, Bis *, void *, void *, void *);
void __4GIFS(void *);
void AllocStack__4DMASi(void *, int);
void AddPrimPack__4GIFSiiUl(void *, int, int, unsigned long);
void PackAD__4GIFSll(void *, long, long);
void PackRGBA__4GIFSUi(void *, unsigned);
void PackSTQ__4GIFSfff(void *, float, float, float);
void PackXYZ__4GIFSiii(void *, int, int, int);
void EndPrim__4GIFSi(void *, int);
void __4VIFS(void *);
void AddDmaCnt__4DMAS(void *);
void AddDmaRet__4DMAS(void *);
void EndDmaCnt__4DMAS(void *);
void AddVifUnpack__4VIFS3UPKiPvi(void *, int, int, void *, int);
void AddVifMscal__4VIFSPv(void *, void *);
void AddVifStrow__4VIFSP2QW(void *, void *);
void AddVifStcycl__4VIFSii(void *, int, int);
void UnpackHelper__4VIFS3UPKiiPiPPUi(void *, int, int, int, int *, unsigned **);
void AddVifStmask__4VIFSUi(void *, unsigned);
void DMAS_DetachCopy(void *, SLOTHEAP *, void *, int, void *);
void QueueSwCallback(void *, BLOT *, long, void *);
extern int D_002C40A4;
extern char B_003DD490[];
extern char g_2a2e10[];
extern const B8 RO_002A8B08;
extern char VU1_ENTRY_650[], VU1_ENTRY_140[];
}
static inline void *PvAllocStackClear(int cb)
{
    ALLOCREQ req;
    req.cb = cb;
    req.cbAlign = 0x10;
    return PvAllocStackClearImpl__Fi(&req);
}
static inline void Store2x3(float *pf, M3 mat)
{
    pf[0] = mat.mat[0][0];
    pf[1] = mat.mat[0][1];
    pf[2] = mat.mat[1][0];
    pf[3] = mat.mat[1][1];
    pf[4] = mat.mat[2][0];
    pf[5] = mat.mat[2][1];
}
void LoadMovieCharacter(BLOT *const pblot, Bis *pbis, void *owner, int cchar, char *achar)
{
    CStackFrame frame;
    M3 mat;
    int ichar = pbis->U16Read();
    CHAR *pchar = (CHAR *)(achar + ichar * 0x40);
    pchar->id = ichar;
    pchar->owner = owner;
    unsigned kind = pbis->U32Read();
    pchar->kind = kind;
    switch (kind) {
    case 0:
    case 5:
        break;
    case 4:
        pchar->u.i[0] = pbis->U16Read();
        break;
    case 8:
        D_002C40A4 = 1;
        LoadMovieDictionary(pblot, pbis, owner, &pchar->u.i[0], &pchar->u.i[1]);
        pchar->u.i[4] = pbis->U32Read();
        pchar->u.i[5] = (int)PvAllocSlotheapClearImpl__FP8SLOTHEAP((SLOTHEAP *)pblot->palloc, pchar->u.i[4] << 2, 0x13);
        for (int icode = 0; icode < pchar->u.i[4]; icode++)
            ((unsigned *)pchar->u.i[5])[icode] = pbis->U32Read();
        pchar->u.i[2] = pbis->U32Read();
        pchar->u.i[3] = (int)PvAllocSlotheapClearImpl__FP8SLOTHEAP((SLOTHEAP *)pblot->palloc, pchar->u.i[2] << 2, 0x13);
        int i;
        for (i = 0; i < pchar->u.i[2]; i++)
            ((float *)pchar->u.i[3])[i] = pbis->F32Read();
        D_002C40A4 = 0;
        break;
    case 3: {
        pchar->u.i[0] = pbis->U32Read();
        pchar->u.i[3] = pbis->U32Read();
        pchar->u.f[4] = pbis->F32Read();
        pchar->u.f[6] = pbis->F32Read();
        pchar->u.f[5] = pbis->F32Read();
        pchar->u.i[7] = pbis->S8Read();
        int textk = pbis->S8Read();
        pchar->u.i[1] = textk;
        if (textk == 1) goto rd;
        if (textk != 0) goto nord;
    rd:
        pchar->u.i[2] = pbis->S32Read();
    nord:
        if (pchar->u.i[1] == 1 && pchar->u.i[2] == 0x2F2)
            pchar->u.i[8] = 1;
        else
            pchar->u.i[8] = 0;
        break;
    }
    case 2: {
        CBinaryInputStream_ReadMatrix(pbis, (MATRIX3 *)&mat);
        Store2x3(&pchar->u.f[0], mat);
        *(unsigned short *)&pchar->u.i[8] = pbis->U16Read();
        void *pv = PvAllocSlotheapClearImpl__FP8SLOTHEAP((SLOTHEAP *)pblot->palloc, *(unsigned short *)&pchar->u.i[8] * 0x18, 0x14);
        pchar->u.i[9] = (int)pv;
        CBinaryInputStream_Read_thunk(pbis, *(unsigned short *)&pchar->u.i[8] * 0x18, pv);
        break;
    }
    case 6:
    case 7: {
        SVEC lt;
        SVEC rb;
        lt.x = pbis->S16Read();
        lt.y = pbis->S16Read();
        rb.x = pbis->S16Read();
        rb.y = pbis->S16Read();
        int oid = pbis->S32Read();
        CStackFrame frame2;
        GIFSX gifs;
        __4GIFS(&gifs);
        AllocStack__4DMASi(&gifs, 0x10);
        AddPrimPack__4GIFSiiUl(&gifs, 0, 1, 0xE);
        if (pchar->kind == 6) {
            pchar->u.i[0] = oid;
            pchar->u.i[1] = 0;
            PackAD__4GIFSll(&gifs, 0x47, 0x5000F);
            PackAD__4GIFSll(&gifs, 0x42, 0x80000000A8UL);
        } else {
            pchar->u.i[0] = oid;
            PackAD__4GIFSll(&gifs, 0x42, 0x44);
            PackAD__4GIFSll(&gifs, 0x47, 0x50000);
        }
        AddPrimPack__4GIFSiiUl(&gifs, 0x54, 9, 0x525252521UL);
        PackRGBA__4GIFSUi(&gifs, 0x80808080);
        if (pchar->kind == 6) {
            PackSTQ__4GIFSfff(&gifs, 0.0f, 0.0f, 0.0f);
            PackXYZ__4GIFSiii(&gifs, lt.x, lt.y, 0);
            PackSTQ__4GIFSfff(&gifs, 1.0f, 0.0f, 0.0f);
            PackXYZ__4GIFSiii(&gifs, rb.x, lt.y, 0);
            PackSTQ__4GIFSfff(&gifs, 0.0f, 1.0f, 0.0f);
            PackXYZ__4GIFSiii(&gifs, lt.x, rb.y, 0);
            PackSTQ__4GIFSfff(&gifs, 1.0f, 1.0f, 0.0f);
            PackXYZ__4GIFSiii(&gifs, rb.x, rb.y, 0);
            AddPrimPack__4GIFSiiUl(&gifs, 0, 1, 0xE);
            PackAD__4GIFSll(&gifs, 0x42, 0x44);
            PackAD__4GIFSll(&gifs, 0x47, 0x50000);
        } else {
            PackSTQ__4GIFSfff(&gifs, 0.0f, 1.0f, 0.0f);
            PackXYZ__4GIFSiii(&gifs, lt.x, lt.y, 0);
            PackSTQ__4GIFSfff(&gifs, 1.0f, 1.0f, 0.0f);
            PackXYZ__4GIFSiii(&gifs, rb.x, lt.y, 0);
            PackSTQ__4GIFSfff(&gifs, 0.0f, 0.0f, 0.0f);
            PackXYZ__4GIFSiii(&gifs, lt.x, rb.y, 0);
            PackSTQ__4GIFSfff(&gifs, 1.0f, 0.0f, 0.0f);
            PackXYZ__4GIFSiii(&gifs, rb.x, rb.y, 0);
        }
        EndPrim__4GIFSi(&gifs, 1);
        VIFSX vifs2;
        __4VIFS(&vifs2);
        AllocStack__4DMASi(&vifs2, 0x14);
        AddDmaCnt__4DMAS(&vifs2);
        char *pstart = gifs.ab;
        char *pcur = gifs.pb;
        AddVifUnpack__4VIFS3UPKiPvi(&vifs2, 0xC, (unsigned)(pcur - pstart) >> 4, pstart, 7);
        AddVifMscal__4VIFSPv(&vifs2, VU1_ENTRY_650);
        EndDmaCnt__4DMAS(&vifs2);
        AddDmaRet__4DMAS(&vifs2);
        if (pchar->kind == 6) {
            DMAS_DetachCopy(&vifs2, (SLOTHEAP *)pblot->palloc, &pchar->u.i[2], 0, &pchar->u.i[3]);
        } else {
            DMAS_DetachCopy(&vifs2, (SLOTHEAP *)pblot->palloc, &pchar->u.i[1], 0, &pchar->u.i[2]);
            QueueSwCallback(B_003DD490, pblot, ((const PL *)&RO_002A8B08)->v, pchar);
        }
        break;
    }
    case 1: {
        pchar->u.shape.cprim = pbis->U16Read();
        PRIM *aprim = (PRIM *)PvAllocStackClear(pchar->u.shape.cprim * 0x24);
        BATCH *abatch = (BATCH *)PvAllocStackClear(pchar->u.shape.cprim * 0x14);
        int iprim;
        for (iprim = 0; iprim < pchar->u.shape.cprim; iprim++) {
            PRIM *pprim = aprim + iprim;
            pprim->cvtx = pbis->U8Read();
            pprim->b14 = pbis->U8Read();
            pprim->w0 = pbis->U8Read();
            pprim->w4 = pbis->U8Read();
            pprim->hasBytes = pbis->U8Read();
            pprim->cslot = pprim->cvtx + 2;
            pprim->axy = (short *)PvAllocStackClear(pprim->cvtx << 2);
            pprim->abyte = (unsigned char *)PvAllocStackClear(pprim->cvtx);
            for (int ivtx = 0; ivtx < pprim->cvtx; ivtx++) {
                short *pxy = (short *)((char *)pprim->axy + ivtx * 4);
                pprim->colour = pbis->U32Read();
                pprim->abyte[ivtx] = pbis->U8Read();
                pxy[0] = pbis->S16Read();
                pxy[1] = pbis->S16Read();
            }
        }
        pchar->u.shape.cbatch = 0;
        pchar->u.shape.cqw = 0;
        pchar->u.shape.cvtxTotal = 0;
        iprim = 0;
        while (iprim < pchar->u.shape.cprim) {
            BATCH *pbatch = abatch + pchar->u.shape.cbatch;
            pbatch->cprim = 0;
            pbatch->cvtx = 0;
            pbatch->cslot = 0;
            pbatch->pfirst = aprim + iprim;
            while (iprim < pchar->u.shape.cprim && pbatch->cslot + aprim[iprim].cslot < 0xBD) {
                pbatch->cslot += aprim[iprim].cslot;
                pbatch->cvtx += aprim[iprim].cvtx;
                pbatch->cprim += 1;
                iprim++;
                pbatch->pend = aprim + iprim;
            }
            int cprimBatch = pbatch->cprim;
            int cvtxBatch = pbatch->cvtx;
            int cqwBatch = (cvtxBatch + 1) / 4 + cvtxBatch / 16 + (cprimBatch * 3 + 3) / 4 + 3;
            pchar->u.shape.cqw += cqwBatch;
            pchar->u.shape.cvtxTotal += pbatch->cvtx;
            pchar->u.shape.cbatch += 1;
        }
        VIFSX vifs;
        __4VIFS(&vifs);
        AllocStack__4DMASi(&vifs, pchar->u.shape.cqw << 1);
        AddDmaCnt__4DMAS(&vifs);
        AddVifStrow__4VIFSP2QW(&vifs, g_2a2e10);
        for (i = 0; i < pchar->u.shape.cbatch; i++) {
            BATCH *pbatch = abatch + i;
            int acount[2];
            acount[0] = pbatch->cprim;
            AddVifUnpack__4VIFS3UPKiPvi(&vifs, 4, 1, acount, 7);
            AddVifStcycl__4VIFSii(&vifs, 1, 2);
            unsigned *pbHeader;
            unsigned *pwColor;
            UnpackHelper__4VIFS3UPKiiPiPPUi(&vifs, 0xA, pbatch->cprim, 8, 0, &pbHeader);
            UnpackHelper__4VIFS3UPKiiPiPPUi(&vifs, 0xE, pbatch->cprim, 9, 0, &pwColor);
            int iqw = pbatch->cprim * 2 + 8;
            AddVifStcycl__4VIFSii(&vifs, 1, 1);
            int iqwFirst = iqw;
            AddVifStmask__4VIFSUi(&vifs, 0x50505050);
            int iprimBatch = 0;
            for (PRIM *pprim = pbatch->pfirst; pprim != pbatch->pend; pprim++) {
                ((unsigned char *)pbHeader)[iprimBatch * 3] = pprim->w0;
                ((unsigned char *)pbHeader)[iprimBatch * 3 + 1] = pprim->cvtx;
                ((unsigned char *)pbHeader)[iprimBatch * 3 + 2] = pprim->b14;
                *(B4 *)&pwColor[iprimBatch] = *(B4 *)&pprim->colour;
                iprimBatch++;
                AddVifUnpack__4VIFS3UPKiPvi(&vifs, 0x15, pprim->cvtx, pprim->axy, iqw);
                iqw += pprim->cvtx;
            }
            AddVifStmask__4VIFSUi(&vifs, 0x3F3F3F3F);
            iqw = iqwFirst;
            for (PRIM *pprim = pbatch->pfirst; pprim != pbatch->pend; pprim++) {
                if (pprim->hasBytes)
                    AddVifUnpack__4VIFS3UPKiPvi(&vifs, 0x12, pprim->cvtx, pprim->abyte, iqw);
                iqw += pprim->cvtx;
            }
            AddVifStmask__4VIFSUi(&vifs, 0);
            AddVifMscal__4VIFSPv(&vifs, VU1_ENTRY_140);
        }
        EndDmaCnt__4DMAS(&vifs);
        AddDmaRet__4DMAS(&vifs);
        DMAS_DetachCopy(&vifs, (SLOTHEAP *)pblot->palloc, &pchar->u.shape.cqw, 0, &pchar->u.shape.pk);
        break;
    }
    }
}
