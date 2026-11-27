// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly.h"
#include "ps2inline.h"
#include "vu0inline.h"
#include "clock.h"
#include "xp.h"

// the object behind JT::field_0x4D4: only the word at 0x1BC is read
struct ATTACHEDOBJ {
    u8 unknown_0x0[0x1BC];
    s32 field_0x1BC;
};

extern "C" {
void AdjustStepNewXp(STEP *, XP *, int);
void AdjustJtZapNewXp(void *, XP *, int);
void func_001374E0(void *, XP *, int);
void func_0019E9C8(void *, XP *, int);
extern float D_002BF298;
extern float D_002BF29C;
}
void AdjustSlyNewXp(SLY *sly, XP *pxp, int iside)
{
    AdjustStepNewXp(sly, pxp, iside);
    switch (sly->jts) {
    case 8:
        func_0019E9C8(sly->PvPipe(), pxp, iside);
        break;
    case 7:
        if (pxp->kind == 0xE && sly->attachKind == 3 && sly->field_0x4D4->field_0x1BC != 0) {
            pxp->bounce = 0.0f;
            if (sly->field_0x4CC == 0) {
                pxp->friction = 0.0f;
            } else {
                QW velocity = pxp->normal;
                float length = LaneX(SqrtX(SquaredLengthXy(velocity)));
                float low = 0.5f, high = 1.5f;
                float scale = length / pxp->vecNormal.z + low;
                if (scale < low)
                    scale = low;
                else if (high < scale)
                    scale = high;
                pxp->friction = scale;
            }
        }
        break;
    case 4:
        AdjustJtZapNewXp(sly->PvZap(), pxp, iside);
        break;
    case 6:
        func_001374E0(sly->PvPart1FF0(), pxp, iside);
        break;
    case 24:
        pxp->friction = 0.0f;
        pxp->bounce = 0.0f;
        break;
    case 5:
        if ((unsigned)(sly->field_0x18D0 - 8) < 2U && g_2dded0.t - sly->field_0x18D4 < D_002BF298)
            pxp->friction = D_002BF29C;
        break;
    }
}
