// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "alloc.h"
#include "dl.h"
#include "pzo_hide.h"
#include "geom.h"

extern "C" {
extern s32 B_003DD490[];
s32 PloFindSwObject_thunk(void *, s32, s32, SWARM *);
void InitDl__FP2DLi(DL *, s32);
void AppendDlEntry(DL *, void *);
void *PvAllocSwClearImpl__Fi(ALLOCREQ *);
void func_0017F138(SWARM *);
void AddSoGeomsToOxa(SWARM *);

void Swarm_PostLoad(SWARM *self)
{
    s32 index;
    s32 count;
    for (index = 0; index < self->cgroup; index++) {
        SWARMGROUP *group = &self->agroup[index];
        group->pcrv = (CRV *)PloFindSwObject_thunk(B_003DD490, 4, group->oid, self);
        if (group->pcrv == 0) {
            index--;
            self->cgroup = self->cgroup - 1;
        } else {
            InitDl__FP2DLi(&group->dl, 0x60);
            for (count = 0; count < group->total; count++) {
                ALLOCREQ request;
                request.cb = 0x70;
                request.cbAlign = 0x10;
                SWARMRIDER *rider = (SWARMRIDER *)PvAllocSwClearImpl__Fi(&request);
                rider->group = group;
                rider->state = -1;
                AppendDlEntry(&group->dl, rider);
            }
        }
    }
    func_0017F138(self);
    GEOM *geom = &self->ageom[self->cgeom++];
    geom->pxf = self->pxfRoot;
    geom->alo = -1;
    geom->pso = self;
    geom->grf |= 0x8000L << 33;
    geom->grf |= 0x8000L << 34;
    if ((int)(self->grfo >> 0x3C) & 1) {
        AddSoGeomsToOxa(self);
    }
}
}
