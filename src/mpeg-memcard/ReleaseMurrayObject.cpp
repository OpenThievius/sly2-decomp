// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "murray.h"
#include "carry.h"
extern const QW D_002C09E0;
extern const QW g_2a2dd0;
extern "C" {
void DetachMurrayObject(MURRAY *);
int FIsBasicDerivedFrom(LO *, int);
void func_00209EE0(LO *);
void func_001F7A68(LO *, int);
void SetSmaGoal__FP3SMA3OID(SMA *, int);
QW bevy_camera_follow_track_heading_weight(MURRAY *, int, QW);
}

void ReleaseMurrayObject(MURRAY *pmurray)
{
    if (pmurray->state == 6) {
        if (pmurray->psmaPartner != 0)
            SetSmaGoal__FP3SMA3OID(pmurray->psmaPartner, 0x1CA);
        return;
    }
    LO *pobj = pmurray->ploCarried;
    if (pobj == 0) return;
    if (pmurray->state == 4 && pmurray->field_0x1450 == 0) {
        pobj->HandleSpliceEvent(6, 0, 0, 0, 0);
        pmurray->ploCarried = 0;
        return;
    }
    DetachMurrayObject(pmurray);
    LO *plo = ((CARRY *)pmurray->ploCarried)->pso;
    if (FIsBasicDerivedFrom(plo, 0x38) != 0)
        func_00209EE0(plo);
    else
        func_001F7A68(plo, 1);
    switch (pmurray->state) {
    case 5:
        plo->Slot35(bevy_camera_follow_track_heading_weight(pmurray, 0, D_002C09E0));
        break;
    case 2:
    case 4:
    case 7:
    case 8:
        plo->Slot35(g_2a2dd0);
        break;
    }
    pmurray->ploCarried = 0;
}
