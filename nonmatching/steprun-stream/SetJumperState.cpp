// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "vu0inline.h"
#include "ps2inline.h"
// SetJumperState: state switch of a jumper (launch an SO along a ballistic arc).
// Behaviour (case 1, launch): vGrav = pjmpt->vGravity * speed^2; dpos = pjmpr->posTarget - so->palo->pos;
// t = fGuided ? DtSolveJumpLaunch(dpos, vGrav, ...) : pjmpt->dtFlight / speed; t = max(pjmpt->dtMin / speed, t);
// so->SetVelocity(dpos / t - vGrav * t / 2); tLand = now + t; tLand - dtMin / speed stored; when guided,
// predicts the landing point/velocity in the parent frame and registers it, then sets the SO gravity to vGrav.
struct VTSO { char pad[0x118]; short delta; short index; void (*SetVelocity)(void *, QW); };
struct ALOP { char pad[0x70]; QW pos; char pad80[0xA0 - 0x80]; void *pxf; };
struct SO { char pad0[0xC]; VTSO *vptr; char pad10[0x58 - 0x10]; ALOP *paloParent; char pad5C[0x148 - 0x5C]; unsigned long grf; };
struct GUARD { char pad[0x498]; void *pfall; };
struct ASEG { char pad[4]; void *paseg; char pad8[4]; float tSeek2; float tSeek3; float dtFlight; float dtMin; QW vGravity; };
struct ASEGA { char pad[0x40]; float speed; };
struct JMPR {
    char pad0[0x10];
    int js;
    float tState;
    char pad18[8];
    QW vGravity;
    ASEG *pjmpt;
    SO *pso;
    ASEGA *pasega;
    void *pv3C;
    QW posTarget;
    float tLand;
    float tPeak;
    void *pvTarget;
    void *pvTarget2;
    int fGuided;
    int fFar;
    int iPredict;
};
extern float g_2dded0[];
extern char D_3DD490[];
extern "C" {
int FIsBasicDerivedFrom(void *, int);
void SubscribeLoObject(void *, void *);
void ClearGuardPathMode(void *);
void DisableFallCheck(void *);
void EnableFallCheck(void *);
void EndJumperFlight(JMPR *);
void RecalcSwOxfFilterForObject(char *, SO *);
int func_0012DE58(SO *, ALOP *, int, QW, QW, float);
}
void ApplyAsegToHandle(void *, SO *, void *, ASEGA **, float, float);
QW GetSoDvGravity(SO *);
void SetSoDvGravity(SO *, QW);
float DtSolveJumpLaunch(QW, QW, float, float, float, float);
void SeekAsega(ASEGA *, int, float, float);
void SetGuardPathTarget(SO *, void *, void *);
QW ConvertXfPos(int, void *, QW);
QW ConvertXfVec(int, void *, QW);

union VU_QUAD { QW q; VECTOR v; };

void SetJumperState(JMPR *pjmpr, int js)
{
    if (js == pjmpr->js)
        return;
    pjmpr->js = js;
    pjmpr->tState = g_2dded0[0];
    switch (js) {
    case 0:
        ApplyAsegToHandle(pjmpr->pjmpt->paseg, pjmpr->pso, pjmpr->pv3C, &pjmpr->pasega, 0.0f, 1.0f);
        SubscribeLoObject(pjmpr->pasega, pjmpr);
        pjmpr->vGravity = GetSoDvGravity(pjmpr->pso);
        break;
    case 1: {
        VU_QUAD scale;
        VU_QUAD dpos;
        VU_QUAD vGrav;
        VU_QUAD velocity;
        VU_QUAD vLand;
        if (FIsBasicDerivedFrom(pjmpr->pso, 0x38)) {
            SO *pso = pjmpr->pso;
            ClearGuardPathMode(pso);
            DisableFallCheck(((GUARD *)pso)->pfall);
        }
        float speed = pjmpr->pasega->speed;
        QW position = pjmpr->pso->paloParent->pos;
        scale.q = VectorFromFloat(speed * speed);
        vGrav.q = VectorScaleX(pjmpr->pjmpt->vGravity, scale.q);
        dpos.q = VectorSub(pjmpr->posTarget, position);
        float dt;
        if (pjmpr->fGuided != 0) {
            if (pjmpr->pvTarget != 0 && (FIsBasicDerivedFrom(pjmpr->pvTarget, 0x13) || FIsBasicDerivedFrom(pjmpr->pvTarget, 0xB)))
                dt = DtSolveJumpLaunch(dpos.q, vGrav.q, 1250.0f, 0.0f, 1.1f, 50.0f);
            else if (pjmpr->fFar != 0)
                dt = DtSolveJumpLaunch(dpos.q, vGrav.q, 1500.0f, -1500.0f, 1.33f, -1.33f);
            else
                dt = DtSolveJumpLaunch(dpos.q, vGrav.q, 1250.0f, -1250.0f, 1.1f, -1.1f);
        } else {
            dt = pjmpr->pjmpt->dtFlight / speed;
        }
        float dtMin = pjmpr->pjmpt->dtMin / speed;
        dt = dtMin > dt ? dtMin : dt;
        SO *pso = pjmpr->pso;
        QW scaleA = VectorFromFloat(1.0f / dt);
        QW scaleB = VectorFromFloat(dt * -0.5f);
        velocity.q = BlendX(scaleA, dpos.q, scaleB, vGrav.q);
        pso->vptr->SetVelocity((char *)pso + pso->vptr->delta, velocity.q);
        float tLand = g_2dded0[0] + dt;
        pjmpr->tLand = tLand;
        pjmpr->tPeak = tLand - pjmpr->pjmpt->dtMin / speed;
        if (pjmpr->fGuided != 0) {
            scale.q = VectorFromFloat(dt);
            vLand.q = ScaleAddX(velocity.q, vGrav.q, scale.q);
            QW pos = ConvertXfPos(0, pjmpr->pso->paloParent->pxf, pjmpr->posTarget);
            QW vel = ConvertXfVec(0, pjmpr->pso->paloParent->pxf, vLand.q);
            pjmpr->iPredict = func_0012DE58(pjmpr->pso, pjmpr->pso->paloParent, 5, pos, vel, pjmpr->tLand);
            pjmpr->pso->grf |= 0x4000000;
            RecalcSwOxfFilterForObject(D_3DD490, pjmpr->pso);
        }
        SetSoDvGravity(pjmpr->pso, vGrav.q);
        break;
    }
    case 2:
        SeekAsega(pjmpr->pasega, 0, pjmpr->pjmpt->tSeek2, 1.0f);
        break;
    case 3:
        SeekAsega(pjmpr->pasega, 0, pjmpr->pjmpt->tSeek3, 1.0f);
        if (pjmpr->pvTarget != 0)
            SetGuardPathTarget(pjmpr->pso, pjmpr->pvTarget, pjmpr->pvTarget2);
        break;
    case 4:
        if (pjmpr->fGuided != 0)
            EndJumperFlight(pjmpr);
        SetSoDvGravity(pjmpr->pso, pjmpr->vGravity);
        if (FIsBasicDerivedFrom(pjmpr->pso, 0x38))
            EnableFallCheck(((GUARD *)pjmpr->pso)->pfall);
        break;
    }
}
