// SPDX-License-Identifier: GPL-3.0-or-later
#include "cplcy.h"
#include "amb.h"
#include "sly2.h"
struct SMP { float a, b, c, d; };
struct Rows { QW row[3]; };
struct M4x { Rows rot; QW pos; }; /* MATRIX4 viewed as three rotation rows and a position */
static inline float Ratio(float value, float low, float high) {
    if (low == high) return 0.0f;
    return (value - low) / (high - low);
}
static inline float Clamp(float value, float low, float high) {
    if (value < low) return low;
    if (high < value) return high;
    return value;
}
extern "C" {
void ContinueAmb(AMB *);
QW DecomposeRotateMatrixEuler(Rows *);
void DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1(M4x *, float *, float *);
float GLimitLm__FP2LMf(void *, float);
float GSmooth__FfffP3SMPPf(float, float, float, SMP *, float *);
void LoadRotateMatrixEuler__FP6VECTORP7MATRIX3(Rows *, QW);
void PauseAmb(AMB *);
QW PosSmooth(QW, QW, SMP *, float *, float);
float RadSmooth__FfffP3SMPPf(float, float, float, SMP *, float *);
void SetAmbPitch(AMB *, float);
void SetAmbVolume(AMB *, float);
void SetCmFov(void *, float);
void SetCmLookAt(void *, float, float, QW, QW);
void SetCmPosMat(void *, M4x *);
void SmoothMatrix(float, Rows *, Rows *, SMP *, Rows *, QW *);
void UpdateCplcy();
s32 __as__6VECTORG9VU_VECTOR(void *, QW);
QW bevy_classes_k30_cam_150780(K30CAM *);
QW bevy_classes_k30_cam_1507f8(K30CAM *);
extern float B_003E1BE0;
extern SMP D_002BBB68;
extern SMP D_002BD9B8, D_002BD9C8, D_002BD9D8, D_002BD9E8, D_002BD9F8;
extern char g_2bbb60[];
extern float g_2dded0[];
// Retail (0x150A28): smooths the blend toward the goal and clamps it with the 1.0 bound in $f1 loaded before the
// first compare: a three-argument Clamp(value, low, high) helper, whose arguments are evaluated before its body,
// gives that order (Clamp01 with literals in the body loaded 1.0 after the branch). The camera matrix gets rows
// 1 and 2 and pos.w = 1.0 through a pointer register ($s1 = matrix, also SetCmPosMat's argument) while the three
// row w = 0 stores are $sp-relative: the rows and pos.w go through `matrix`, the w zeros through the stack object.
// The w zeros are written last to first (retail emits 0xEC, 0xDC, 0xCC). Still differs: rows 0 and 1 of the copy
// get $v0/$v1 swapped (score 4, local register allocation).
void bevy_classes_k30_cam_update(K30CAM *self) {
    Rows prev;
    Rows next;
    Rows out;
    Rows tmp;
    M4x placed;
    UpdateCplcy();
    if (g_2dded0[1] != 0.0f) {
        if (self->minDistance >= 0.0f) {
            float smoothed = GSmooth__FfffP3SMPPf(self->distance, self->minDistance, g_2dded0[1], &D_002BD9B8, 0);
            float clamped = Clamp(smoothed, 0.0f, 1.0f);
            float delta = clamped - self->distance;
            self->rate = delta / g_2dded0[1];
            self->distance = clamped;
        }
        float rate = self->rate;
        if (rate != 0.0f) {
            AMB *ambA = (AMB *)self->field_0xC0;
            SetAmbPitch(ambA, GLimitLm__FP2LMf(&D_002BBB68, __builtin_fabsf(rate)));
            AMB *ambB = (AMB *)self->field_0xC0;
            SetAmbVolume(ambB, GLimitLm__FP2LMf(g_2bbb60, __builtin_fabsf(self->rate) * 0.5f + 0.5f));
            AMB *ambC = (AMB *)self->field_0xC0;
            if (ambC->cPause > 0) ContinueAmb(ambC);
        } else {
            AMB *amb = (AMB *)self->field_0xC0;
            if (amb->cPause <= 0) PauseAmb(amb);
        }
        if (self->active != 0) {
            self->previousPosition = PosSmooth(self->previousPosition, self->currentPosition, &D_002BD9C8, 0, g_2dded0[1]);
            LoadRotateMatrixEuler__FP6VECTORP7MATRIX3(&tmp, self->previousTarget);
            prev = tmp;
            LoadRotateMatrixEuler__FP6VECTORP7MATRIX3(&tmp, self->currentTarget);
            next = tmp;
            SmoothMatrix(g_2dded0[1], &prev, &next, &D_002BD9D8, &out, 0);
            self->previousTarget = DecomposeRotateMatrixEuler(&out);
            self->previousDistance = RadSmooth__FfffP3SMPPf(self->previousDistance, self->currentDistance, g_2dded0[1], &D_002BD9E8, 0);
            __as__6VECTORG9VU_VECTOR(&placed.pos, self->previousPosition);
            M4x *matrix = &placed;
            matrix->rot = out;
            ((float *)&placed.rot.row[2])[3] = 0.0f;
            ((float *)&placed.rot.row[1])[3] = 0.0f;
            ((float *)&placed.rot.row[0])[3] = 0.0f;
            ((float *)&matrix->pos)[3] = 1.0f;
            SetCmPosMat(&B_002DDF40, matrix);
            SetCmFov(&B_002DDF40, self->previousDistance);
            DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1(&placed, &self->radPan, &self->radTilt);
            self->distance = GLimitLm__FP2LMf(g_2bbb60, Ratio(self->previousDistance, self->fovMin, self->fovMax));
        } else {
            float inverse = 1.0f - self->distance;
            SetCmFov(&B_002DDF40, (1.0f - inverse) * self->fovMin + inverse * self->fovMax);
            QW old30 = self->target;
            QW goal30 = bevy_classes_k30_cam_1507f8(self);
            self->target = PosSmooth(old30, goal30, &D_002BD9F8, 0, g_2dded0[1]);
            QW old20 = self->position;
            QW goal20 = bevy_classes_k30_cam_150780(self);
            QW look = PosSmooth(old20, goal20, &D_002BD9F8, 0, g_2dded0[1]);
            self->position = look;
            SetCmLookAt(&B_002DDF40, 0.0f, 0.0f, self->target, look);
        }
        B_003E1BE0 = g_2dded0[0];
    }
}
}
