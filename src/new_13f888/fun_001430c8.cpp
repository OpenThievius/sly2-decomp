// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "ps2inline.h"
#include "jt.h"
extern "C" {
QW PosLoWorld(void *);
QW ConvertAloPos(void *, JT *, QW);
float atan2f(float, float);
extern float D_FLT_002BD2C0;
extern float D_FLT_002BD2C4;
}
/* One reader on a guessed class: func_001430C8 reads these two words of a JT. Not in jt.h (one reader). */
struct JTAIMVIEW {
    u8 unknown_0x0[0x10F8];
    /* 0x10F8 */ void *field_0x10F8;
    /* 0x10FC */ s32 field_0x10FC;
};
extern "C" int func_001430C8(JT *pjt)
{
    const JTAIMVIEW *view = (const JTAIMVIEW *)pjt;
    int quadrant;
    if (view->field_0x10F8) {
        QW pos = ConvertAloPos(0, pjt, PosLoWorld(view->field_0x10F8));
        float x = LaneX(pos);
        float y = LaneX(RotateWords3(pos));
        float angle = atan2f(y, x);
        float magnitude = angle < 0.0f ? -angle : angle;
        if (magnitude < D_FLT_002BD2C0)
            quadrant = 0;
        else if (D_FLT_002BD2C4 < magnitude)
            quadrant = 3;
        else if (0.0f < angle)
            quadrant = 1;
        else
            quadrant = 2;
    }
    int mask = 8;
    switch (view->field_0x10FC) {
    case -1:
    case 0: break;
    case 1: mask = 0x10 << quadrant; break;
    case 2: mask = 0x100 << quadrant; break;
    case 3: mask = 0x1000; break;
    case 4: mask = 0x100; break;
    }
    return mask;
}
