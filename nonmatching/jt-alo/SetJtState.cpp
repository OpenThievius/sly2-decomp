// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "jt.h"
#include "ps2inline.h"
#include "vu0inline.h"

/* SetJtState: leave the old state (jts), enter the new one, set the behaviour substate (jtbs), stamp the times, set the lookats,
   start the state's sound and apply its animation (an ASEG or a state machine). Fields past JT's 0x1320 bytes are Sly's. */

#define FIELD(type, offset) (*(type *)((char *)pjt + (offset)))

struct SM;
struct SO;
struct XA;
struct SW;
struct ASEG;
enum OID { OID_NIL = -1 };
union VU_SCALE { QW q; VECTOR v; };
struct MATROWS3 { QW row[3]; };
struct EFFECT { QW mat[3]; QW pos; };

void RemoveSoXa(SO *pso, XA *pxa);
void FreeSwXaList(SW *psw, XA *pxa);
int IsmsFindSmOptional(SM *psm, OID oid);
void GetJtHangHeading(JT *pjt, float *prad);
float RadNormalize(float rad);
void CalculateJtHangAccel(JT *pjt);
void ChooseJtRushTarget(JT *pjt);
void ChooseJtSmashTarget(JT *pjt);
void FixStepAngularVelocity(STEP *pstep);
float TFindAsegLabel(ASEG *paseg, OID oid);

extern "C" {
QW SetVectorCylind__FP6VECTORfff(float rad, float sXY, float sZ);
QW PosLoWorld(void *plo);
void SetXfKind(JT *pjt, void *pxf, int kind);
void SetJtJtcs(JT *pjt, int jtcs);
void ScheduleJtGlance(JT *pjt);
void *NewEmitter(int sid);
void SetEmitterUnpositioned(void *pemitter, void *palo);
void SetAmbVolume(void *pamb, float uVolume);
void SetAmbRange(void *pamb, float sStart, float sFull);
void SetAmbPos(void *pamb, QW pos);
void ExplodeExpl(LO *pexpl);
void SetJmpBodyState(void *pjmp, int state, int arg);
void UnsubscribeLoObject(LO *plo, JT *pjt);
void SubscribeLoObject(LO *plo, JT *pjt);
void RemoveXfAct(JT *pjt, void *pxf, void *pact);
void InsertXfAct(JT *pjt, void *pxf, void *pact);
void func_00140C88(JT *pjt, void *ptunnel);
void SetJtZapState(void *pzap, int state);
void bevy_player_p25_1375d0(void *p, int state);
int bevy_player_p25_1374f0(void *p);
void SetAttachSubstate(void *pattach, int state);
void SetJtPipeState(void *ppipe, int state);
void func_001F2A60(JT *pjt, int arg);
int FAsegaGone(void *pasega);
void func_00209EE0(void *plo);
void bevy_camera_follow_activity(void *pcm, int kind, JT *pjt);
void CarryThrow_SetState(void *pcarry, int state);
void SetSoCnstrForce(JT *pjt, int f);
int func_001430C8(JT *pjt);
void func_00142868(JT *pjt, int f);
void ResetRunBlendFootsteps(void *prunblend);
QW PosJtHangGrip(JT *pjt);
void UpdateJtHangPose(JT *pjt);
void SetStepRadTarget(JT *pjt, float rad);
void SetBinocState(void *pbinoc, int state);
void bevy_player_p13_18df50(JT *pjt, int arg);
int FGadgetAcquired(int gadget);
void func_0018E1E0(JT *pjt);
void SetStepRadTargetDir(JT *pjt, QW dir);
void PredictAsegEffect(ASEG *paseg, JT *pjt, int arg2, int arg3, float t, float svt, EFFECT *peffect, int arg7);
void Spire_FindClosestPoint(LO *pspire, QW pos, int arg2, void *presult, int arg4, int arg5);
void ReblendAsegbl(void *pasegbl);
void SetJtLookats(JT *pjt, int grf);
void RetractAsega(LO *pasega);
void RetractSma(LO *psma);
void ApplyAseg(ASEG *paseg, JT *pjt, float t, float svt, int grfapl, void *phandle);
LO *PsmaApplySmEx(SM *psm, JT *pjt, int oid, int grfapl, int grfsmt);
extern float g_2dded0;
extern QW g_2a2dd0;
extern char B_002DEB30[];
extern SW B_003DD490;
extern float D_002BF3E0;
extern float D_002BF3E4;
extern float D_002BF3E8;
extern float D_002BF358;
extern float D_002BF35C;
}

static inline void ClearVectorXyz(VECTOR *pv)
{
    pv->z = 0.0f;
    pv->y = 0.0f;
    pv->x = 0.0f;
}

extern "C" void SetJtState(JT *pjt, int jtsNew, int jtbsNew)
{
    VU_SCALE scale;
    EFFECT effect;
    float radHeading;
    LO *pexpl;
    int sid = -1;
    ASEG *paseg = 0;
    int grfLookats = 0;
    int oid = -1;
    int grfapl = 1;
    float t = 0.0f;
    float svt = 1.0f;
    SM *psm = 0;
    int grfsmt = 0xFFFC;
    int fKeepAnim = 0;

    if (FIELD(int, 0x18C8) == jtsNew) {
        if (FIELD(int, 0x18D0) == jtbsNew) {
            return;
        }
    } else {
        if (jtsNew == 2) {
            switch (FIELD(int, 0x18C8)) {
            case 3:
            case 0x16:
                FIELD(int, 0x37C) = FIELD(int, 0x18C4);
                break;
            case 8:
                FIELD(int, 0x37C) = FIELD(int, 0xF5C);
                break;
            case 0x15:
                FIELD(int, 0x37C) = FIELD(int, 0x1F18);
                break;
            default:
                FIELD(int, 0x37C) = 0;
                break;
            }
        }

        switch (FIELD(int, 0x18C8)) {
        case 2: {
            switch (jtsNew) {
            case 3:
            case 8:
            case 0x12:
                break;
            case 7:
                if (FIELD(int, 0x4C8) == 1) {
                    break;
                }
            default: {
                void *pemitter = NewEmitter(0x3D);
                SetEmitterUnpositioned(pemitter, pjt);
                SetAmbVolume(pemitter, 0.7f);
                SetAmbRange(pemitter, 500.0f, 1000.0f);
                break;
            }
            }
            if (FIELD(int, 0x18D8) == 0 && jtsNew != 8 && jtsNew != 3 && jtsNew != 0x16) {
                SetJtJtcs(pjt, -1);
            }
            if (FIELD(int, 0x108C) == 0) {
                pexpl = 0;
                switch (jtsNew) {
                case 7:
                    switch (FIELD(int, 0x4C8)) {
                    case 1:
                        break;
                    case 3:
                    case 4:
                        pexpl = FIELD(LO *, 0x1AAC);
                        break;
                    default:
                        pexpl = FIELD(LO *, 0x1AA8);
                        break;
                    }
                    break;
                case 0:
                case 1:
                case 5:
                case 9:
                case 0x18:
                    pexpl = FIELD(LO *, 0x1AA8);
                    break;
                }
                if (pexpl != 0) {
                    pexpl->Add();
                    ExplodeExpl(pexpl);
                    pexpl->Remove();
                }
            }
            SetJmpBodyState((char *)pjt + 0x2C0, -1, 0);
            break;
        }
        case 3: {
            XA *pxa;
            FIELD(LO *, 0x18C4)->HandleSpliceEvent(6, 0, 0, 0, 0);
            UnsubscribeLoObject(FIELD(LO *, 0x18C4), pjt);
            SetJtJtcs(pjt, -1);
            RemoveXfAct(pjt, FIELD(void *, 0x19C0), FIELD(void *, 0x1A00));
            pxa = FIELD(XA *, 0x1900);
            if (pxa != 0) {
                RemoveSoXa(*(SO **)((char *)pxa + 4), pxa);
                FreeSwXaList(&B_003DD490, FIELD(XA *, 0x1900));
                FIELD(XA *, 0x1900) = 0;
            }
            func_00140C88(pjt, 0);
            break;
        }
        case 8: {
            int jtcs;
            SetJtPipeState((char *)pjt + 0xF50, -1);
            jtcs = -1;
            if (jtsNew == 2 && FIELD(int, 0x14D8) != 0) {
                jtcs = 0xB;
            }
            SetJtJtcs(pjt, jtcs);
            break;
        }
        case 7:
            SetAttachSubstate((char *)pjt + 0x4C0, -1);
            break;
        case 4:
            SetJtZapState((char *)pjt + 0xDF0, -1);
            break;
        case 0x17:
            CarryThrow_SetState((char *)pjt + 0x11B0, -1);
            break;
        case 6:
            bevy_player_p25_1375d0((char *)pjt + 0x1FF0, -1);
            break;
        case 9:
            FIELD(int, 0x18C0) = 0;
            func_001F2A60(pjt, FIELD(int, 0x1A90));
            break;
        case 0:
            SetXfKind(pjt, FIELD(void *, 0x58), 2);
            SetXfKind(pjt, FIELD(void *, 0x5C), 2);
            switch (FIELD(int, 0x18D8)) {
            case 6:
                SetJtJtcs(pjt, 4);
                break;
            case 7:
                SetJtJtcs(pjt, 5);
                break;
            case 8:
            case 9:
                SetJtJtcs(pjt, -1);
                break;
            case 0xC:
                if (jtbsNew != 6) {
                    SetJtJtcs(pjt, 0xE);
                }
                break;
            case 0xD:
                if (jtbsNew != 7) {
                    SetJtJtcs(pjt, 0xF);
                }
                break;
            }
            ScheduleJtGlance(pjt);
            break;
        case 0xB:
            FIELD(int, 0x10E0) &= ~2;
            break;
        case 1:
        case 10:
        case 12: {
            char *pasega = FIELD(char *, 0x1030);
            FIELD(float, 0x1A0) = *(float *)(pasega + 0x1C) / *(float *)(*(char **)(pasega + 0x14) + 0x74);
            break;
        }
        case 0x10:
            if (FIELD(void *, 0x1030) != 0 && !FAsegaGone(FIELD(void *, 0x1030))) {
                func_00209EE0(FIELD(void *, 0x10DC));
            }
            FIELD(int, 0x1D2C) = 0;
            FIELD(int, 0x10E0) &= ~4;
            break;
        case 0x12:
        case 0x13:
        case 0x14:
            SetXfKind(pjt, FIELD(void *, 0x58), 2);
            SetXfKind(pjt, FIELD(void *, 0x5C), 2);
            break;
        case 0x15:
            SetSoCnstrForce(pjt, 0);
            FIELD(LO *, 0x1F18)->HandleSpliceEvent(6, 0, 0, 0, 0);
            if (FIELD(int, 0x1024) == *(int *)((char *)FIELD(LO *, 0x1F18) + 0x110)) {
                func_00140C88(pjt, 0);
            }
            FIELD(LO *, 0x1F18) = 0;
            break;
        case 0x16:
            SetSoCnstrForce(pjt, 0);
            FIELD(LO *, 0x18C4)->HandleSpliceEvent(6, 0, 0, 0, 0);
            UnsubscribeLoObject(FIELD(LO *, 0x18C4), pjt);
            FIELD(LO *, 0x18C4) = 0;
            func_00140C88(pjt, 0);
            break;
        case 0x11:
            FIELD(int, 0x1D30) = 0;
            bevy_camera_follow_activity(B_002DEB30, 0x38, pjt);
            break;
        case 0x18:
            FIELD(float, 0x200) = 1.0f;
            *(float *)(FIELD(char *, 0x150) + 0x18) = FIELD(float, 0x1A8);
            break;
        case 0xD:
            FIELD(int, 0x18C0) = 0;
            break;
        }

        switch (jtsNew) {
        case 0: {
            int jts;
            psm = FIELD(SM *, 0x1028);
            SetXfKind(pjt, FIELD(void *, 0x58), 1);
            SetXfKind(pjt, FIELD(void *, 0x5C), 1);
            jts = FIELD(int, 0x18C8);
            FIELD(int, 0x1514) = 0;
            switch (jts) {
            case 10:
                oid = 0x177;
                break;
            case 2: {
                int fHigh = FIELD(int, 0x18F0);
                if (fHigh == -1) {
                    QW pos = PosLoWorld(pjt);
                    fHigh = D_002BF3E0 < FIELD(float, 0x2FC) - LaneZInGeneralRegister(pos);
                }
                oid = (fHigh == 1) ? 0x179 : 0x178;
                break;
            }
            case 12:
                oid = 0x176;
                break;
            default:
                oid = 0x175;
                break;
            }
            if (IsmsFindSmOptional(psm, (OID)oid) < 0) {
                oid = -1;
            }
            grfsmt = func_001430C8(pjt);
            ClearVectorXyz(&FIELD(VECTOR, 0x190));
            if (FIELD(int, 0x1A54) != 0 && FIELD(int, 0x1A70) != 0) {
                switch (FIELD(int, 0x18D8)) {
                case 4:
                    SetJtJtcs(pjt, 6);
                    break;
                case 5:
                    SetJtJtcs(pjt, 7);
                    break;
                }
            }
            grfLookats = 0x1F;
            func_00142868(pjt, 1);
            break;
        }
        case 1:
            paseg = FIELD(ASEG *, 0x1324);
            grfapl = 9;
            t = FIELD(float, 0x1A0) * *(float *)((char *)paseg + 0x74);
            ResetRunBlendFootsteps((char *)pjt + 0x1320);
            break;
        case 6: {
            char *p = (char *)pjt + 0x1FF0;
            fKeepAnim = 1;
            bevy_player_p25_1375d0(p, bevy_player_p25_1374f0(p));
            break;
        }
        case 3: {
            int kind;
            FIELD(int, 0x18F8) = -1;
            FIELD(float, 0x199C) = 1.0f;
            FIELD(float, 0x1998) = 1.0f;
            FIELD(float, 0x18F4) = g_2dded0;
            svt = 0.0f;
            paseg = FIELD(ASEG *, 0x1994);
            ClearVectorXyz((VECTOR *)(FIELD(char *, 0x1A00) + 0x20));
            t = 0.5f;
            InsertXfAct(pjt, FIELD(void *, 0x19C0), FIELD(void *, 0x1A00));
            {
                QW posGrip = PosLoWorld(FIELD(void *, 0x19A4));
                FIELD(QW, 0x1960) = VectorSub(posGrip, PosJtHangGrip(pjt));
            }
            UpdateJtHangPose(pjt);
            FIELD(LO *, 0x18C4)->HandleSpliceEvent(5, 0, 0, 0, 0);
            SubscribeLoObject(FIELD(LO *, 0x18C4), pjt);
            GetJtHangHeading(pjt, &radHeading);
            {
                float radReverse = RadNormalize(radHeading + 3.1415927f);
                kind = 1;
                if (FIELD(LO *, 0x18C4) != 0) {
                    kind = *(int *)((char *)FIELD(LO *, 0x18C4) + 0x124);
                }
                switch (kind) {
                case 0:
                    if (__builtin_fabsf(RadNormalize(radHeading - *(float *)(FIELD(char *, 0x150) + 0x18))) < 1.5707964f) {
                        goto forward;
                    }
                    goto reverse;
                case 1:
                forward:
                    SetStepRadTarget(pjt, radHeading);
                    FIELD(int, 0x18FC) = 0;
                    break;
                case 2:
                reverse:
                    SetStepRadTarget(pjt, radReverse);
                    FIELD(int, 0x18FC) = 1;
                    break;
                }
            }
            sid = *(int *)((char *)FIELD(LO *, 0x18C4) + 0x12C);
            SetJtJtcs(pjt, 1);
            ClearVectorXyz(&FIELD(VECTOR, 0x190));
            CalculateJtHangAccel(pjt);
            func_00140C88(pjt, *(void **)((char *)FIELD(LO *, 0x18C4) + 0x100));
            break;
        }
        case 8:
            SetJtPipeState((char *)pjt + 0xF50, 0);
            fKeepAnim = 1;
            break;
        case 4:
            SetBinocState((char *)pjt + 0xF00, -1);
            bevy_player_p13_18df50(pjt, 0);
            break;
        case 7: {
            int kind = FIELD(int, 0x4C8);
            if (kind < 5) {
                grfLookats = (kind < 3) ? 0 : 7;
            }
            break;
        }
        case 0x17:
            fKeepAnim = 1;
            break;
        case 9:
            SetJtJtcs(pjt, -1);
            ChooseJtRushTarget(pjt);
            paseg = FIELD(ASEG *, 0x1A7C);
            break;
        case 13:
            SetJtJtcs(pjt, -1);
            ClearVectorXyz(&FIELD(VECTOR, 0x190));
            ChooseJtSmashTarget(pjt);
            paseg = FIELD(ASEG *, 0x1A80);
            FIELD(float, 0x19B0) = g_2dded0 + D_002BF3E4;
            break;
        case 14:
            SetJtJtcs(pjt, -1);
            ClearVectorXyz(&FIELD(VECTOR, 0x190));
            paseg = FIELD(ASEG *, 0x1A84);
            break;
        case 10:
            paseg = FIELD(ASEG *, 0x1BC0);
            grfapl = 9;
            t = FIELD(float, 0x1A0) * *(float *)((char *)paseg + 0x74);
            FIELD(int, 0x1038) = -1;
            break;
        case 11:
            paseg = FIELD(ASEG *, 0x1BC8);
            FIELD(int, 0x10E0) |= 2;
            grfLookats = 100;
            FIELD(QW, 0x190) = g_2a2dd0;
            FIELD(int, 0x1BD4) = 0;
            break;
        case 12:
            paseg = FIELD(ASEG *, 0x1C34);
            grfapl = 9;
            t = FIELD(float, 0x1A0) * *(float *)((char *)paseg + 0x74);
            ResetRunBlendFootsteps((char *)pjt + 0x1C30);
            break;
        case 0x10:
            FIELD(int, 0x10E0) |= 4;
            if (FGadgetAcquired(0x1C)) {
                MATROWS3 *pmat;
                paseg = FIELD(ASEG *, 0x2050);
                func_0018E1E0(pjt);
                scale.q = VectorFromFloat(-1.0f);
                pmat = &FIELD(MATROWS3, 0x1B0);
                pjt->Slot35(TransformVector(VectorScaleX(FIELD(QW, 0x190), scale.q), pmat->row[0], pmat->row[1], pmat->row[2]));
                FixStepAngularVelocity(pjt);
            } else {
                float z;
                float tLabel;
                MATROWS3 *pmat;
                paseg = FIELD(ASEG *, 0x1D1C);
                {
                    QW posTarget = PosLoWorld(FIELD(void *, 0x10DC));
                    z = 0.0f;
                    {
                        QW dir = VectorSub(posTarget, PosLoWorld(pjt));
                        scale.q = VectorFromFloat(-1.0f);
                        SetStepRadTargetDir(pjt, VectorScaleX(dir, scale.q));
                    }
                }
                FixStepAngularVelocity(pjt);
                tLabel = TFindAsegLabel(paseg, (OID)0x173);
                PredictAsegEffect(paseg, pjt, *(int *)(FIELD(char *, 0x19A4) + 0x60), FIELD(int, 0x60), tLabel, z, &effect, 0);
                tLabel = tLabel / *(float *)((char *)paseg + 0x78);
                {
                    QW posT = PosLoWorld(FIELD(void *, 0x10DC));
                    QW posPred;
                    scale.q = QuadFromFloat(tLabel);
                    posPred = ScaleAddX(posT, FIELD(LO *, 0x10DC)->GetVelocityVec(), scale.q);
                    pmat = &FIELD(MATROWS3, 0x1B0);
                    posPred = VectorSub(posPred, TransformVector(effect.pos, pmat->row[0], pmat->row[1], pmat->row[2]));
                    FIELD(QW, 0x190) = ScaleByReciprocalX(VectorSub(posPred, PosLoWorld(pjt)), scale.q);
                }
                FIELD(float, 0x198) = z;
                pjt->Slot35(FIELD(QW, 0x190));
            }
            break;
        case 0x12:
            psm = FIELD(SM *, 0x102C);
            SetXfKind(pjt, FIELD(void *, 0x58), 1);
            SetXfKind(pjt, FIELD(void *, 0x5C), 1);
            ClearVectorXyz(&FIELD(VECTOR, 0x190));
            SetJtJtcs(pjt, -1);
        case 0x13:
            SetXfKind(pjt, FIELD(void *, 0x58), 1);
            SetXfKind(pjt, FIELD(void *, 0x5C), 1);
            ClearVectorXyz(&FIELD(VECTOR, 0x190));
            SetJtJtcs(pjt, -1);
            break;
        case 0x14:
            SetXfKind(pjt, FIELD(void *, 0x58), 2);
            SetXfKind(pjt, FIELD(void *, 0x5C), 2);
            ClearVectorXyz(&FIELD(VECTOR, 0x190));
            SetJtJtcs(pjt, -1);
            break;
        case 0x11:
            paseg = FIELD(ASEG *, 0x1D34);
            grfapl = 9;
            bevy_camera_follow_activity(B_002DEB30, 0x37, pjt);
            break;
        case 0x15:
            Spire_FindClosestPoint(FIELD(LO *, 0x1F18), PosLoWorld(pjt), 0, (char *)pjt + 0x1F1C, 0, 0);
            SetSoCnstrForce(pjt, 1);
            pjt->Slot35(g_2a2dd0);
            pjt->Slot36(g_2a2dd0);
            ClearVectorXyz(&FIELD(VECTOR, 0x190));
            FIELD(LO *, 0x1F18)->HandleSpliceEvent(5, 0, 0, 0, 0);
            if (*(void **)((char *)FIELD(LO *, 0x1F18) + 0x110) != 0) {
                func_00140C88(pjt, *(void **)((char *)FIELD(LO *, 0x1F18) + 0x110));
            }
            break;
        case 0x16:
            paseg = FIELD(ASEG *, 0x1F90);
            grfapl = 9;
            SetJtJtcs(pjt, -1);
            SetSoCnstrForce(pjt, 1);
            pjt->Slot35(g_2a2dd0);
            pjt->Slot36(g_2a2dd0);
            ClearVectorXyz(&FIELD(VECTOR, 0x190));
            FIELD(LO *, 0x18C4)->HandleSpliceEvent(5, 0, 0, 0, 0);
            SubscribeLoObject(FIELD(LO *, 0x18C4), pjt);
            func_00140C88(pjt, *(void **)((char *)FIELD(LO *, 0x18C4) + 0x100));
            break;
        case 0x18: {
            float zero = 0.0f;
            grfapl = 9;
            grfLookats = 0x18;
            FIELD(float, 0x202C) = zero;
            FIELD(float, 0x2014) = zero;
            FIELD(float, 0x2020) = 1.0f;
            ReblendAsegbl(FIELD(void *, 0x2038));
            paseg = FIELD(ASEG *, 0x2038);
            SetStepRadTarget(pjt, *(float *)(FIELD(char *, 0x150) + 0x18));
            {
                QW vel = SetVectorCylind__FP6VECTORfff(FIELD(float, 0x1A8), D_002BF3E8, zero);
                VECTOR *pv;
                pjt->Slot35(vel);
                pv = &FIELD(VECTOR, 0x190);
                pv->z = zero;
                pv->y = zero;
                pv->x = zero;
            }
            break;
        }
        }
    }

    if (FIELD(int, 0x18D0) != jtbsNew) {
        switch (jtbsNew) {
        case -1:
            break;
        case 0:
        case 1:
        case 2: {
            char *pasega = FIELD(char *, 0x1030);
            if (pasega != 0 && *(ASEG **)(pasega + 0x14) == FIELD(ASEG *, 0x1994)) {
                fKeepAnim = 1;
            } else {
                paseg = FIELD(ASEG *, 0x1994);
                svt = 0.0f;
                t = *(float *)((char *)paseg + 0x74) * 0.5f;
            }
            break;
        }
        case 3:
            psm = FIELD(SM *, 0x1950);
            break;
        case 4:
            psm = FIELD(SM *, 0x1BC4);
            ClearVectorXyz(&FIELD(VECTOR, 0x190));
            break;
        case 5:
            paseg = FIELD(ASEG *, 0x14D0);
            FIELD(int, 0x1038) = -1;
            ClearVectorXyz(&FIELD(VECTOR, 0x190));
            grfapl = 9;
            break;
        case 6:
            SetJtJtcs(pjt, -1);
            paseg = FIELD(ASEG *, 0x1D08);
            ClearVectorXyz(&FIELD(VECTOR, 0x190));
            FIELD(int, 0x18E8) = 0;
            FIELD(int, 0x18E4) = 0;
            break;
        case 7:
            SetJtJtcs(pjt, -1);
            paseg = FIELD(ASEG *, 0x1D0C);
            ClearVectorXyz(&FIELD(VECTOR, 0x190));
            FIELD(int, 0x18E8) = 0;
            FIELD(int, 0x18E4) = 0;
            break;
        case 8:
        case 9:
            if (jtbsNew == 8) {
                paseg = FIELD(ASEG *, 0x1D10);
            } else {
                paseg = FIELD(ASEG *, 0x1FE8);
            }
            FIELD(int, 0x18E4) = 0;
            ClearVectorXyz(&FIELD(VECTOR, 0x190));
            break;
        case 10:
            psm = FIELD(SM *, 0x1F14);
            break;
        case 11:
            paseg = FIELD(ASEG *, 0x1F10);
            grfapl = 9;
            break;
        case 12:
            grfLookats = 0x18;
            FIELD(float, 0x200) = D_002BF358;
            break;
        case 13:
            fKeepAnim = 1;
            grfLookats = 0x18;
            FIELD(float, 0x200) = D_002BF35C;
            break;
        }
    }

    if (jtsNew != FIELD(int, 0x18C8)) {
        FIELD(int, 0x18C8) = jtsNew;
        FIELD(float, 0x18CC) = g_2dded0;
    }
    if (jtbsNew != FIELD(int, 0x18D0)) {
        FIELD(int, 0x18D0) = jtbsNew;
        FIELD(float, 0x18D4) = g_2dded0;
    }
    pjt->Slot90();
    SetJtLookats(pjt, grfLookats);
    if (sid != -1) {
        void *pemitter = NewEmitter(sid);
        SetEmitterUnpositioned(pemitter, 0);
        SetAmbPos(pemitter, PosLoWorld(pjt));
    }
    if (!fKeepAnim) {
        if (FIELD(LO *, 0x1030) != 0) {
            RetractAsega(FIELD(LO *, 0x1030));
            FIELD(LO *, 0x1030)->Slot2();
            FIELD(LO *, 0x1030) = 0;
        } else if (FIELD(LO *, 0x1034) != 0) {
            RetractSma(FIELD(LO *, 0x1034));
            FIELD(LO *, 0x1034)->Slot2();
            FIELD(LO *, 0x1034) = 0;
        }
        if (paseg != 0) {
            ApplyAseg(paseg, pjt, t, svt, grfapl, (char *)pjt + 0x1030);
            FIELD(LO *, 0x1030)->OnAdd();
        } else if (psm != 0) {
            LO *psma = PsmaApplySmEx(psm, pjt, oid, grfapl, grfsmt);
            FIELD(LO *, 0x1034) = psma;
            psma->OnAdd();
        }
    }
}
