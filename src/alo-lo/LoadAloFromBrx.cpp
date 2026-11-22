// SPDX-License-Identifier: GPL-3.0-or-later
#include "act.h"
#include "alo.h"
#include "alloc.h"
#include "sw.h"
#include "sly2.h"
struct Bis;
extern "C" {
unsigned U8Read__18CBinaryInputStream(Bis *);
int S8Read__18CBinaryInputStream(Bis *);
int S16Read__18CBinaryInputStream(Bis *);
int S32Read__18CBinaryInputStream(Bis *);
float F32Read__18CBinaryInputStream(Bis *);
void ReadVector__18CBinaryInputStreamP6VECTOR(Bis *, VECTOR *);
void CBinaryInputStream_ReadMatrix4(Bis *, MATRIX4 *);
void func_00117F90(Bis *, CLQ *);
void func_00117FB0(Bis *, LM *);
void *PvAllocSwClearImpl__Fi(ALLOCREQ *);
void *PvAllocAct(int);
QW GetXfDofValue(XF *, XF *);
void InsertXfAct(ALO *, XF *, ACT *);
void LoadAloIkLimbs(ALO *, Bis *);
void LoadXfMirrors(ALO *, Bis *);
void func_0021C888(ALO *, Bis *);
void func_0022C818(ALO *, XF *);
void UpdateAloXfWorld(ALO *);
extern char D_002CA6A0[], D_002CA7A0[], D_002CA7E0[], D_002CA820[];
}
/* the two halfwords LoadAloFromBrx stores at XF 0xAC (a thousandth of the loaded scales, 1000 when the record has none): a view,
   since this loader is their only reader and not a method of XF */
struct XFLOADVIEW {
    u8 unknown_0x0[0xAC];
    /* 0xAC */ s16 limitLo;
    /* 0xAE */ s16 limitHi;
};
static inline XF *ReadXf(ALO *palo, Bis *pbis)
{
    int id = S16Read__18CBinaryInputStream(pbis);
    return (XF *)palo->PxfFromRef(id);
}
extern "C" void LoadAloFromBrx(ALO *palo, Bis *pbis)
{
    int index = 0;
    ALLOCREQ req;
    int count = S16Read__18CBinaryInputStream(pbis);
    req.cb = count << 8;
    req.cbAlign = 0x10;
    palo->cxf = count;
    palo->axf = (XF *)PvAllocSwClearImpl__Fi(&req);
    {
        ACT2 *actB;
        ACT4 *actC;
        ACT1 *actA;
        ACT9 *actD;
        int hasA;
        int hasB;
        int hasC;
        for (; index < palo->cxf; index++) {
            XF *rec = &palo->axf[index];
            rec->pxfParent = ReadXf(palo, pbis);
            rec->dof = S16Read__18CBinaryInputStream(pbis);
            rec->id = S32Read__18CBinaryInputStream(pbis);
            unsigned flags = U8Read__18CBinaryInputStream(pbis);
            if (flags & 1) {
                float scaleA = F32Read__18CBinaryInputStream(pbis);
                ((XFLOADVIEW *)rec)->limitHi = 1000;
                ((XFLOADVIEW *)rec)->limitLo = (int)(scaleA * 1000.0f);
            } else if (flags & 2) {
                ((XFLOADVIEW *)rec)->limitLo = (int)(F32Read__18CBinaryInputStream(pbis) * 1000.0f);
                ((XFLOADVIEW *)rec)->limitHi = (int)(F32Read__18CBinaryInputStream(pbis) * 1000.0f);
            } else {
                ((XFLOADVIEW *)rec)->limitLo = 1000;
                ((XFLOADVIEW *)rec)->limitHi = 1000;
            }
            hasA = flags & 4;
            if (hasA) {
                ACT1 *fresh = (ACT1 *)PvAllocAct(0x30);
                fresh->act.vtable = D_002CA820;
                fresh->act.kind = 1;
                fresh->field_0x1C = 2;
                actA = fresh;
                actA->act.xfk = S8Read__18CBinaryInputStream(pbis);
            }
            hasB = flags & 8;
            if (hasB) {
                ACT2 *fresh = (ACT2 *)PvAllocAct(0x80);
                fresh->act.kind = 2;
                fresh->act.vtable = D_002CA7E0;
                actB = fresh;
                actB->act.xfk = S8Read__18CBinaryInputStream(pbis);
                actB->field_0x60 = F32Read__18CBinaryInputStream(pbis);
                func_00117F90(pbis, &actB->clq30);
                func_00117FB0(pbis, &actB->lm50);
                func_00117F90(pbis, &actB->clq40);
                func_00117FB0(pbis, &actB->lm58);
                actB->field_0x64 = S8Read__18CBinaryInputStream(pbis);
                actB->field_0x68 = S8Read__18CBinaryInputStream(pbis);
                actB->field_0x6C = S32Read__18CBinaryInputStream(pbis);
            }
            hasC = flags & 0x10;
            if (hasC) {
                ACT4 *fresh = (ACT4 *)PvAllocAct(0x28);
                fresh->act.kind = 4;
                fresh->act.vtable = D_002CA7A0;
                actC = fresh;
                actC->act.xfk = S8Read__18CBinaryInputStream(pbis);
                actC->field_0x1C = F32Read__18CBinaryInputStream(pbis);
                actC->field_0x20 = F32Read__18CBinaryInputStream(pbis);
            }
            int hasD = flags & 0x20;
            if (hasD) {
                ACT9 *fresh = (ACT9 *)PvAllocAct(0x30);
                fresh->act.vtable = D_002CA6A0;
                fresh->act.kind = 9;
                fresh->act.xfk = 0x14;
                actD = fresh;
                ReadVector__18CBinaryInputStreamP6VECTOR(pbis, &actD->vec20);
            }
            switch (rec->dof) {
            case 0:
            case 13:
            case 15:
                CBinaryInputStream_ReadMatrix4(pbis, &rec->mat);
                break;
            case 8:
            case 14:
                memset(&rec->mat, 0, 0x40);
                rec->mat.mat[3][3] = 1.0f;
                rec->mat.mat[2][2] = 1.0f;
                rec->mat.mat[1][1] = 1.0f;
                rec->mat.mat[0][0] = 1.0f;
                rec->pxfSource = ReadXf(palo, pbis);
                rec->mat.mat[3][0] = -rec->pxfSource->mat.mat[3][0];
                rec->mat.mat[3][1] = -rec->pxfSource->mat.mat[3][1];
                rec->mat.mat[3][2] = -rec->pxfSource->mat.mat[3][2];
                break;
            default:
                CBinaryInputStream_ReadMatrix4(pbis, &rec->mat);
                QW dof = GetXfDofValue(rec, rec);
                rec->field_0xE0 = dof;
                rec->posGoal = dof;
                break;
            }
            func_0022C818(palo, rec);
            if (hasA) {
                actA->act.palo = palo;
                actA->act.pxf = rec;
                actA->act.priority = -1;
                actA->vec20 = GetXfDofValue(rec, rec);
                InsertXfAct(palo, rec, &actA->act);
            }
            if (hasB) {
                actB->act.palo = palo;
                actB->act.pxf = rec;
                actB->act.priority = actB->field_0x68;
                actB->vec20 = GetXfDofValue(rec, rec);
                InsertXfAct(palo, rec, &actB->act);
            }
            if (hasC) {
                actC->act.palo = palo;
                actC->act.pxf = rec;
                actC->act.priority = -1;
                InsertXfAct(palo, rec, &actC->act);
            }
            if (hasD) {
                actD->act.palo = palo;
                actD->act.pxf = rec;
                actD->act.priority = -1;
                InsertXfAct(palo, rec, &actD->act);
            }
        }
    }
    UpdateAloXfWorld(palo);
    LoadAloIkLimbs(palo, pbis);
    LoadXfMirrors(palo, pbis);
    func_0021C888(palo, pbis);
    palo->pxfLinear = ReadXf(palo, pbis);
    palo->pxfAngular = ReadXf(palo, pbis);
    palo->pxfRoot = ReadXf(palo, pbis);
    if (palo->cxf > 0) {
        if (!(palo->grfSw & 1)) {
            s32 grfEntry = palo->pgrfentry->grf;
            palo->pgrfentry->grf = grfEntry & ~0x20;
            return;
        }
        s32 grfSw = palo->grfSw;
        palo->grfSw = grfSw & ~0x20;
    }
}
