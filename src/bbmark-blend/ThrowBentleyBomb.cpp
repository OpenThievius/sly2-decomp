// SPDX-License-Identifier: GPL-3.0-or-later
#include "bentley.h"
#include "sly2.h"
struct LAUNCH { u8 unknown_0x0[0x50]; QW vecTarget; s32 field_0x60; };
struct GEOM { u8 unknown_0x0[0x18]; s32 grf; };
extern QW g_2a2dd0;
extern float g_2dded0;
extern "C" {
void CalcBentleyBombTarget(BENTLEY *);
SO *PloLeaseCloneObject(int, int);
void LaunchSoAtTarget(LAUNCH *, SO *);
void PrimeBomb__FP4BOMBf(SO *, float);
void SetBentleyAimState(BENTLEY *, int);
}
void ThrowBentleyBomb(BENTLEY *pbentley, int grfGeom)
{
    CalcBentleyBombTarget(pbentley);
    int ppool;
    switch (pbentley->field_0x16D8) {
    case 0:
        ppool = pbentley->field_0x16DC;
        break;
    case 1:
        ppool = pbentley->field_0x16E0;
        break;
    default:
        return;
    }
    if (ppool == 0)
        return;
    SO *pbomb = PloLeaseCloneObject(ppool, 0);
    if (pbomb == 0)
        return;
    pbomb->ageom->grf = grfGeom;
    LAUNCH *plaunch = pbentley->field_0x16E4;
    plaunch->field_0x60 = 0;
    plaunch->vecTarget = pbentley->posTarget;
    LaunchSoAtTarget(plaunch, pbomb);
    pbomb->Slot36(g_2a2dd0);
    PrimeBomb__FP4BOMBf(pbomb, 4.0f);
    SetBentleyAimState(pbentley, 1);
    pbentley->field_0x1700 = g_2dded0;
}
