#include "vu0inline.h"
#include "stepguard.h"
#include "sly.h"
#include "clq.h"
#include "goals.h"
struct LSG { QW pos; u8 unknown_0x10[0x50]; };
struct HITOBJ { u8 unknown_0x0[0x14]; JT **pptarget; };
struct HIT { u8 unknown_0x0[4]; HITOBJ *pobj; };
extern "C" {
void CStackFrame_Construct(void *);
void CStackFrame_Destructor(void *, int);
void CalculateVectorPanTilt__FP6VECTORPfT1(QW, float *, float *);
void DecomposeSphere(QW, float *, float *, float *);
int FIsBasicDerivedFrom(void *, int);
QW *PmatLoWorld(void *);
QW PosLoWorld(void *);
HIT *PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG(int, QW, QW, int, int, LSG *);
float RadYawSo(void *);
void bevy_camera_follow_push_out(void *, QW, QW, void *, void *, int *, int *);
extern char B_003DD490;
extern char FFilterOxaBasic;
extern float g_2dded0;
}
int FCheckLm(LM *, float);
float RadNormalize(float);
extern "C" int func_00175D00(GOALNOTICE *pcheck)
{
    STEPGUARD *pactor = (STEPGUARD *)pcheck->pstep;
    if (!(pactor->grf & 8) || pactor->paimstate || pcheck->prange)
        return 0;
    if (!pcheck->ptarget)
        return 0;
    if (((pcheck->ptarget->grfo >> 60) & 1) == 0)
        return 0;
    if (FIsBasicDerivedFrom(pcheck->ptarget, 0x32)) {
        if (((JT *)pcheck->ptarget)->NAlertLevel() == 2)
            return 0;
    }
    int fForce = 0;
    if (FIsBasicDerivedFrom(pcheck->ptarget, 0x34)) {
        JT *ptarget = (JT *)pcheck->ptarget;
        if (ptarget->field_0x4CC != -1) {
            if (ptarget->attachKind < 5)
                fForce = ptarget->attachKind >= 3;
        }
        if (ptarget->jmpState != -1) {
            if ((ptarget->jmpState ^ 0x11) == 0)
                fForce = 1;
        }
        if (~ptarget->field_0xF54 != 0)
            fForce = 1;
        if (FIsBasicDerivedFrom(ptarget, 0x35)) {
            switch (((SLY *)ptarget)->jts) {
            case 3:
            case 0x15:
            case 0x16:
                fForce = 1;
                break;
            }
        }
    }
    char frame[0x10];
    LSG lsg;
    float yaw, pitch, dist, pan;
    int count, list;
    QW posActor = PosLoWorld(((STEPGUARD *)pcheck->pstep));
    QW posTarget = PosLoWorld(pcheck->ptarget);
    QW delta = VectorSub(posTarget, posActor);
    float yawSo = RadYawSo(((STEPGUARD *)pcheck->pstep));
    DecomposeSphere(delta, &yaw, &pitch, &dist);
    if (!FCheckLm((LM *)((STEPGUARD *)pcheck->pstep)->lmDistance, dist))
        return 0;
    float yawDiff = RadNormalize(yaw - yawSo);
    if (!FCheckLm((LM *)((STEPGUARD *)pcheck->pstep)->lmYaw, yawDiff))
        return 0;
    CalculateVectorPanTilt__FP6VECTORPfT1(*PmatLoWorld(((STEPGUARD *)pcheck->pstep)), 0, &pan);
    float pitchDiff = RadNormalize(pitch - pan);
    if (!FCheckLm((LM *)((STEPGUARD *)pcheck->pstep)->lmPitch, pitchDiff))
        return 0;
    if (!fForce) {
        if (pcheck->state == 0) {
            if (g_2dded0 - pcheck->tState < 3.0f)
                return 0;
        } else if (pcheck->state != 2) {
            return 0;
        }
    }
    CStackFrame_Construct(frame);
    bevy_camera_follow_push_out(&B_003DD490, posActor, posTarget, &FFilterOxaBasic, ((STEPGUARD *)pcheck->pstep)->poxa, &count, &list);
    HIT *phit = PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG(0, posActor, posTarget, count, list, &lsg);
    if (phit && *phit->pobj->pptarget != (JT *)pcheck->ptarget) {
        CStackFrame_Destructor(frame, 2);
        return 0;
    }
    CStackFrame_Destructor(frame, 2);
    return 1;
}
