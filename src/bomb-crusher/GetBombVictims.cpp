// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "alloc.h"
#include "geom.h"
#include "oxa.h"
#include "so.h"

// the bomb: an SO whose blast radii and centre sit past SO's size (read here only)
struct BOMB : SO {
    u8 unknown_0x150[0xC];
    f32 radius;
    f32 radiusJt;
    u8 unknown_0x164[0x1C];
    QW posCenter;
};
// local view of a GEOM's kind and BSP words (inside GEOM's unknown spans; read here only)
struct GEOMBSPVIEW { u8 unknown_0x0[0xC]; s32 kind; u8 unknown_0x10[0x64]; s32 bsp; };
struct VICTIMS { s32 cgeom; GEOM **ageom; s32 cpso; };
extern "C" {
extern char B_003DD490[];
void FFilterOxaBasic();
void IntersectSwBoundingSphere(float, void *, QW, void *, void *, int *, GEOM ***);
void *PvAllocStackImpl__Fi(ALLOCREQ *);
int FIsBasicDerivedFrom(void *, int);
int CsbiIntersectSphereBsp__FP6VECTORfiP3BSPT3P4GEOMiP3SBI(QW, float, GEOM *, int, int, int, int, void *);
void SortUniquePso(void *, int *, void *);
}
extern "C" void GetBombVictims(BOMB *pbomb, int *pcpso, void **papso)
{
    ALLOCREQ req;
    char asbi[0x30];
    VICTIMS v;
    float radius = pbomb->radius;
    float radiusJt = pbomb->radiusJt;
    float query = radiusJt < radius ? radius : radiusJt;
    IntersectSwBoundingSphere(query, B_003DD490, pbomb->posCenter, (void *)FFilterOxaBasic, pbomb->poxa, &v.cgeom, &v.ageom);
    if (v.cgeom == 0) {
        *pcpso = 0;
        *papso = 0;
        return;
    }
    req.cb = v.cgeom << 2;
    req.cbAlign = 0x10;
    SO **apso = (SO **)PvAllocStackImpl__Fi(&req);
    v.cpso = 0;
    for (int igeom = 0; igeom < v.cgeom; igeom++) {
        GEOM *pgeom = v.ageom[igeom];
        SO *pso = pgeom->pso;
        SO *powner = pso->poxa->owner;
        GEOMBSPVIEW *pview = (GEOMBSPVIEW *)pgeom;
        if (pview->kind == 1)
            continue;
        if (powner == pbomb->poxa->owner)
            continue;
        if (pview->bsp != 0) {
            QW pos = pbomb->posCenter;
            float r = FIsBasicDerivedFrom(powner, 0x34) ? pbomb->radiusJt : pbomb->radius;
            if (CsbiIntersectSphereBsp__FP6VECTORfiP3BSPT3P4GEOMiP3SBI(pos, r, pgeom, 0x7FFFFFFF, 0, 0, 1, asbi) == 0)
                continue;
        }
        apso[v.cpso] = pgeom->pso;
        v.cpso = v.cpso + 1;
    }
    SortUniquePso(pbomb, &v.cpso, apso);
    *pcpso = v.cpso;
    *papso = apso;
}
