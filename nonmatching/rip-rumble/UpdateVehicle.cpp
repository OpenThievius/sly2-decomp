// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "po.h"
#include "xf.h"
#include "ps2inline.h"
#include "vu0inline.h"

union VU_SCALE { QW q; VECTOR v; };
struct LM { float gMin; float gMax; };
struct SMP;
struct SMA;
struct ACT;
struct AMB { u8 unknown_0x0[0x4E]; s16 cpause; };
struct CLOCK { float t; float dt; };

struct WHEEL {
    int oid; XF *pxf; u8 unknown_0x8[4]; float uSteer; float uSteerSide; float radSteer; u8 unknown_0x18[0x60 - 0x18];
};
struct AXLE { int oid; XF *pxf; ACT *pact; LM lm; };
struct GUN {
    u8 unknown_0x0[0x18]; int oidSm; void *psm; SMA *psma; u8 unknown_0x24[0x2C - 0x24]; int oidXf; XF *pxf; ACT *pact;
    int oidMuzzle; LO *pmuzzle; LM lmRad; LM lmSpeed; float agRange[3]; u8 unknown_0x5C[4]; LM lmRange; float gGravity;
    u8 unknown_0x6C[0x74 - 0x6C]; float rad; float speed; u8 unknown_0x7C[0xA0 - 0x7C]; int fOnTarget;
};
struct VEHICLE : PO {
    /* 0x180 */ int state; float tState; u8 unknown_0x188[0x190 - 0x188];
    /* 0x190 */ int cwheel; u8 unknown_0x194[0x1A0 - 0x194]; WHEEL awheel[8];
    /* 0x4A0 */ float sWheelSpread; int caxle; AXLE aaxle[4];
    /* 0x4F8 */ int cgun; GUN *apgun[8]; float speedMax; u8 unknown_0x520[0x540 - 0x520];
    /* 0x540 */ float heading; float headingGoal; float uSteer; float radAim; float speedGoal; float speed; float field_0x558;
    u8 unknown_0x55C[0x598 - 0x55C];
    /* 0x598 */ AMB *pamb; int sfxid; float uVolume; LO *ploTarget; u8 unknown_0x5A8[0x5C0 - 0x5A8];
    /* 0x5C0 */ float tUpright;
};

extern "C" {
void UpdateSo(SO *);
float atan2f(float, float);
int FVehicleGunHasAmmo(GUN *);
void SetSmaGoal__FP3SMA3OID(SMA *, int);
void UpdateVehicleAi(VEHICLE *);
void func_001D2150(VEHICLE *);
float RadNormalize__Ff(float);
QW SetVectorCylind__FP6VECTORfff(float, float, float);
QW ConvertXfVec(XF *, XF *, QW);
float GLimitLm__FP2LMf(LM *, float);
void func_0012D108(ACT *, QW);
float RadSmooth__FfffP3SMPPf(float, float, float, SMP *, float *);
float GSmooth__FfffP3SMPPf(float, float, float, SMP *, float *);
QW PosLoWorld(void *);
int FFloatsNear__Ffff(float, float, float);
void SetAmbVolume(AMB *, float);
void SetAmbPitch(AMB *, float);
void ContinueAmb(AMB *);
void func_001F5078(VEHICLE *);
extern float D_FLT_002C2030;
extern float D_FLT_002C2040[3];
extern LM D_FLT_002C2050;
extern float D_FLT_002C2060[3];
extern LM D_FLT_002C2070;
extern float D_FLT_002C2080[3];
extern LM D_FLT_002C2090;
extern float D_FLT_002C20A4;
extern SMP D_002C2098;
extern SMP D_002C20A8;
extern CLOCK g_2dded0;
extern QW g_2a2dc0;
}

static inline float GPoly(const float *ag, float x) { return ag[0] + x * (ag[1] + x * ag[2]); }
static inline float GClamp(float g, float gMin, float gMax)
{
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}

extern "C" void UpdateVehicle(VEHICLE *pvehicle)
{
    union VU_SCALE scale;
    int igun;
    UpdateSo(pvehicle);
    pvehicle->heading = atan2f(pvehicle->pxfRoot->matWorld.mat[0][1], pvehicle->pxfRoot->matWorld.mat[0][0]);
    for (igun = 0; igun < pvehicle->cgun; igun++) {
        GUN *pgun = pvehicle->apgun[igun];
        if (!FVehicleGunHasAmmo(pgun))
            SetSmaGoal__FP3SMA3OID(pgun->psma, 0x65);
    }
    switch (pvehicle->state) {
    case 0:
    case 3:
        pvehicle->speedGoal = pvehicle->speed = 0.0f;
        pvehicle->headingGoal = pvehicle->heading;
        break;
    case 2:
        func_001D2150(pvehicle);
        break;
    case 1:
        UpdateVehicleAi(pvehicle);
        break;
    }
    pvehicle->uSteer = GClamp(GPoly(D_FLT_002C2040, RadNormalize__Ff(pvehicle->headingGoal - pvehicle->heading)), D_FLT_002C2050.gMin, D_FLT_002C2050.gMax);
    pvehicle->field_0x558 =
        GClamp(GPoly(D_FLT_002C2060, __builtin_fabsf(RadNormalize__Ff(pvehicle->headingGoal - pvehicle->heading))), D_FLT_002C2070.gMin, D_FLT_002C2070.gMax);
    float uSpeed = GClamp(GPoly(D_FLT_002C2080, __builtin_fabsf(RadNormalize__Ff(pvehicle->headingGoal - pvehicle->heading))), D_FLT_002C2090.gMin, D_FLT_002C2090.gMax);
    float speedGoal = pvehicle->speedGoal;
    float speedLimit = speedGoal < D_FLT_002C2030 ? speedGoal : D_FLT_002C2030;
    pvehicle->speed = uSpeed * speedLimit * pvehicle->uSteer / pvehicle->sWheelSpread;
    if (pvehicle->PmatWorld()->mat[2][2] > 0.5f)
        pvehicle->tUpright = g_2dded0.t;

    int iaxle;
    for (iaxle = 0; iaxle < pvehicle->caxle; iaxle++) {
        AXLE *paxle = &pvehicle->aaxle[iaxle];
        QW vec = SetVectorCylind__FP6VECTORfff(pvehicle->radAim, 1.0f, 0.0f);
        QW dir = ConvertXfVec(0, paxle->pxf->pxfParent, vec);
        float rad = GLimitLm__FP2LMf(&paxle->lm, atan2f(LaneX(RotateWords3(dir)), LaneX(dir)));
        scale.q = VectorFromFloats3(0.0f, 0.0f, rad);
        func_0012D108(paxle->pact, scale.q);
    }

    int iwheel;
    for (iwheel = 0; iwheel < pvehicle->cwheel; iwheel++) {
        WHEEL *pwheel = &pvehicle->awheel[iwheel];
        float radGoal;
        if (pvehicle->speedGoal != 0.0f)
            radGoal = pwheel->uSteer * pvehicle->uSteer;
        else
            radGoal = 0.0f;
        pwheel->radSteer = RadSmooth__FfffP3SMPPf(pwheel->radSteer, radGoal, g_2dded0.dt, &D_002C2098, 0);
    }

    QW posSelf = PosLoWorld(pvehicle);
    QW posTarget = PosLoWorld(pvehicle->ploTarget);
    QW velTarget = pvehicle->ploTarget->GetVelocityVec();
    for (igun = 0; igun < pvehicle->cgun; igun++) {
        float sTarget = LaneX(SqrtX(SquaredLengthXy(VectorSub(posTarget, posSelf))));
        GUN *pgun = pvehicle->apgun[igun];
        if (pgun->pxf == 0)
            continue;
        if (pvehicle->speedGoal != 0.0f || !FVehicleGunHasAmmo(pgun)) {
            pgun->fOnTarget = 0;
            pgun->speed = pgun->lmSpeed.gMin;
            pgun->rad = 0.0f;
        } else {
            float t = GClamp(GPoly(pgun->agRange, sTarget), pgun->lmRange.gMin, pgun->lmRange.gMax);
            QW posGun;
            if (pgun->pmuzzle != 0)
                posGun = PosLoWorld(pgun->pmuzzle);
            else
                posGun = pgun->pxf->matWorld.row[3];
            int fOnTarget = 0;
            float tHalf = t * -0.5f;
            float gDrop = pgun->gGravity * tHalf;
            float rcp = 1.0f / t;
            QW delta = VectorSub(posTarget, posGun);
            QW up = g_2a2dc0;
            QW velFlat = VectorSub(velTarget, VectorScaleX(up, DotProduct(velTarget, up)));
            scale.q = VectorFromFloat(rcp);
            QW scaleRcp = scale.q;
            scale.q = VectorFromFloat(gDrop);
            QW aim = ScaleAddTwoX(velFlat, delta, scaleRcp, up, scale.q);
            float rad = atan2f(LaneZInGeneralRegister(aim), LaneX(SqrtX(SquaredLengthXy(aim))));
            float speed = LaneX(SqrtX(SquaredLength(aim)));
            pgun->rad = GLimitLm__FP2LMf(&pgun->lmRad, rad);
            pgun->speed = GLimitLm__FP2LMf(&pgun->lmSpeed, speed);
            if (FFloatsNear__Ffff(pgun->rad, rad, 0.01f))
                fOnTarget = FFloatsNear__Ffff(pgun->speed, speed, 0.01f) != 0;
            pgun->fOnTarget = fOnTarget;
            if (!fOnTarget) {
                pgun->rad = 0.0f;
                pgun->speed = pgun->lmSpeed.gMin;
            }
        }
        ACT *pact = pgun->pact;
        scale.q = VectorFromFloats3(0.0f, -pgun->rad, 0.0f);
        func_0012D108(pact, scale.q);
    }

    if (pvehicle->pamb != 0) {
        pvehicle->uVolume = GSmooth__FfffP3SMPPf(pvehicle->uVolume, pvehicle->speedGoal / D_FLT_002C20A4, g_2dded0.dt, &D_002C20A8, 0);
        float uVolume = GClamp(pvehicle->uVolume, 0.2f, 1.0f);
        SetAmbVolume(pvehicle->pamb, uVolume);
        SetAmbPitch(pvehicle->pamb, uVolume * 0.2f);
        if (pvehicle->pamb->cpause > 0)
            ContinueAmb(pvehicle->pamb);
    }
    if (pvehicle->speedGoal != 0.0f || pvehicle->speed != 0.0f)
        func_001F5078(pvehicle);
}
