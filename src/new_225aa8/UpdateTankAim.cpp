// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "ps2inline.h"
#include "vu0inline.h"
#include "tank.h"
#include "guard.h"
#include "sw.h"
#include "cref.h"
#include "clock.h"
struct Locals_225BA0 { MATRIX3Q rotation; MATRIX3Q lookAt; float pan; float tilt; };
struct SAVE;
struct SMP;
extern "C" {
extern SAVE B_003D4A60;
extern SW B_003DD490;
extern unsigned int D_002C4408[4]; /* src/data/new_225aa8.cpp; GSmooth reads it as an SMP */
CRef RefGetGameSaveValue(SAVEPATH *, SAVE *);
void DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1(MATRIX3Q *, float *, float *);
float GLimitAbs__Fff(float, float);
float GLimitLm__FP2LMf(LM *, float);
float GSmooth__FfffP3SMPPf(float, float, float, SMP *, float *);
void LoadLookAtMatrix(MATRIX3Q *, QW);
QW PosLoWorld(LO *);
void func_0012D108(ACT *, QW);
void UpdateTankAim(TANK *self) {
    if (self->ploAim != 0 && self->fAim != 0) {
        Locals_225BA0 l;
        MATRIX3Q *plookAt = &l.lookAt;
        QW targetPosition = PosLoWorld(self->ploAim);
        QW direction = VectorSub(targetPosition, PosLoWorld(self));
        LoadLookAtMatrix(plookAt, direction);
        l.rotation = l.lookAt;
        DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1(&l.rotation, &l.pan, &l.tilt);
        float panDelta = l.pan - self->pan;
        self->pan = l.pan;
        float tiltDelta = l.tilt - self->tilt;
        self->tilt = l.tilt;
        self->panRate = panDelta;
        self->tiltRate = tiltDelta;
    } else {
    if (self->pjoy != 0) {
            float stickX = GLimitAbs__Fff(self->pstick()->xLeft + self->pstick()->xRight, 1.0f);
            float stickY = GLimitAbs__Fff(self->pstick()->yLeft, 1.0f);
            float skill = self->skill;
            float scale = (((1.0f - skill) * 0.5f) + skill) * 10.0f;
            float panAccel = -stickX * stickX * stickX * scale;
            float limit = skill * 1.3f;
            if (panAccel * self->panRate <= 0.0f) {
                self->panRate = 0.0f;
            }
            float tiltAccel = stickY * stickY * stickY * scale;
            int invert = RefGetGameSaveValue(B_003DD490.psavepathReverseAim, &B_003D4A60).m_tag.m_n;
            if (invert == 0) {
                tiltAccel = -tiltAccel;
            }
            if (tiltAccel * self->tiltRate <= 0.0f) {
                self->tiltRate = 0.0f;
            }
            self->panRate = GSmooth__FfffP3SMPPf(self->panRate, 0.0f, g_2dded0.dt, (SMP *)D_002C4408, 0);
            self->tiltRate = GSmooth__FfffP3SMPPf(self->tiltRate, 0.0f, g_2dded0.dt, (SMP *)D_002C4408, 0);
            self->panRate = GLimitAbs__Fff(self->panRate + panAccel * g_2dded0.dt, limit * 0.9f);
            float newTilt = GLimitAbs__Fff(self->tiltRate + tiltAccel * g_2dded0.dt, limit * 0.8f);
            self->tiltRate = newTilt;
            self->pan = self->pan + self->panRate * g_2dded0.dt;
            self->tilt = self->tilt + newTilt * g_2dded0.dt;
        }
    }
    self->pan = GLimitLm__FP2LMf(&self->lmPan, self->pan);
    float tilt = GLimitLm__FP2LMf(&self->lmTilt, self->tilt);
    self->tilt = tilt;
    if (self->fRotAct != 0) {
        union VU_VECTOR { QW q; VECTOR v; } vector;
        vector.q = VectorFromFloats3(0.0f, -tilt, self->pan);
        func_0012D108(self->pact, vector.q);
    }
}
}
