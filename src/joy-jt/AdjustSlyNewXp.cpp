// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly.h"
#include "ps2inline.h"
#include "vu0inline.h"
#include "clock.h"

// the record the step's AdjustStepNewXp (slot 55) fills: the move the object makes this frame (ZAPXP, jtzap.h, sees the same 0x94 and 0x98)
struct NEWXP {
    u8 unknown_0x0[0x80];
    union {
        /* 0x80 */ QW vel;       // the velocity AdjustSlyNewXp measures in state 7 (a quadword; its z lane, 0x88, is the divisor)
        f32 afl[4];
    };
    u8 unknown_0x90[0x4];
    /* 0x94 */ f32 field_0x94;
    /* 0x98 */ s32 field_0x98;
    /* 0x9C */ s32 field_0x9C; // 0xE selects the attached case of state 7
};

// the object behind JT::field_0x4D4: only the word at 0x1BC is read
struct ATTACHEDOBJ {
    u8 unknown_0x0[0x1BC];
    s32 field_0x1BC;
};

extern "C" {
void AdjustStepNewXp(STEP *, NEWXP *, int);
void AdjustJtZapNewXp(void *, NEWXP *, int);
void func_001374E0(void *, NEWXP *, int);
void func_0019E9C8(void *, NEWXP *, int);
extern float D_002BF298;
extern float D_002BF29C;
}
void AdjustSlyNewXp(SLY *sly, NEWXP *pxp, int iside)
{
    AdjustStepNewXp(sly, pxp, iside);
    switch (sly->jts) {
    case 8:
        func_0019E9C8(sly->PvPipe(), pxp, iside);
        break;
    case 7:
        if (pxp->field_0x9C == 0xE && sly->attachKind == 3 && sly->field_0x4D4->field_0x1BC != 0) {
            pxp->field_0x98 = 0;
            if (sly->field_0x4CC == 0) {
                pxp->field_0x94 = 0.0f;
            } else {
                QW velocity = pxp->vel;
                float length = LaneX(SqrtX(SquaredLengthXy(velocity)));
                float low = 0.5f, high = 1.5f;
                float scale = length / pxp->afl[2] + low;
                if (scale < low)
                    scale = low;
                else if (high < scale)
                    scale = high;
                pxp->field_0x94 = scale;
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
        pxp->field_0x94 = 0.0f;
        pxp->field_0x98 = 0;
        break;
    case 5:
        if ((unsigned)(sly->field_0x18D0 - 8) < 2U && g_2dded0.t - sly->field_0x18D4 < D_002BF298)
            pxp->field_0x94 = D_002BF29C;
        break;
    }
}
