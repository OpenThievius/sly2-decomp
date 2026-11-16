// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "sly.h"
#include "ps2inline.h"
#include "vu0inline.h"

union VU_SCALE { QW q; VECTOR v; };

/* the controller's left stick: its direction and how far it is pushed */
struct JOY {
    u8 unknown_0x0[0x18];
    /* 0x18 */ f32 radStick;
    /* 0x1C */ f32 uStick;
};

struct CURVEVT { char pad[0x18]; short delta; short index; void (*fn)(void *, float, float, VECTOR *, VECTOR *); };
struct CURVE { CURVEVT *vt; };
struct CHN { char p0[4]; CURVE *curve; };
struct ASEGA { char p0[0x14]; void *seg; char p1[0x1C - 0x18]; float t; char p2[0x40 - 0x20]; float rate; };

extern "C" {
extern char D_3DD490[];
extern QW g_2a2dd0;
extern float D_002BF35C;
extern float D_002BF3C0;
extern float D_002BF3C4;
extern float D_FLT_002BF3C8;
extern float D_002BF3CC;
float RadYawSo(SLY *);
void BuildJtTargetList(void *, SLY *, int);
void UpdateJtBinocInput(SLY *);
void UpdateJtStateTransitions(SLY *);
void UpdateJtCaneInput(SLY *);
void UpdateJtActiveHang__FP2JTP3JOY(SLY *);
void bevy_player_p18_gadget_glide_steer(void *);
void UpdateAttachMotion(void *);
void bevy_player_p25_137218(void *);
void SetJtGoalVelocityFromStick(SLY *, void *, void *, float, float);
void func_0018B460(SLY *);
void SetRunBlendU(void *, float);
void SetStepRadTarget(SLY *, float);
void func_002046F0(SLY *, int);
QW SetVectorCylind__FP6VECTORfff(float, float, float);
QW bevy_camera_follow_track_heading_weight(void *, void *, QW);
int FGadgetAcquired(int);
void func_0018E1E0(SLY *);
CHN *PchnFindAseg(void *, void *, int, int);
QW func_00204E38(float, SLY *, ASEGA *);
void SetAsegaSpeed(SLY *, float);
void DrainJtPower(SLY *, float);
void SetJtState(SLY *, int, int);
void ReblendAsegbl(void *);
void UpdateZapPost(void *);
void UpdateJtSafePoints(SLY *);
int FAsegaGone(int);
void ReleaseAsegaHandle(void *);
}
float RadNormalize(float);
/* the larger of two floats (g++'s >? operator) */
static inline float GMax(float a, float b) { return a >? b; }
float GLimitAbs(float, float);


extern "C" void bevy_player_input_from_pad_cm(SLY *psly)
{
    RadNormalize(psly->pjoy->radStick - RadYawSo(psly));
    BuildJtTargetList(D_3DD490, psly, 0xFFFF);
    UpdateJtBinocInput(psly);
    UpdateJtStateTransitions(psly);
    UpdateJtCaneInput(psly);
    switch (psly->jts) {
    case 0:
    case 1:
        break;
    case 4:
    case 9: {
        ASEGA *pasega = (ASEGA *)psly->field_0x1030;
        psly->velGoal = g_2a2dd0;
        if (pasega) {
            CHN *pchn = PchnFindAseg(pasega->seg, psly, 1, 1);
            if (pchn) {
                VU_SCALE vel;
                CURVE *pcurve = pchn->curve;
                pcurve->vt->fn((char *)pcurve + pcurve->vt->delta, pasega->t, pasega->rate, 0, &vel.v);
                VU_SCALE scale;
                scale.q = VectorFromFloat(-1.0f);
                psly->velGoal = VectorScaleX(vel.q, scale.q);
            }
        }
        break;
    }
    case 3:
        UpdateJtActiveHang__FP2JTP3JOY(psly);
        break;
    case 2:
        bevy_player_p18_gadget_glide_steer(psly->PvJmp());
        break;
    case 7:
        UpdateAttachMotion(psly->PvAttach());
        break;
    case 6:
        bevy_player_p25_137218((char *)psly + 0x1FF0);
        break;
    case 10:
        SetJtGoalVelocityFromStick(psly, (char *)psly + 0x1AC0, psly->field_0x1BC0, psly->pjoy->radStick, psly->pjoy->uStick);
        break;
    case 11:
        func_0018B460(psly);
        break;
    case 12:
        SetRunBlendU((char *)psly + 0x1C30, psly->pjoy->uStick);
        SetStepRadTarget(psly, psly->pjoy->radStick);
        break;
    case 5:
        switch (psly->field_0x18D0) {
        case 4:
            if (psly->field_0x10DC)
                func_002046F0(psly, psly->field_0x10DC);
            break;
        case 5:
            SetJtGoalVelocityFromStick(psly, (char *)psly + 0x13D0, psly->field_0x14D0, psly->pjoy->radStick, psly->pjoy->uStick);
            break;
        case 8:
        case 9: {
            VU_SCALE dir;
            dir.q = SetVectorCylind__FP6VECTORfff(psly->pjoy->radStick + 3.14159265f, psly->pjoy->uStick * D_002BF3C0, 0.0f);
            psly->velGoal = bevy_camera_follow_track_heading_weight(0, psly, dir.q);
            break;
        }
        }
        break;
    case 16:
        if (FGadgetAcquired(0x1C)) {
            func_0018E1E0(psly);
        } else if (psly->field_0x1D2C) {
            CHN *pchn = PchnFindAseg(psly->field_0x1D1C, psly, 1, 1);
            if (pchn) {
                VU_SCALE vel;
                CURVE *pcurve = pchn->curve;
                ASEGA *pasega = (ASEGA *)psly->field_0x1030;
                pcurve->vt->fn((char *)pcurve + pcurve->vt->delta, pasega->t, pasega->rate, 0, &vel.v);
                VU_SCALE scale;
                scale.q = VectorFromFloat(-1.0f);
                psly->velGoal = VectorScaleX(vel.q, scale.q);
            }
        }
        break;
    case 19: {
        ASEGA *pasega = (ASEGA *)psly->field_0x1030;
        QW vel = func_00204E38(pasega->t, psly, pasega);
        VU_SCALE scale;
        scale.q = VectorFromFloat(-1.0f);
        psly->velGoal = VectorScaleX(vel, scale.q);
        break;
    }
    case 20: {
        ASEGA *pasega = (ASEGA *)psly->field_0x1030;
        QW vel = func_00204E38(pasega->t, psly, pasega);
        VU_SCALE scale;
        scale.q = VectorFromFloat(-1.0f);
        psly->velGoal = VectorScaleX(vel, scale.q);
        SetAsegaSpeed(psly, psly->pjoy->uStick);
        SetStepRadTarget(psly, psly->pjoy->radStick);
        break;
    }
    case 17: {
        ASEGA *pasega = (ASEGA *)psly->field_0x1030;
        QW vel = func_00204E38(pasega->t, psly, pasega);
        VU_SCALE scale;
        scale.q = VectorFromFloat(-1.0f);
        psly->velGoal = VectorScaleX(vel, scale.q);
        if (psly->pjoy->uStick > 0.0f)
            SetStepRadTarget(psly, psly->pjoy->radStick);
        break;
    }
    case 24: {
        DrainJtPower(psly, D_002BF3C4);
        if (psly->field_0x18D0 == 12) {
            float dRad = RadNormalize(RadYawSo(psly) - psly->radHeading);
            if (__builtin_fabsf(dRad) < D_FLT_002BF3C8)
                SetJtState(psly, 0x18, 0xD);
        } else {
            SetStepRadTarget(psly, psly->pjoy->radStick);
        }
        QW vel = psly->Slot34();
        float u = GLimitAbs(LaneZInGeneralRegister(vel) / (psly->field_0x1F4 * D_002BF35C), 1.0f);
        float g = D_002BF3CC * u;
        psly->field_0x2014 = GMax(0.0f, g);
        psly->field_0x202C = GMax(0.0f, -g);
        psly->field_0x2020 = 1.0f - __builtin_fabsf(g);
        ReblendAsegbl(psly->field_0x2038);
        break;
    }
    }
    UpdateZapPost((char *)psly + 0xDF0);
    UpdateJtSafePoints(psly);
    if (psly->field_0x1310 && FAsegaGone(psly->field_0x1310)) {
        ReleaseAsegaHandle((char *)psly + 0x1310);
        psly->field_0x1314 = -1;
    }
}
