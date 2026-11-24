/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
#include "ps2inline.h"
#include "so.h"
#include "jt.h"
struct SM;
struct ACTADJ;
struct XMG;
struct ALO;
/* One reader on a guessed class: UpdateJtStand reads these words of the player (Sly's region past JT's 0x1320 bytes
   that sly.h leaves unknown). Not in sly.h; names unproven. */
struct JTSTANDVIEW {
    u8 unknown_0x0[0x1514];
    /* 0x1514 */ s32 field_0x1514;
    u8 unknown_0x1518[0x8];
    /* 0x1520 */ u8 xmgLeft[0x100];
    /* 0x1620 */ u8 xmgRight[0x100];
    u8 unknown_0x1720[0x19D4 - 0x1720];
    /* 0x19D4 */ ALO *rightBall;
    /* 0x19D8 */ ALO *leftBall;
    /* 0x19DC */ ALO *rightHeel;
    /* 0x19E0 */ ALO *leftHeel;
    u8 unknown_0x19E4[0xC];
    /* 0x19F0 */ ACTADJ *leftAdj;
    /* 0x19F4 */ ACTADJ *rightAdj;
};
/* The surface object's word 0x4C is read as an LO (slot 34 called): one reader, not in lo.h. */
struct SOBASEVIEW {
    u8 unknown_0x0[0x4C];
    /* 0x4C */ LO *base;
};
extern "C" {
extern float g_2dded4;
int func_001430C8(JT *);
void SetSmaMask(void *, int);
float GLimitAbs__Fff(float, float);
void SetStepRadTarget(JT *, float);
int IsmsFindSmOptional__FP2SM3OID(SM *, int);
void SeekSma(void *, int);
int FMatchJtXmg(JT *, void *, void *);
}
void RebuildJtXmg(JT *, ALO *, float, ALO *, ACTADJ *, XMG *);
void UpdateJtStand(JT *jt)
{
    JTSTANDVIEW *view = (JTSTANDVIEW *)jt;
    SetSmaMask(jt->field_0x1034, func_001430C8(jt));
    if (jt->Slot92() == 0 && jt->psoSurface) {
        LO *base = ((SOBASEVIEW *)jt->psoSurface)->base;
        union { QW q; float f[4]; } angular;
        angular.q = base->Slot34();
        angular.f[2] = GLimitAbs__Fff(angular.f[2], 10.0f);
        SetStepRadTarget(jt, jt->radHeading + angular.f[2] * g_2dded4);
    }
    if (view->leftAdj) {
        XMG *left = (XMG *)view->xmgLeft;
        XMG *right = (XMG *)view->xmgRight;
        RebuildJtXmg(jt, view->leftBall, 5.0f, view->leftHeel, view->leftAdj, left);
        RebuildJtXmg(jt, view->rightBall, 5.0f, view->rightHeel, view->rightAdj, right);
        if (FMatchJtXmg(jt, left, view->leftAdj) == 0 || FMatchJtXmg(jt, right, view->rightAdj) == 0) {
            if (view->field_0x1514 == 0 && jt->psm) {
                if (IsmsFindSmOptional__FP2SM3OID(jt->psm, 0x17C) >= 0)
                    SeekSma(jt->field_0x1034, 0x17C);
                view->field_0x1514 = 1;
            }
        }
    }
}
