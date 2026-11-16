// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "ps2inline.h"
#include "vu0inline.h"

union VU_VEC { QW q; VECTOR v; };
struct SMP { float gMaxSpeed, gAccel, gDecel; };
union VU_SMP { QW q; VECTOR v; SMP smp; };
struct CLQ { float g0, g1, g2, pad; };
struct LM { float gMin, gMax; };
struct SMPA { float g0, g1, g2, g3; };
struct CRV { char pad0[0xE0]; int fClosed; char pad1[4]; int ccv; };
struct LO;
struct TN {
    char pad0[0x10C];
    CRV *pcrv;
    char pad1[0x120 - 0x110];
    int fCylinder;
    char pad2[0x12C - 0x124];
    int fFakeCylinder;
    float dpanMax;
    char pad3[0x138 - 0x134];
    float tActivate;
    char pad4[0x140 - 0x13C];
    float sClosest;
    char pad5[0x164 - 0x144];
    int grftnd;
    int fPullBack;
    int fPushIn;
    float dtPullBack;
    float gPullBack;
    float dtPushIn;
    float gPushIn;
    int ifollow;
    char pad6[0x18C - 0x184];
    int fNoClip;
    LO *paloLook;
    char pad7[0x1A0 - 0x194];
    CLQ clqLook;
    LM lmLook;
};
struct TNFN {
    char pad0[4];
    float dsOffset;
    char pad1[0x10 - 8];
    CLQ aclq[3];
    LM alm[3];
    float tiltLook;
    float panLook;
    char pad2[0x64 - 0x60];
    float gSmooth;
    float gFollow;
    char pad3[0x80 - 0x6C];
    float gSpring;
    float gDamp;
    LM lmTilt;
};
struct CPDEFI {
    int grf;
    char pad0[0xC];
    QW pos;
    QW dpos;
    float pan;
    char pad1[4];
    float tCut;
    int ifollow;
};
struct JOY {
    char pad0[0x103C];
    float xLeft;
    float yLeft;
    char pad1[0x1070 - 0x1044];
    float xRight;
    float yRight;
    float gManual;
};
struct JT {
    char pad0[0x4C8];
    int fOnGround;
    int ijtcamGround;
    char pad1[0x4F4 - 0x4D0];
    int jtcs;
    char pad2[0x500 - 0x4F8];
    QW posSpring;
    char pad3[0x528 - 0x510];
    TN *ptn;
    char pad4[0x10E4 - 0x52C];
    int jts;
};
struct CPTN {
    LO *palo;
    char pad0[0xC];
    TN *ptn;
    TNFN *ptnfn;
    float pan;
    float tilt;
    float rad;
    float dradSpring;
    int fManual;
    float panManual;
    float tiltManual;
    int ftnd;
    int fReset;
    int fLocked;
    float dpan;
    float dtilt;
    float tManual;
    float panCylinder;
    float panFwd;
    float tiltFwd;
    float panRev;
    float tiltRev;
    float tCut;
    float gSmooth;
    float vrad;
    float vtilt;
    QW posEye;
    char pad1[4];
    float dpanLook;
    float dtiltLook;
    float vpanLook;
    float vtiltLook;
};
struct CM {
    char pad0[0x40];
    float rMulX;
    float rMulY;
    char pad1[0x4C - 0x48];
    float sNearClip;
    char pad2[0x60 - 0x50];
    MATRIX3 mat;
    QW pos;
    char pad3[0x2E0 - 0xA0];
    VECTOR posSpring;
    VECTOR vSpring;
    int fCut;
    float panCut;
    float tiltCut;
};
struct CLOCK { float t; float dt; char pad0[8]; float dtReal; float tReal; };
struct BEVYCAM { char pad0[4]; float tActivity; };

extern "C" {
int FIsBasicDerivedFrom(void *, int);
void UpdateCptnSquishCut(CPTN *);
void UpdateCptnClosestPoint(CPTN *, CPDEFI *);
void SpringCm__FfffP2CMP6VECTORP6VECTORP6VECTOR(float, float, CM *, VECTOR *, VECTOR *, QW);
float GSmooth__FfffP3SMPPf(float, float, float, SMP *, float *);
void CalculateTnCrv(TN *, QW, VECTOR *, VECTOR *);
void DecomposeCylind(QW, float *, float *, float *);
float RadNormalize__Ff(float);
float GLimitAbs__Fff(float, float);
void CalculateTnPos__FP2TNP6VECTORffP3CLQP2LM4FTNDT1(TN *, float *, float, float, CLQ *, LM *, int, VECTOR *);
void DecomposeSphere(QW, float *, float *, float *);
float atanf(float);
float atan2f(float, float);
float GLimitLm__FP2LMf(LM *, float);
QW PosLoWorld(LO *);
void *NewEmitter(int);
void SetEmitterUnpositioned(void *, int);
float RadSmoothA__FffffP4SMPAPf(float, float, float, float, SMPA *, float *);
void bevy_camera_follow_activity(BEVYCAM *, int, int);
float RadSmooth__FfffP3SMPPf(float, float, float, SMP *, float *);
QW *PmatLoWorld(LO *);
QW bevy_camera_follow_track_heading_weight(TN *, void *, QW);
QW SetVectorSphere__FP6VECTORfff(float, float, float);
void FindCptnClearEyePosition(CPTN *, QW, QW, VECTOR *);
QW ClipCmEye(CM *, QW, QW);
void DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1(MATRIX3 *, float *, float *);
void SetCmLookAt(CM *, QW, QW, float, float);
void GetTnfnNose__FP4TNFNP6CPDEFIP6VECTORP2TN(TNFN *, CPDEFI *, VECTOR *, TN *);

extern CLOCK g_2dded0;
extern CM B_002DDF40;
extern QW B_002DE220;
extern BEVYCAM B_002DEB30;
extern QW g_2a2da0;
extern QW g_2a2dc0;
extern QW g_2a2dd0;
extern LM g_2bbb60;
extern int D_002C4118;
extern LM D_002C41B0;
extern float D_002C41D8;
extern float D_002C41DC;
extern float D_002C41E0;
extern float D_002C41E4;
extern float D_002C41E8;
extern float D_002C41EC;
extern CLQ D_002C41F0;
extern LM D_002C4200;
extern SMP D_002C4208;
extern CLQ D_002C4220;
extern SMP D_002C4230;
extern SMPA D_002C4240;
extern SMPA D_002C4250;
extern SMP D_002C4260;
extern float D_002C426C;
extern float D_002C4270;
extern float D_002C4274;
extern float D_002C4278;
extern float D_002C427C;
extern float D_002C4280;
}

static inline float fmax2(float a, float b) { return b > a ? b : a; }
static inline float fmin2(float a, float b) { return b < a ? b : a; }

void UpdateCptn(CPTN *pcptn, CPDEFI *pcpdefi, JOY *pjoy, float dt)
{
    VECTOR posNose;
    VU_VEC posTarget;
    VU_VEC vecHeading;
    VU_VEC dpos;
    VU_VEC dposT;
    VU_VEC posT;
    VU_VEC vecT;
    SMP smp;
    VU_SMP vecFacing;
    float panFwd, tiltFwd, radFwd;
    float panRev, tiltRev, radRev;
    float panEye, tiltEye, radEye;
    float radCyl;
    float zCyl;
    float panCm;
    float tiltCm;

    float dtReal = g_2dded0.dtReal;
    LO *palo = pcptn->palo;
    TN *ptn = pcptn->ptn;
    JT *pjt = FIsBasicDerivedFrom(palo, 0x34) ? (JT *)palo : 0;
    UpdateCptnSquishCut(pcptn);
    int grftnd;
    int fPullBack;
    int fPushIn;
    if (ptn) {
        fPullBack = ptn->fPullBack;
        grftnd = ptn->grftnd;
        fPushIn = ptn->fPushIn;
    } else {
        fPushIn = 0;
        grftnd = 4;
        fPullBack = 0;
    }
    UpdateCptnClosestPoint(pcptn, pcpdefi);
    GetTnfnNose__FP4TNFNP6CPDEFIP6VECTORP2TN(pcptn->ptnfn, pcpdefi, &posNose, ptn);
    if (pjt && pjt->jtcs == 2)
        SpringCm__FfffP2CMP6VECTORP6VECTORP6VECTOR(8.0f, -6.0f, &B_002DDF40, &B_002DDF40.posSpring, &B_002DDF40.vSpring,
                                                   VectorSub(pjt->posSpring, *(QW *)&posNose));
    posTarget.q = VectorAdd(*(QW *)&posNose, B_002DE220);
    if (ptn && ptn->paloLook)
        pcpdefi->grf &= ~1;
    pcptn->gSmooth = GSmooth__FfffP3SMPPf(pcptn->gSmooth, (pcpdefi->grf & 1) ? 0.0f : pcptn->ptnfn->gSmooth, g_2dded0.dt, &D_002C4230, 0);
    pcptn->tCut = fmax2(pcpdefi->tCut, pcptn->tCut);
    panRev = tiltFwd = panFwd = tiltRev = 0.0f;
    if (ptn && (grftnd & 3)) {
        CalculateTnCrv(ptn, *(QW *)&posNose, &dpos.v, &vecHeading.v);
        if (ptn->fCylinder) {
            DecomposeCylind(dpos.q, &dpos.v.x, &dpos.v.y, &dpos.v.z);
            if (!pcptn->fReset)
                dpos.v.x += GLimitAbs__Fff(RadNormalize__Ff(pcptn->panCylinder - dpos.v.x), ptn->dpanMax);
            pcptn->panCylinder = dpos.v.x;
        }
        if (grftnd & 1) {
            CalculateTnPos__FP2TNP6VECTORffP3CLQP2LM4FTNDT1(ptn, &dpos.v.x, ptn->sClosest, pcptn->ptnfn->dsOffset, pcptn->ptnfn->aclq,
                                                           pcptn->ptnfn->alm, 1, &dposT.v);
            DecomposeSphere(VectorSub(dposT.q, posTarget.q), &panFwd, &tiltFwd, &radFwd);
        }
        if (grftnd & 2) {
            CalculateTnPos__FP2TNP6VECTORffP3CLQP2LM4FTNDT1(ptn, &dpos.v.x, ptn->sClosest, pcptn->ptnfn->dsOffset, pcptn->ptnfn->aclq,
                                                           pcptn->ptnfn->alm, 2, &dposT.v);
            DecomposeSphere(VectorSub(dposT.q, posTarget.q), &panRev, &tiltRev, &radRev);
        }
    }
    if (pcptn->fReset)
        pcptn->ftnd = 4;
    if (B_002DDF40.fCut) {
        if (B_002DDF40.fCut == 2) {
            pcptn->ftnd = 4;
            pcptn->pan = B_002DDF40.panCut;
            pcptn->tilt = GLimitLm__FP2LMf(&D_002C41B0, B_002DDF40.tiltCut - atanf(pcptn->ptnfn->panLook * B_002DDF40.rMulY));
        } else if (!(grftnd & 3)) {
            pcptn->ftnd = 4;
            pcptn->pan = pcpdefi->pan;
            pcptn->tilt = pcptn->ptnfn->lmTilt.gMin;
        } else if (!(grftnd & 2) || ((grftnd & 1) && __builtin_fabsf(RadNormalize__Ff(panFwd - pcpdefi->pan)) <
                                                        __builtin_fabsf(RadNormalize__Ff(panRev - pcpdefi->pan)))) {
            pcptn->ftnd = 1;
        } else {
            pcptn->ftnd = 2;
        }
        pcptn->tCut = g_2dded0.t;
        pcptn->tManual = g_2dded0.t - D_002C41DC;
    }
    int ftnd = pcptn->ftnd;
    if (!(ftnd & grftnd) && ftnd > 0 && ftnd < 3)
        pcptn->ftnd = 4;

    if (ptn && ptn->paloLook) {
        dposT.q = VectorSub(PosLoWorld(ptn->paloLook), pcpdefi->pos);
        dposT.v.z = 0.0f;
        QW vec = dposT.q;
        QW length = SqrtX(SquaredLength(vec));
        if (LaneX(length) < 0.0001f)
            dposT.q = g_2a2dd0;
        else
            dposT.q = ScaleByReciprocalX(vec, length);
        float dist = LaneX(length);
        float g = ptn->clqLook.g0 + dist * (ptn->clqLook.g1 + dist * ptn->clqLook.g2);
        if (g < ptn->lmLook.gMin)
            g = ptn->lmLook.gMin;
        else if (ptn->lmLook.gMax < g)
            g = ptn->lmLook.gMax;
        posT.q = VectorFromFloat(g);
        dpos.q = VectorScaleX(dposT.q, posT.q);
    } else {
        dpos.q = pcpdefi->dpos;
    }

    float pan = pcptn->pan;
    float tilt = pcptn->tilt;
    if ((grftnd & 4) && (pcptn->fManual || 0.0f < pjoy->gManual || pcptn->dpan != 0.0f || pcptn->dtilt != 0.0f)) {
        if (pcptn->ftnd != 4)
            SetEmitterUnpositioned(NewEmitter(3), 0);
        if (0.0f < pjoy->gManual)
            pcptn->fManual = 0;
        if (pcptn->fManual) {
            SMPA *psmpa;
            if (pjt && pjt->jts == 4)
                psmpa = &D_002C4250;
            else
                psmpa = &D_002C4240;
            pan = RadSmoothA__FffffP4SMPAPf(pan, pcptn->dpan, pcptn->panManual, dtReal, psmpa, &pcptn->dpan);
            tilt = RadSmoothA__FffffP4SMPAPf(tilt, pcptn->dtilt, pcptn->tiltManual, dtReal, psmpa, &pcptn->dtilt);
            if (pan == pcptn->panManual && tilt == pcptn->tiltManual)
                pcptn->fManual = 0;
        } else {
            float x = pjoy->xRight;
            float y = pjoy->yRight;
            float ddMax = D_002C41EC * dtReal;
            float dpanGoal = x * __builtin_fabsf(x) * D_002C41E4;
            float dtiltGoal = y * __builtin_fabsf(y) * D_002C41E8;
            float dpanLow = pcptn->dpan - ddMax;
            float dpanHigh = pcptn->dpan + ddMax;
            if (dpanGoal < dpanLow)
                dpanGoal = dpanLow;
            else if (dpanHigh < dpanGoal)
                dpanGoal = dpanHigh;
            pcptn->dpan = dpanGoal;
            float dtiltHigh = pcptn->dtilt + ddMax;
            float dtiltLow = pcptn->dtilt - ddMax;
            if (dtiltGoal < dtiltLow)
                pcptn->dtilt = dtiltLow;
            else if (dtiltHigh < dtiltGoal)
                pcptn->dtilt = dtiltHigh;
            else
                pcptn->dtilt = dtiltGoal;
            float angle = atan2f(__builtin_fabsf(pjoy->yRight), __builtin_fabsf(pjoy->xRight));
            if (angle < 0.2617994f)
                pcptn->dtilt = 0.0f;
            else if (1.3089969f < angle)
                pcptn->dpan = 0.0f;
            pan = RadNormalize__Ff(pan + pcptn->dpan * dtReal);
            tilt = GLimitLm__FP2LMf(&D_002C41B0, RadNormalize__Ff(tilt + pcptn->dtilt * dtReal));
            if (5.0f < g_2dded0.tReal - B_002DEB30.tActivity) {
                B_002DEB30.tActivity = g_2dded0.tReal;
                bevy_camera_follow_activity(&B_002DEB30, 6, 0);
            }
        }
        pcptn->ftnd = 4;
        pcptn->fLocked = 1;
        pcptn->tManual = g_2dded0.t;
    } else if (pcptn->ftnd == 4) {
        dposT.v.y = pjoy->yLeft;
        dposT.v.x = pjoy->xLeft;
        dposT.v.z = 0.0f;
        QW fallback = g_2a2da0;
        QW dir = dposT.q;
        QW length = SqrtX(SquaredLength(dir));
        if (LaneX(length) < 0.0001f)
            dir = fallback;
        else
            dir = ScaleByReciprocalX(dir, length);
        posT.q = VectorSub(posTarget.q, B_002DDF40.pos);
        dposT.q = dir;
        posT.v.z = posT.v.z * 0.3f;
        QW dposCam = posT.q;
        QW lengthCam = SqrtX(SquaredLength(dposCam));
        if (LaneX(lengthCam) < 0.0001f)
            posT.q = g_2a2da0;
        else
            posT.q = ScaleByReciprocalX(dposCam, lengthCam);
        float distCam = LaneX(lengthCam);
        int ifollow;
        if (!ptn || (ifollow = ptn->ifollow) == -1)
            ifollow = pcpdefi->ifollow;
        switch (ifollow) {
        case 0:
            vecT.q = CrossProduct(g_2a2dc0, posT.q);
            break;
        case 1:
            vecT = posT;
            break;
        }
        QW fallbackAxis = g_2a2da0;
        QW axis = vecT.q;
        QW lengthAxis = SqrtX(SquaredLength(axis));
        if (LaneX(lengthAxis) < 0.0001f)
            axis = fallbackAxis;
        else
            axis = ScaleByReciprocalX(axis, lengthAxis);
        vecT.q = axis;
        float gTurn = GLimitAbs__Fff(LaneX(DotProduct(dpos.q, axis)) / distCam, D_002C41E0);
        float yJoy = dposT.v.y;
        float gJoy = D_002C41F0.g0 + yJoy * (D_002C41F0.g1 + yJoy * D_002C41F0.g2);
        if (gJoy < D_002C4200.gMin)
            gJoy = D_002C4200.gMin;
        else if (D_002C4200.gMax < gJoy)
            gJoy = D_002C4200.gMax;
        float dpanAuto = gTurn * pcptn->gSmooth * gJoy;
        float dtManual = g_2dded0.t - pcptn->tManual;
        float gManual = D_002C4220.g0 + dtManual * (D_002C4220.g1 + dtManual * D_002C4220.g2);
        if (gManual < g_2bbb60.gMin)
            gManual = g_2bbb60.gMin;
        else if (g_2bbb60.gMax < gManual)
            gManual = g_2bbb60.gMax;
        dpanAuto = dpanAuto * gManual;
        float panAuto = RadNormalize__Ff(pan + dpanAuto * g_2dded0.dt);
        float gSpeed = fmin2(1.0f, LaneX(SqrtX(SquaredLengthXy(dpos.q))) * 0.0016666667f);
        float tiltAuto;
        if (0.1f < gSpeed) {
            smp.gMaxSpeed = D_002C4260.gMaxSpeed * gSpeed;
            smp.gAccel = D_002C4260.gAccel * gSpeed;
            smp.gDecel = D_002C4260.gDecel;
            tiltAuto = RadSmooth__FfffP3SMPPf(tilt, GLimitLm__FP2LMf(&pcptn->ptnfn->lmTilt, tilt), g_2dded0.dt, &smp, 0);
        } else {
            tiltAuto = tilt;
        }
        if (!(grftnd & 3)) {
            pan = panAuto;
            tilt = tiltAuto;
        } else {
            float w;
            float panGoal;
            float tiltGoal;
            if (!ptn->pcrv && !ptn->fFakeCylinder) {
            fwd:
                w = 1.0f;
                panGoal = panFwd;
                tiltGoal = tiltFwd;
            } else if (pjt && ptn == pjt->ptn) {
                w = 3.0f;
                panGoal = panFwd;
                tiltGoal = tiltFwd;
            } else if (pcptn->ftnd == 1) {
                goto fwd;
            } else if (pcptn->ftnd == 2) {
                panGoal = panRev;
                w = 1.0f;
                tiltGoal = tiltRev;
            } else {
                vecFacing.q = *PmatLoWorld(palo);
                vecFacing.v.z = 0.0f;
                QW fallbackFacing = g_2a2da0;
                QW facing = vecFacing.q;
                QW lengthFacing = SqrtX(SquaredLength(facing));
                if (LaneX(lengthFacing) < 0.0001f)
                    facing = fallbackFacing;
                else
                    facing = ScaleByReciprocalX(facing, lengthFacing);
                vecFacing.q = facing;
                vecHeading.q = bevy_camera_follow_track_heading_weight(ptn, 0, vecHeading.q);
                float dot = LaneX(DotProduct(vecFacing.q, vecHeading.q));
                w = dot * dot * (3.0f - (__builtin_fabsf(dot) + __builtin_fabsf(dot)));
                if (!(grftnd & 2) || 0.0f < dot) {
                    panGoal = panFwd;
                    tiltGoal = tiltFwd;
                } else {
                    panGoal = panRev;
                    tiltGoal = tiltRev;
                }
            }
            float gFollow;
            if (pjt) {
                if (pjt->ijtcamGround != -1 && !pjt->fOnGround)
                    gFollow = fmin2(1.0f, LaneX(SqrtX(SquaredLengthXy(dpos.q))) * 0.005f);
                else
                    gFollow = fmin2(1.0f, LaneX(SqrtX(SquaredLengthXy(dpos.q))) * 0.0016666667f);
            } else {
                gFollow = 0.0f;
            }
            gFollow = gFollow * pcptn->ptnfn->gFollow;
            if (fPushIn) {
                float dtCut = g_2dded0.t - (pcptn->tCut + D_002C41D8);
                float dtManualPush = g_2dded0.t - (pcptn->tManual + D_002C41DC);
                float g = 0.0f;
                if (0.0f < ptn->dtPushIn) {
                    g = GLimitLm__FP2LMf(&g_2bbb60, dtCut / ptn->dtPushIn);
                    g = g * GLimitLm__FP2LMf(&g_2bbb60, dtManualPush / ptn->dtPushIn);
                } else if (0.0f < dtCut && 0.0f < dtManualPush) {
                    g = 1.0f;
                }
                g = g * ptn->gPushIn;
                if (gFollow * w < g) {
                    w = 1.0f;
                    gFollow = g;
                }
            }
            if (fPullBack && !pcptn->fLocked) {
                float g;
                if (0.0f < ptn->dtPullBack)
                    g = GLimitLm__FP2LMf(&g_2bbb60, (g_2dded0.t - ptn->tActivate) / ptn->dtPullBack);
                else
                    g = 1.0f;
                g = g * ptn->gPullBack;
                if (gFollow * w < g) {
                    w = 1.0f;
                    gFollow = g;
                }
            }
            vecFacing.smp.gMaxSpeed = D_002C4208.gMaxSpeed * gFollow;
            vecFacing.smp.gAccel = D_002C4208.gAccel * gFollow;
            vecFacing.smp.gDecel = D_002C4208.gDecel;
            float panFollow = RadSmooth__FfffP3SMPPf(pan, RadNormalize__Ff(pan + RadNormalize__Ff(panGoal - pan)), g_2dded0.dt, &vecFacing.smp, 0);
            float tiltFollow = RadSmooth__FfffP3SMPPf(tilt, RadNormalize__Ff(tilt + RadNormalize__Ff(tiltGoal - tilt)), g_2dded0.dt, &vecFacing.smp, 0);
            float dpanFollow = __builtin_fabsf(RadNormalize__Ff(panGoal - panFollow));
            if (__builtin_fabsf(RadNormalize__Ff(panGoal - panAuto)) < dpanFollow)
                panFollow = panAuto;
            float dtiltFollow = __builtin_fabsf(RadNormalize__Ff(tiltGoal - tiltFollow));
            if (__builtin_fabsf(RadNormalize__Ff(tiltGoal - tiltAuto)) < dtiltFollow)
                tiltFollow = tiltAuto;
            float dpanA = RadNormalize__Ff(panAuto - pan);
            float dpanF = RadNormalize__Ff(panFollow - pan);
            pan = RadNormalize__Ff(pan + (1.0f - w) * dpanA + w * dpanF);
            float dtiltA = RadNormalize__Ff(tiltAuto - tilt);
            float dtiltF = RadNormalize__Ff(tiltFollow - tilt);
            tilt = RadNormalize__Ff(tilt + (1.0f - w) * dtiltA + w * dtiltF);
            if (!pcptn->fReset) {
                CRV *pcrv = pcptn->ptn->pcrv;
                if (!pcrv || pcrv->fClosed || pcrv->ccv < 3) {
                    if (grftnd & 1) {
                        if ((RadNormalize__Ff(pcptn->pan - pcptn->panFwd) * RadNormalize__Ff(pan - panFwd) <= 0.0f ||
                             __builtin_fabsf(RadNormalize__Ff(pan - panFwd)) < 0.0001f) &&
                            __builtin_fabsf(RadNormalize__Ff(pan - panFwd)) < 1.5707964f) {
                            if ((RadNormalize__Ff(pcptn->tilt - pcptn->tiltFwd) * RadNormalize__Ff(tilt - tiltFwd) <= 0.0f ||
                                 __builtin_fabsf(RadNormalize__Ff(tilt - tiltFwd)) < 0.0001f) &&
                                __builtin_fabsf(RadNormalize__Ff(tilt - tiltFwd)) < 1.5707964f) {
                                pcptn->fLocked = 1;
                                pcptn->ftnd = 1;
                                goto done;
                            }
                        }
                    }
                    if (grftnd & 2) {
                        if ((RadNormalize__Ff(pcptn->pan - pcptn->panRev) * RadNormalize__Ff(pan - panRev) <= 0.0f ||
                             __builtin_fabsf(RadNormalize__Ff(pan - panRev)) < 0.0001f) &&
                            __builtin_fabsf(RadNormalize__Ff(pan - panRev)) < 1.5707964f) {
                            if ((RadNormalize__Ff(pcptn->tilt - pcptn->tiltRev) * RadNormalize__Ff(tilt - tiltRev) <= 0.0f ||
                                 __builtin_fabsf(RadNormalize__Ff(tilt - tiltRev)) < 0.0001f) &&
                                __builtin_fabsf(RadNormalize__Ff(tilt - tiltRev)) < 1.5707964f) {
                                pcptn->ftnd = 2;
                                pcptn->fLocked = 1;
                            }
                        }
                    }
                }
            }
        }
    }
done:
    float tiltLook;
    float panLook;
    switch (pcptn->ftnd) {
    case 1:
        panEye = panFwd;
        tiltEye = tiltFwd;
        radEye = radFwd;
        panLook = pcptn->ptnfn->panLook;
        tiltLook = pcptn->ptnfn->tiltLook;
        break;
    case 2:
        panEye = panRev;
        tiltEye = tiltRev;
        radEye = radRev;
        tiltLook = -pcptn->ptnfn->tiltLook;
        panLook = pcptn->ptnfn->panLook;
        break;
    case 4:
        panEye = pan;
        tiltEye = tilt;
        float rad;
        if (!(grftnd & 3)) {
            rad = __builtin_fabsf(pcptn->ptnfn->dsOffset);
            panLook = pcptn->ptnfn->panLook;
            tiltLook = pcptn->ptnfn->tiltLook;
        } else {
            float u;
            if (!(grftnd & 2)) {
                u = 1.0f;
            } else if (!(grftnd & 1)) {
                u = 0.0f;
            } else {
                if (pcptn->pan < panFwd && pcptn->pan < panRev) {
                    if (panRev < panFwd)
                        panFwd = panFwd - 6.2831855f;
                    else
                        panRev = panRev - 6.2831855f;
                } else if (panFwd < pcptn->pan && panRev < pcptn->pan) {
                    if (panFwd < panRev)
                        panFwd = panFwd + 6.2831855f;
                    else
                        panRev = panRev + 6.2831855f;
                }
                u = (pcptn->pan - panRev) / (panFwd - panRev);
                u = u * u * (3.0f - (u + u));
            }
            float tiltLookFwd = pcptn->ptnfn->tiltLook;
            rad = u * radFwd + (1.0f - u) * radRev;
            panLook = pcptn->ptnfn->panLook;
            tiltLook = u * tiltLookFwd + (1.0f - u) * -tiltLookFwd;
        }
        radEye = rad;
        break;
    }
    if (B_002DDF40.fCut) {
        pcptn->vrad = 0.0f;
        pcptn->vtilt = 0.0f;
    } else {
        float gDamp = pcptn->ptnfn->gDamp * D_002C426C * g_2dded0.dt + 1.0f;
        float gSpring = pcptn->ptnfn->gSpring * D_002C4270 * g_2dded0.dt;
        pcptn->vrad = gDamp * pcptn->vrad + (radEye - pcptn->rad) * gSpring;
        pcptn->vtilt = gDamp * pcptn->vtilt + (panLook - pcptn->dradSpring) * gSpring;
        radEye = pcptn->rad + pcptn->vrad * g_2dded0.dt;
        panLook = pcptn->dradSpring + pcptn->vtilt * g_2dded0.dt;
    }
    dposT.q = SetVectorSphere__FP6VECTORfff(panEye, tiltEye, radEye);
    posT.q = VectorAdd(posTarget.q, dposT.q);
    if (!ptn || !ptn->fNoClip) {
        if (B_002DDF40.fCut)
            FindCptnClearEyePosition(pcptn, posTarget.q, posT.q, &posT.v);
        else if (!D_002C4118)
            posT.q = ClipCmEye(&B_002DDF40, pcptn->posEye, posT.q);
    }
    dposT.q = VectorSub(posT.q, posTarget.q);
    DecomposeSphere(dposT.q, &panEye, &tiltEye, &radEye);
    pcptn->posEye = posT.q;
    vecT.q = VectorFromFloat((radEye + B_002DDF40.sNearClip) / radEye);
    posT.q = VectorAdd(posTarget.q, VectorScaleX(dposT.q, vecT.q));
    float panOffset = atanf(tiltLook * B_002DDF40.rMulX);
    float tiltOffset = -atanf(panLook * B_002DDF40.rMulY);
    if (pcptn->fReset) {
        float dtiltLook;
        if (B_002DDF40.fCut) {
            pcptn->dpanLook = 0.0f;
            dtiltLook = 0.0f;
        } else {
            DecomposeCylind(dposT.q, 0, &radCyl, &zCyl);
            DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1(&B_002DDF40.mat, &panCm, &tiltCm);
            float panEyeCm = RadNormalize__Ff(panEye + 3.1415927f + panOffset);
            float tiltEyeCm = RadNormalize__Ff(atan2f(-zCyl, radCyl) + tiltOffset);
            pcptn->dpanLook = RadNormalize__Ff(panCm - panEyeCm);
            dtiltLook = RadNormalize__Ff(tiltCm - tiltEyeCm);
        }
        pcptn->dtiltLook = dtiltLook;
        pcptn->vpanLook = 0.0f;
        pcptn->vtiltLook = 0.0f;
    } else {
        pcptn->vpanLook = pcptn->vpanLook + (pcptn->dpanLook * D_002C4274 + pcptn->vpanLook * D_002C4278) * g_2dded0.dt;
        pcptn->vtiltLook = pcptn->vtiltLook + (pcptn->dtiltLook * D_002C427C + pcptn->vtiltLook * D_002C4280) * g_2dded0.dt;
        pcptn->dpanLook = pcptn->dpanLook + pcptn->vpanLook * g_2dded0.dt;
        pcptn->dtiltLook = pcptn->dtiltLook + pcptn->vtiltLook * g_2dded0.dt;
    }
    SetCmLookAt(&B_002DDF40, posT.q, posTarget.q, panOffset + pcptn->dpanLook, tiltOffset + pcptn->dtiltLook);
    pcptn->dradSpring = panLook;
    pcptn->pan = panEye;
    pcptn->tilt = tiltEye;
    pcptn->rad = radEye;
    pcptn->panFwd = panFwd;
    pcptn->tiltFwd = tiltFwd;
    pcptn->panRev = panRev;
    pcptn->tiltRev = tiltRev;
    pcptn->fReset = 0;
}
