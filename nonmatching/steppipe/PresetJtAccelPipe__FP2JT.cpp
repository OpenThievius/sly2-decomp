// SPDX-License-Identifier: GPL-3.0-or-later
#include "vu0inline.h"
#include "ps2inline.h"
#include "sly2.h"
#include "jt.h"

struct MATRIX3Q { QW row[3]; };
struct JTPIPE {
    /* 0x0 */ JT *pjt;
    /* 0x4 */ int state;
    u8 unknown_0x8[0x4];
    /* 0xC */ JT *pjtGoal;
    /* 0x10 */ float u;
    u8 unknown_0x14[0x4];
    /* 0x18 */ int fFlag;
};
struct WORLDTIME { u8 unknown_0x0[0x14]; };
struct WORLDCLOCK { u8 unknown_0x0[0x74]; float t; };
struct JTWORLD { u8 unknown_0x0[0x14]; WORLDCLOCK *pclock; u8 unknown_0x18[0x4]; float tDelta; };

extern "C" {
MATRIX3Q *PmatLoWorld(void *);
void MatMulMatTransMat(MATRIX3Q *pmatOut, MATRIX3Q *pmatLeft, MATRIX3Q *pmatRight);
void EvaluateBezierMat(float dt, float t, float gScale, MATRIX3Q *pmatStart, QW wStart, MATRIX3Q *pmatEnd, QW wEnd, MATRIX3Q *pmatOut, QW *pwOut);
extern QW g_2a2dd0;
extern float g_2dded0[];
}
void GetJtPipeGoalMat__FP2JTP4PIPEfP7MATRIX3(JT *pjt, int fFlag, float u, MATRIX3Q *pmat);
void DecomposeRotateMatrixRad__FP7MATRIX3PfP6VECTOR(MATRIX3Q *pmat, float *pRad, VECTOR *pAxis);

void PresetJtAccelPipe(JT *pipeJt)
{
    JTPIPE *ppipe = (JTPIPE *)pipeJt;
    MATRIX3Q matGoal;
    MATRIX3Q matTarget;
    MATRIX3Q matRot;
    VECTOR axis;
    MATRIX3Q matDelta;
    float rad;
    GetJtPipeGoalMat__FP2JTP4PIPEfP7MATRIX3(ppipe->pjtGoal, ppipe->fFlag == 0, ppipe->u, &matGoal);
    MATRIX3Q *pmatUse;
    if (ppipe->state == 0 || ppipe->state == 4) {
        float tNow = g_2dded0[1];
        JTWORLD *pworld = (JTWORLD *)ppipe->pjt->field_0x1030;
        float tRemain = pworld->pclock->t - pworld->tDelta;
        float dt = tNow > tRemain ? tNow : tRemain;
        MATRIX3Q *pmatJt = PmatLoWorld(ppipe->pjt);
        QW w = ppipe->pjt->Slot34();
        EvaluateBezierMat(dt, tNow, 1.0f, pmatJt, w, &matGoal, g_2a2dd0, &matTarget, 0);
        pmatUse = &matTarget;
    } else {
        matTarget = matGoal;
        pmatUse = &matTarget;
    }
    MatMulMatTransMat(&matDelta, PmatLoWorld(ppipe->pjt), pmatUse);
    matRot = matDelta;
    DecomposeRotateMatrixRad__FP7MATRIX3PfP6VECTOR(&matRot, &rad, &axis);
    ppipe->pjt->Slot36(GeneralFromVector(VectorScaleX(*(QW *)&axis, VectorFromFloat(rad / g_2dded0[1]))));
}
