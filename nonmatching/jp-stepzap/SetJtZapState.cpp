// SPDX-License-Identifier: GPL-3.0-or-later
struct JOY { char pad[0x18]; float radHeading; };
#include "sly2.h"
#include "jt.h"
#include "ps2inline.h"
#include "vu0inline.h"

union VU_SCALE { QW q; VECTOR v; };

struct GLOWXF { char pad[0x20]; VECTOR rgba; };
struct CLOCK { float t; };
struct LM { float lo; float hi; };
struct COEFFS { float c0, c1, c2; };
struct GLOWSO { char pad[0x60]; GLOWXF *pxf; };
struct GLOWLO { char pad[0xA8]; GLOWSO *pso; };
struct SLYGLOW { char pad[0x19B8]; GLOWLO *aplo[2]; };
struct JTFLAGS { char pad[0x15C]; int fZapping; char pad160[0x1B0 - 0x160]; QW normalZap; };

struct ZAP {
    JT *pjt;
    int state;
    float tState;
    char pad0c[0x98 - 0xC];
    float tNext;
    char pad9c[4];
    void *aaseg[16];
};

struct TARGETINFO { char pad[0x90]; QW pos; };

extern "C" {
int FIsBasicDerivedFrom(void *, int);
QW PosLoWorld(void *);
float RadYawSo(void *);
float atan2f(float, float);
void SetStepRadTarget(void *, float);
void SetStepRadTargetDir(void *, QW);
void func_001F4BF8(void *);
void RetractAsegaHandle(void *);
void RetractSmaRef(void *);
void ApplyAsegToHandle(void *, void *, int, void *, float, float);
void func_001F1448(void *, void *, int, int, void *);
extern VECTOR D_002BFA00;
extern VECTOR D_002BFA10;
extern COEFFS D_FLT_002BFA20;
extern LM g_2bbb60;
extern CLOCK g_2dded0;
extern QW g_2a2dd0;
extern TARGETINFO B_002DDF40;
}
float RadNormalize(float);

static inline float Quadratic(COEFFS *pcoeffs, float u)
{
    return pcoeffs->c0 + u * (pcoeffs->c1 + u * pcoeffs->c2);
}

static inline float GLimitLm(LM *plm, float g)
{
    float lo = plm->lo;
    float hi = plm->hi;
    if (g < lo)
        return lo;
    if (hi < g)
        return hi;
    return g;
}
void FixStepAngularVelocity(STEP *);

extern "C" void SetJtZapState(ZAP *pzap, int state)
{
    VU_SCALE vel;
    void *paseg;
    int grf;
    int stateOld = pzap->state;

    if (state == stateOld)
        return;

    switch (stateOld) {
    case -1:
        if (FIsBasicDerivedFrom(pzap->pjt, 0x35)) {
            SLYGLOW *psly = (SLYGLOW *)pzap->pjt;
            psly->aplo[0]->pso->pxf->rgba = D_002BFA00;
            psly->aplo[1]->pso->pxf->rgba = D_002BFA00;
        }
        pzap->pjt->Slot91();
        {
            VECTOR *pvel = (VECTOR *)&pzap->pjt->velGoal;
            pvel->z = 0.0f;
            pvel->y = 0.0f;
            pvel->x = 0.0f;
        }
        ((JTFLAGS *)pzap->pjt)->fZapping = 0;
        pzap->tNext = 3.4028235e38f;
        break;
    case 3:
    case 10:
        if (FIsBasicDerivedFrom(pzap->pjt, 0x35)) {
            VECTOR *prgba = &((SLYGLOW *)pzap->pjt)->aplo[0]->pso->pxf->rgba;
            prgba->z = 0.0f;
            prgba->y = 0.0f;
            prgba->x = 0.0f;
        }
        break;
    }

    paseg = 0;
    grf = 1;
    switch (state) {
    case -1:
        if (FIsBasicDerivedFrom(pzap->pjt, 0x35)) {
            SLYGLOW *psly = (SLYGLOW *)pzap->pjt;
            VECTOR *prgba = &psly->aplo[0]->pso->pxf->rgba;
            prgba->z = 0.0f;
            prgba->y = 0.0f;
            prgba->x = 0.0f;
            prgba = &psly->aplo[1]->pso->pxf->rgba;
            prgba->z = 0.0f;
            prgba->y = 0.0f;
            prgba->x = 0.0f;
        }
        ((JTFLAGS *)pzap->pjt)->fZapping = 1;
        pzap->tNext = g_2dded0.t;
        break;
    case 8: {
        QW velNow = pzap->pjt->GetVelocityVec();
        if (-250.0f < LaneX(DotProduct(velNow, ((JTFLAGS *)pzap->pjt)->normalZap))) {
            state = 9;
        } else {
            vel.q = pzap->pjt->GetVelocityVec();
            float speed = LaneX(SqrtX(SquaredLengthXy(vel.q)));
            float clamped = GLimitLm(&g_2bbb60, Quadratic(&D_FLT_002BFA20, speed));
            SetStepRadTarget(pzap->pjt, pzap->pjt->radHeading +
                                            RadNormalize(atan2f(vel.v.y, vel.v.x) + 3.1415927f - pzap->pjt->radHeading) * clamped);
            FixStepAngularVelocity(pzap->pjt);
        }
    }
    case 9:
        grf = 0x21;
        paseg = pzap->aaseg[state];
        break;
    case 10:
        grf = 0x21;
        {
            QW posTarget = B_002DDF40.pos;
            SetStepRadTargetDir(pzap->pjt, VectorSub(posTarget, PosLoWorld(pzap->pjt)));
        }
    case 3:
        paseg = pzap->aaseg[state];
        if (FIsBasicDerivedFrom(pzap->pjt, 0x35))
            ((SLYGLOW *)pzap->pjt)->aplo[0]->pso->pxf->rgba = D_002BFA10;
        break;
    case 5:
    case 11:
        {
            QW posTarget = B_002DDF40.pos;
            SetStepRadTargetDir(pzap->pjt, VectorSub(posTarget, PosLoWorld(pzap->pjt)));
        }
        if (state == 11)
            grf = 0x21;
        paseg = pzap->aaseg[state];
        break;
    case 0:
    case 6:
    case 7:
        paseg = pzap->aaseg[state];
        break;
    case 4:
    case 12:
        pzap->pjt->Slot36(g_2a2dd0);
        SetStepRadTarget(pzap->pjt, RadYawSo(pzap->pjt));
        if (state == 12)
            grf = 0x21;
        pzap->pjt->pjoy->radHeading = pzap->pjt->radHeading;
        paseg = pzap->aaseg[state];
        break;
    case 1:
    case 2:
        grf = 0;
        SetStepRadTarget(pzap->pjt, RadYawSo(pzap->pjt));
        pzap->pjt->pjoy->radHeading = pzap->pjt->radHeading;
        paseg = pzap->aaseg[state];
        break;
    }

    func_001F4BF8(pzap->pjt);
    pzap->state = state;
    pzap->tState = g_2dded0.t;
    if (state != -1) {
        if (paseg == 0)
            paseg = pzap->aaseg[state < 8 ? 0 : 8];
        RetractAsegaHandle(&pzap->pjt->field_0x1030);
        RetractSmaRef(&pzap->pjt->field_0x1034);
        ApplyAsegToHandle(paseg, pzap->pjt, grf, &pzap->pjt->field_0x1030, 0.0f, 1.0f);
        func_001F1448(0, pzap->pjt, -1, 0, &pzap->pjt->field_0x1034);
        pzap->pjt->Slot90();
    }
}
