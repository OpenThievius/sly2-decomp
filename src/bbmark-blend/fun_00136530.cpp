// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "bentley.h"
#include "murray.h"
#include "so.h"
#include "xf.h"
#define FIELD(type, base, offset) (*(type *)((char *)(base) + (offset)))
struct ACT;
/* the animation per state, after BENTLEY::field_0x1800 and the time it was set (0x1804) */
struct BENTLEYASEG_136530 { u8 unknown_0x0[0x1808]; void *apaseg[3]; };
extern "C" {
struct CLOCK_136530 { float t; float dt; };
extern CLOCK_136530 g_2dded0;
extern QW g_2a2dd0;
extern MURRAY *g_2f7900;
void func_001A58D0(void *, int, int);
void func_0012E460(void *);
void SetXfKind(void *, XF *, int);
float RadYawSo(void *);
void SetStepRadTarget(void *, float);
void CarryThrow_SetState(void *, int);
MATRIX4 ConvertXfMatrix4(XF *, XF *, MATRIX4 *);
QW DecomposeRotateMatrixEuler(MATRIX4 *);
ACT *func_0012DC18(void *, XF *, int, int, int, QW);
void RetractSmaRef(void *);
void ApplyAsegToHandle(void *, void *, int, void *, float, float);
}
void FixStepAngularVelocity(STEP *);

extern "C" void func_00136530(BENTLEY *pbentley, int state)
{
    if (state == pbentley->field_0x1800)
        return;
    switch (pbentley->field_0x1800) {
    case 0: {
        int saved = FIELD(int, pbentley, 0x9E4);
        func_001A58D0(pbentley, 0, 0xF);
        FIELD(int, pbentley, 0x9E4) = saved;
        func_0012E460((char *)pbentley + 0x1810);
        func_0012E460((char *)pbentley + 0x1814);
        SetXfKind(pbentley, pbentley->pxfLinear, 2);
        SetXfKind(pbentley, pbentley->pxfAngular, 2);
        break;
    }
    case 1:
        SetStepRadTarget(pbentley, RadYawSo(pbentley));
        FIELD(int, pbentley, 0x1A4) = 0;
        FixStepAngularVelocity(pbentley);
        break;
    }
    pbentley->field_0x1800 = state;
    FIELD(float, pbentley, 0x1804) = g_2dded0.t;
    void *paseg = ((BENTLEYASEG_136530 *)pbentley)->apaseg[state];
    switch (state) {
    case -1:
        if (g_2f7900->state == 0xF && FIELD(int, g_2f7900, 0x1914) != 7)
            CarryThrow_SetState((char *)g_2f7900 + 0x1910, 0);
        return;
    case 0: {
        MATRIX4 mat;
        SO *pso = FIELD(SO *, g_2f7900, 0x191C);
        void *pxf = pso->Slot32(&mat);
        mat = ConvertXfMatrix4(FIELD(XF *, pbentley, 0x54)->pxfParent, pbentley->pxfLinear->pxfParent, &mat);
        int saved = FIELD(int, pbentley, 0x9E4);
        pbentley->SetParent(g_2f7900, pxf, 3);
        FIELD(int, pbentley, 0x9E4) = saved;
        pbentley->Slot35(g_2a2dd0);
        pbentley->Slot36(g_2a2dd0);
        FIELD(ACT *, pbentley, 0x1810) = func_0012DC18(pbentley, pbentley->pxfLinear, 1, 7, 2, mat.row[3]);
        FIELD(ACT *, pbentley, 0x1814) = func_0012DC18(pbentley, pbentley->pxfAngular, 1, 7, 2, DecomposeRotateMatrixEuler(&mat));
        break;
    }
    case 1:
        FIELD(int, pbentley, 0x1A4) = -1;
        break;
    }
    RetractSmaRef(&pbentley->field_0x1034);
    ApplyAsegToHandle(paseg, pbentley, 9, &pbentley->field_0x1030, 0.0f, 1.0f);
    pbentley->Slot90();
}
