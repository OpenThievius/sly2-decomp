// SPDX-License-Identifier: GPL-3.0-or-later
struct Bis;
#include "alloc.h"
#include "phys.h"
#include "so.h"
struct GEOMDATA { int word[6]; };
struct SOREC {
    void *shape; void *owner; float field8; int fieldC;
    int field10; short field14; unsigned long flagA : 1; unsigned long flagB : 1; unsigned long flagC : 1;
    int field18; int field1C; char pad20[0x48]; int field68[4]; GEOMDATA geomSource; GEOMDATA geomCopy; char padA8[8];
};
extern "C" {
int U32Read__18CBinaryInputStream(Bis *);
int S8Read__18CBinaryInputStream(Bis *);
int S16Read__18CBinaryInputStream(Bis *);
int S32Read__18CBinaryInputStream(Bis *);
float F32Read__18CBinaryInputStream(Bis *);
void *PvAllocSwClearImpl__Fi(ALLOCREQ *);
void LoadAloFromBrx(SO *, Bis *);
void LoadGlobsetFromBrx(void *, SO *, Bis *);
void CBinaryInputStream_ReadGeom(Bis *, GEOMDATA *);
void CBinaryInputStream_ReadBspc(Bis *, GEOMDATA *, void *);
void CBinaryInputStream_ReadMatrix(Bis *, void *);
void CloneGeom(GEOMDATA *, int, GEOMDATA *);
void AddSoGeomsToOxa(SO *);
void AdjustSoMomint__FP2SOf(SO *, float);
void LoadOptionsFromBrx__FPvP18CBinaryInputStream(SO *, Bis *);
void func_001F2500(SO *);
void LoadSwObjectsFromBrx(SO *, Bis *, int);
int SetLoGrfzon(SO *, int);
extern char D_002C44F0[];
}
extern "C" void CSo_LoadFromBrx(SO *pso, Bis *pbis)
{
    int index = 0;
    SOREC *rec;
    ALLOCREQ req;
    LoadAloFromBrx(pso, pbis);
    int grfzon = U32Read__18CBinaryInputStream(pbis);
    LoadGlobsetFromBrx(&pso->field_0x80, pso, pbis);
    int extra = pso->Slot63();
    int count = S16Read__18CBinaryInputStream(pbis);
    req.cb = (count + extra) * 0xB0;
    req.cbAlign = 0x10;
    pso->cgeom = count;
    pso->ageom = (GEOM *)PvAllocSwClearImpl__Fi(&req);
    if (pso->cgeom > 0) {
        do {
            rec = &((SOREC *)pso->ageom)[index];
            rec->owner = pso;
            int shapeId = S16Read__18CBinaryInputStream(pbis);
            rec->shape = pso->PxfFromRef(shapeId);
            rec->fieldC = S32Read__18CBinaryInputStream(pbis);
            rec->flagA = S8Read__18CBinaryInputStream(pbis);
            rec->flagB = S8Read__18CBinaryInputStream(pbis);
            rec->field8 = F32Read__18CBinaryInputStream(pbis);
            CBinaryInputStream_ReadGeom(pbis, &rec->geomSource);
            GEOMDATA *geomUsed;
            if (rec->shape == 0) {
                rec->shape = D_002C44F0;
                rec->geomCopy = rec->geomSource;
                geomUsed = &rec->geomCopy;
            } else {
                CloneGeom(&rec->geomSource, 0, &rec->geomCopy);
                geomUsed = &rec->geomCopy;
            }
            CBinaryInputStream_ReadBspc(pbis, geomUsed, rec->field68);
            index++;
            rec->field18 = U32Read__18CBinaryInputStream(pbis);
            rec->field14 = S16Read__18CBinaryInputStream(pbis);
            rec->field1C = S16Read__18CBinaryInputStream(pbis);
            rec->flagC = S8Read__18CBinaryInputStream(pbis);
        } while (index < pso->cgeom);
    }
    index = pso->cgeom;
    if (index < index + extra) {
        int offset = index * 0xB0;
        do {
            index++;
            rec = (SOREC *)((char *)pso->ageom + offset);
            rec->field14 = -10;
            offset += 0xB0;
        } while (index < pso->cgeom + extra);
    }
    AddSoGeomsToOxa(pso);
    if (pso->cgeom > 0) {
        req.cb = 0xE0;
        req.cbAlign = 0x10;
        PHYS *momint = (PHYS *)PvAllocSwClearImpl__Fi(&req);
        pso->pphys = momint;
        momint->field_0xD0 = F32Read__18CBinaryInputStream(pbis);
        CBinaryInputStream_ReadMatrix(pbis, momint);
        AdjustSoMomint__FP2SOf(pso, 1.0f);
        pso->Slot64();
    }
    LoadOptionsFromBrx__FPvP18CBinaryInputStream(pso, pbis);
    if (pso->field_0xB8 != 0) {
        int *flags = (int *)pso->pgrfentry;
        if (((uptr)flags ^ 1) & 1) {
            *flags |= 8;
        } else {
            pso->grfSw = (u32)((sptr)flags | 8);
        }
    }
    func_001F2500(pso);
    LoadSwObjectsFromBrx(pso, pbis, 0);
    SetLoGrfzon(pso, grfzon);
}
