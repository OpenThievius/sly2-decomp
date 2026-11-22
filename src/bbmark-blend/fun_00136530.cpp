// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "clock.h"
#include "bentley.h"
#include "murray.h"
#include "so.h"
#include "xf.h"
extern "C" {
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

/* what func_00136530 keeps per state: a view of BENTLEY (one reader each; not a method of the class) */
struct BENTLEYPOSE {
    u8 unknown_0x0[0x1804];
    /* 0x1804 */ f32 field_0x1804; /* the clock time when field_0x1800 changes */
    /* 0x1808 */ ASEG *apasegState[2]; /* applied per state (0 and 1) */
    /* 0x1810 */ ACT *field_0x1810; /* the act it starts on pxfLinear in state 0 */
    /* 0x1814 */ ACT *field_0x1814; /* the same on pxfAngular */
};

extern "C" void func_00136530(BENTLEY *pbentley, int state)
{
    if (state == pbentley->field_0x1800)
        return;
    switch (pbentley->field_0x1800) {
    case 0: {
        int saved = pbentley->field_0x9E4;
        func_001A58D0(pbentley, 0, 0xF);
        pbentley->field_0x9E4 = saved;
        func_0012E460(&((BENTLEYPOSE *)pbentley)->field_0x1810);
        func_0012E460(&((BENTLEYPOSE *)pbentley)->field_0x1814);
        SetXfKind(pbentley, pbentley->pxfLinear, 2);
        SetXfKind(pbentley, pbentley->pxfAngular, 2);
        break;
    }
    case 1:
        SetStepRadTarget(pbentley, RadYawSo(pbentley));
        pbentley->fLock = 0;
        FixStepAngularVelocity(pbentley);
        break;
    }
    pbentley->field_0x1800 = state;
    ((BENTLEYPOSE *)pbentley)->field_0x1804 = g_2dded0.t;
    void *paseg = ((BENTLEYPOSE *)pbentley)->apasegState[state];
    switch (state) {
    case -1:
        if (g_2f7900->state == 0xF && g_2f7900->stateCarry != 7)
            CarryThrow_SetState(g_2f7900->PvCarry(), 0);
        return;
    case 0: {
        MATRIX4 mat;
        SO *pso = g_2f7900->psoCarry;
        void *pxf = pso->Slot32(&mat);
        mat = ConvertXfMatrix4(pbentley->axf->pxfParent, pbentley->pxfLinear->pxfParent, &mat);
        int saved = pbentley->field_0x9E4;
        pbentley->SetParent(g_2f7900, pxf, 3);
        pbentley->field_0x9E4 = saved;
        pbentley->Slot35(g_2a2dd0);
        pbentley->Slot36(g_2a2dd0);
        ((BENTLEYPOSE *)pbentley)->field_0x1810 = func_0012DC18(pbentley, pbentley->pxfLinear, 1, 7, 2, mat.row[3]);
        ((BENTLEYPOSE *)pbentley)->field_0x1814 = func_0012DC18(pbentley, pbentley->pxfAngular, 1, 7, 2, DecomposeRotateMatrixEuler(&mat));
        break;
    }
    case 1:
        pbentley->fLock = -1;
        break;
    }
    RetractSmaRef(&pbentley->field_0x1034);
    ApplyAsegToHandle(paseg, pbentley, 9, &pbentley->field_0x1030, 0.0f, 1.0f);
    pbentley->Slot90();
}
