// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "guard.h"
#include "stepguard.h"
#include "sw.h"
extern SW B_003DD490;
extern "C" {
void LoadDirAnimSet(void *pdiranims);
void LoadJumpAnim(void *pjumpanim, LO *ploOwner);
LO *PloFindSwObject_thunk(SW *, int, int, LO *);
int CidGetBasic(LO *);
void *PeaFindAsegLabel(LO *, int);
void *func_0020C010(u32 cb);
void func_0020BD78(JUMPANIM *);
}

void BindAnimref(ANIMREF *ref, STEPGUARD *owner)
{
    if (ref->kind != 2) {
        if (ref->kind == 3) {
            LoadDirAnimSet(ref->pdata);
            return;
        }
    } else {
        LoadJumpAnim(ref->pdata, owner);
        return;
    }
    LO *plo = PloFindSwObject_thunk(&B_003DD490, 4, ref->oid, owner);
    if (plo != 0) {
        switch (CidGetBasic(plo)) {
        case 0x6D:
            if (PeaFindAsegLabel(plo, 0x22) != 0) {
                ref->kind = 2;
                ref->pdata = func_0020C010(0x40);
                func_0020BD78((JUMPANIM *)ref->pdata);
                ((JUMPANIM *)ref->pdata)->pobject = plo;
                LoadJumpAnim(ref->pdata, owner);
                if ((s32)ref->grf == -1) ref->grf = 0;
            } else {
                ref->pdata = plo;
                ref->kind = 0;
            }
            return;
        case 0x6F:
            ref->kind = 1;
            ref->pdata = plo;
            if ((s32)ref->grf == -1) ref->grf = 0;
            return;
        default:
            ref->kind = -1;
            return;
        }
    }
    ref->kind = -1;
}
