#include "types.h"
#include "globset.h"
#include "so.h"
#include "alo.h"
struct BIS_167320;
struct REQ_167320 { int size; int align; };
struct GLOBREC { char c0; u8 unknown_0x1[2]; char type; float f4; u8 unknown_0x8[0x14 - 8]; };
struct GLOBINFO {
    int n0;
    int n4;
    u8 unknown_0x8[4];
    unsigned type : 3;
    unsigned c : 5;
    unsigned pad8b : 2;
    unsigned fHasF : 1;
    unsigned fFlag : 1;
    u8 unknown_0x10[0x28 - 0x10];
};
struct VEC_167320 { float x, y, z; };
struct INFO_167320 { float f0; int pad4; int n8; };
extern "C" {
void *memset(void *, int, unsigned int);
int S8Read__18CBinaryInputStream(BIS_167320 *);
unsigned U8Read__18CBinaryInputStream(BIS_167320 *);
int S16Read__18CBinaryInputStream(BIS_167320 *);
int U16Read__18CBinaryInputStream(BIS_167320 *);
int S32Read__18CBinaryInputStream(BIS_167320 *);
unsigned U32Read__18CBinaryInputStream(BIS_167320 *);
float F32Read__18CBinaryInputStream(BIS_167320 *);
void ReadVector__18CBinaryInputStreamP6VECTOR(BIS_167320 *, VEC_167320 *);
void CBinaryInputStream_Read_thunk(BIS_167320 *, int, void *);
void CBinaryInputStream_Skip(BIS_167320 *, int);
void *PvAllocSwClearImpl__Fi(REQ_167320 *);
int func_001ED7A8(int, BIS_167320 *);
int func_0013FAD0(int, short *);
void LoadGlobFromBrx(GLOBSET *, GLOBREC *, GLOBINFO *, INFO_167320 *, SUBGLOB *, int, BIS_167320 *);
void LoadGlobSkinnedFromBrx(GLOBSET *, GLOBREC *, GLOBINFO *, INFO_167320 *, SUBGLOB *, int, BIS_167320 *);
void LoadGlobStreamedFromBrx(GLOBSET *, GLOBREC *, GLOBINFO *, INFO_167320 *, SUBGLOB *, int, BIS_167320 *);
void LoadGlobIndexedFromBrx(GLOBSET *, GLOBREC *, GLOBINFO *, INFO_167320 *, SUBGLOB *, int, BIS_167320 *);
void LoadGlobsetBndTreeFromBrx(GLOBSET *, BIS_167320 *);
}

static inline void *PvAllocSwClear(int cb)
{
    REQ_167320 req;
    req.size = cb;
    req.align = 0x10;
    return PvAllocSwClearImpl__Fi(&req);
}

#define FLT_MAX_167320 3.40282347e+38f

extern "C" void LoadGlobsetFromBrx(GLOBSET *pglobset, ALO *palo, BIS_167320 *pbis)
{
    pglobset->palo = palo;
    int fNoSub = S8Read__18CBinaryInputStream(pbis);
    ReadVector__18CBinaryInputStreamP6VECTOR(pbis, (VEC_167320 *)pglobset->center);
    pglobset->radius = F32Read__18CBinaryInputStream(pbis);
    pglobset->field_0x24 = U8Read__18CBinaryInputStream(pbis);
    pglobset->field_0x28 = (int *)PvAllocSwClear(pglobset->field_0x24 * 4);
    for (int i = 0; i < pglobset->field_0x24; i++)
        pglobset->field_0x28[i] = func_001ED7A8(1, pbis);
    pglobset->field_0x2C = U8Read__18CBinaryInputStream(pbis);
    pglobset->field_0x30 = (int *)PvAllocSwClear(pglobset->field_0x2C * 4);
    pglobset->field_0x34 = 0;
    for (int i = 0; i < pglobset->field_0x2C; i++)
        pglobset->field_0x30[i] = S32Read__18CBinaryInputStream(pbis);
    pglobset->cglob = S16Read__18CBinaryInputStream(pbis);
    pglobset->aglob = (GLOBREC *)PvAllocSwClear(pglobset->cglob * sizeof(GLOBREC));
    pglobset->aglobi = (GLOBINFO *)PvAllocSwClear(pglobset->cglob * sizeof(GLOBINFO));
    if (!fNoSub)
        pglobset->asubglob = (SUBGLOB *)PvAllocSwClear(pglobset->cglob * sizeof(SUBGLOB));
    for (int iglob = 0; iglob < pglobset->cglob; iglob++) {
        GLOBREC *pglob = &pglobset->aglob[iglob];
        GLOBINFO *pglobi = &pglobset->aglobi[iglob];
        SUBGLOB *psubglob = pglobset->asubglob ? &pglobset->asubglob[iglob] : 0;
        INFO_167320 info;
        memset(&info, 0, sizeof(info));
        short ashort[0x80];
        int cshort = S8Read__18CBinaryInputStream(pbis);
        if (cshort != 0) {
            CBinaryInputStream_Read_thunk(pbis, cshort * 2, ashort);
            int cbSkip = S32Read__18CBinaryInputStream(pbis);
            if (!func_0013FAD0(cshort, ashort)) {
                CBinaryInputStream_Skip(pbis, cbSkip);
                iglob--;
                pglobset->cglob--;
                continue;
            }
        }
        pglob->type = S8Read__18CBinaryInputStream(pbis);
        int count = U16Read__18CBinaryInputStream(pbis);
        pglobi->n4 = (int)palo->PxfFromRef(S16Read__18CBinaryInputStream(pbis));
        pglob->c0 = S8Read__18CBinaryInputStream(pbis);
        float scale = F32Read__18CBinaryInputStream(pbis);
        pglob->f4 = scale == FLT_MAX_167320 ? FLT_MAX_167320 : scale * __builtin_fabsf(scale);
        info.f0 = F32Read__18CBinaryInputStream(pbis);
        pglobi->n0 = S32Read__18CBinaryInputStream(pbis);
        info.n8 = S8Read__18CBinaryInputStream(pbis);
        pglobi->fFlag = S8Read__18CBinaryInputStream(pbis);
        if (!fNoSub) {
            ReadVector__18CBinaryInputStreamP6VECTOR(pbis, (VEC_167320 *)psubglob->pos);
            psubglob->radius = F32Read__18CBinaryInputStream(pbis);
            psubglob->field_0x14 = U32Read__18CBinaryInputStream(pbis);
            if ((psubglob->field_0x10 = F32Read__18CBinaryInputStream(pbis)) == FLT_MAX_167320) {
                switch (pglob->type) {
                case 0:
                case 2:
                case 3:
                    psubglob->field_0x10 = 1e10f;
                    break;
                case 1:
                    psubglob->field_0x10 = 2000.0f;
                    break;
                }
            }
        }
        pglobi->type = pglob->type;
        pglobi->c = pglob->c0;
        if (pglob->f4 != FLT_MAX_167320)
            pglobi->fHasF = 1;
        switch (pglob->type) {
        case 0:
            LoadGlobFromBrx(pglobset, pglob, pglobi, &info, psubglob, count, pbis);
            break;
        case 1:
            LoadGlobSkinnedFromBrx(pglobset, pglob, pglobi, &info, psubglob, count, pbis);
            break;
        case 2:
            LoadGlobStreamedFromBrx(pglobset, pglob, pglobi, &info, psubglob, count, pbis);
            break;
        case 3:
            LoadGlobIndexedFromBrx(pglobset, pglob, pglobi, &info, psubglob, count, pbis);
            break;
        }
        iglob += count;
    }
    LoadGlobsetBndTreeFromBrx(pglobset, pbis);
}
