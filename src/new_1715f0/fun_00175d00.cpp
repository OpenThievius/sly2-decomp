#include "vu0inline.h"
#include "stepguard.h"
#include "sly.h"
#include "clq.h"
/* The guard's sight limits, read only here (the class is a guess from grf, paimstate and poxa): a local view. */
struct GUARDSIGHTVIEW { u8 unknown_0x0[0xF48]; LM lmDistance; LM lmYaw; LM lmPitch; };
struct LSG { QW pos; u8 unknown_0x10[0x50]; };
struct HITOBJ { u8 unknown_0x0[0x14]; JT **pptarget; };
struct HIT { u8 unknown_0x0[4]; HITOBJ *pobj; };
struct GUARDCHECK { u8 unknown_0x0[0x10]; STEPGUARD *pactor; u8 unknown_0x14[0x30 - 0x14]; JT *ptarget; int field_0x34; float field_0x38; int field_0x3C; };
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
extern "C" int func_00175D00(GUARDCHECK *pcheck)
{
    STEPGUARD *pactor = pcheck->pactor;
    if (!(pactor->grf & 8) || pactor->paimstate || pcheck->field_0x3C)
        return 0;
    if (!pcheck->ptarget)
        return 0;
    if (((pcheck->ptarget->grfo >> 60) & 1) == 0)
        return 0;
    if (FIsBasicDerivedFrom(pcheck->ptarget, 0x32)) {
        if (pcheck->ptarget->NAlertLevel() == 2)
            return 0;
    }
    int fForce = 0;
    if (FIsBasicDerivedFrom(pcheck->ptarget, 0x34)) {
        JT *ptarget = pcheck->ptarget;
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
    QW posActor = PosLoWorld(pcheck->pactor);
    QW posTarget = PosLoWorld(pcheck->ptarget);
    QW delta = VectorSub(posTarget, posActor);
    float yawSo = RadYawSo(pcheck->pactor);
    DecomposeSphere(delta, &yaw, &pitch, &dist);
    if (!FCheckLm(&((GUARDSIGHTVIEW *)pcheck->pactor)->lmDistance, dist))
        return 0;
    float yawDiff = RadNormalize(yaw - yawSo);
    if (!FCheckLm(&((GUARDSIGHTVIEW *)pcheck->pactor)->lmYaw, yawDiff))
        return 0;
    CalculateVectorPanTilt__FP6VECTORPfT1(*PmatLoWorld(pcheck->pactor), 0, &pan);
    float pitchDiff = RadNormalize(pitch - pan);
    if (!FCheckLm(&((GUARDSIGHTVIEW *)pcheck->pactor)->lmPitch, pitchDiff))
        return 0;
    if (!fForce) {
        if (pcheck->field_0x34 == 0) {
            if (g_2dded0 - pcheck->field_0x38 < 3.0f)
                return 0;
        } else if (pcheck->field_0x34 != 2) {
            return 0;
        }
    }
    CStackFrame_Construct(frame);
    bevy_camera_follow_push_out(&B_003DD490, posActor, posTarget, &FFilterOxaBasic, pcheck->pactor->poxa, &count, &list);
    HIT *phit = PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG(0, posActor, posTarget, count, list, &lsg);
    if (phit && *phit->pobj->pptarget != pcheck->ptarget) {
        CStackFrame_Destructor(frame, 2);
        return 0;
    }
    CStackFrame_Destructor(frame, 2);
    return 1;
}
