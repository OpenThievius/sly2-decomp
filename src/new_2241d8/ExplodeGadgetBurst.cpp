// SPDX-License-Identifier: GPL-3.0-or-later
#include "gadgetobj.h"
#include "geom.h"
#include "sw.h"
#include "sly2.h"
#include "vu0inline.h"
extern SW B_003DD490;
extern int D_002C4368[];
extern float D_002C4338[];
struct BURSTENTRY { u8 unknown_0x0[0x60]; };
extern "C" {
void CStackFrame_Construct(void *);
void CStackFrame_Destructor(void *, int);
void IntersectSwBoundingSphere(SW *, QW, void *, void *, float, int *, GEOM ***);
QW SetVectorSphere__FP6VECTORfff(float, float, float);
QW LimitVectorLength__FP6VECTORfT0(QW, float);
void AddGadgetBurstWkr(GADGETOBJ *, int, int, QW, QW, int, GEOM **, int, int *, BURSTENTRY *);
void PaloAbsorbWkr(BURSTENTRY *);
int *PhitfxSpawn(int, QW, LO *);
void FFilterOxaBasic();
}
extern "C" void ExplodeGadgetBurst(GADGETOBJ *pgadget, int word1, int word2, QW origin, float fradius)
{
    char frame[0x10];
    BURSTENTRY aentry[32];
    int cgeom;
    GEOM **ageom;
    int centry;
    CStackFrame_Construct(frame);
    IntersectSwBoundingSphere(&B_003DD490, origin, (void *)FFilterOxaBasic, pgadget->poxa, fradius, &cgeom, &ageom);
    centry = 0;
    for (unsigned int iring = 0; iring < 11; iring++) {
        for (int ipoint = 0; ipoint < D_002C4368[iring]; ipoint++) {
            QW offset = SetVectorSphere__FP6VECTORfff(2.0f * (float)ipoint * 3.1415927f / (float)D_002C4368[iring], D_002C4338[iring], fradius);
            QW pos = VectorAdd(origin, offset);
            AddGadgetBurstWkr(pgadget, word1, word2, origin, pos, cgeom, ageom, 0x20, &centry, aentry);
        }
    }
    for (int igeom = 0; igeom < cgeom; igeom++) {
        QW delta = VectorSub(ageom[igeom]->pxf->matWorld.row[3], origin);
        QW offset = LimitVectorLength__FP6VECTORfT0(delta, fradius);
        QW pos = VectorAdd(origin, offset);
        AddGadgetBurstWkr(pgadget, word1, word2, origin, pos, cgeom, ageom, 0x20, &centry, aentry);
    }
    for (int ientry = 0; ientry < centry; ientry++)
        PaloAbsorbWkr(&aentry[ientry]);
    PhitfxSpawn(B_003DD490.field_0x402C, origin, pgadget)[0x15] = 1;
    CStackFrame_Destructor(frame, 2);
}
