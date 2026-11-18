/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
#include "jt.h"
#include "ps2inline.h"
#include "vu0inline.h"
union VU_SCALE { QW q; VECTOR v; };
#define F(base, type, offset) (*(type *)((char *)(base) + (offset)))
struct JMP_ASEGS {
    char pad0[8];
    int iaseg;
    char pad_c[0x120 - 0xC];
    void *apasegLand[5];
    void *apasegFall[5];
};

static inline void ClearVelocity(char *lo)
{
    int *clear = (int *)(lo + 0x190);
    clear[2] = 0;
    clear[1] = 0;
    *(int *)(lo + 0x190) = 0;
}
extern "C" {
void ApplyAsegToHandle(void *, char *, int, char *, float, float);
void Carry_SetState(char *, int);
QW ConvertXfPos(void *, void *, QW);
QW ConvertXfVec(void *, void *, QW);
float DtSolveJumpLaunch(QW, QW, float, float, float, float);
int FIsBasicDerivedFrom(void *, int);
QW GetJmpLaunchVelocity(char *, int);
void GetNormalVectors__FP6VECTORN30(QW, QW, QW, QW *);
QW PosLoWorld(char *);
void ReblendAsegbl(void *);
void RecalcSwOxfFilterForObject(void *, void *);
void RetractSmaRef(char *);
void SetHbskHbsks(void *, int);
void SetJtJtcs(char *, int);
void SetSmaGoal__FP3SMA3OID(void *, int);
void SetSoNoXpsAll(char *, int);
void SetStepGravityRatio__FP4STEPf(char *, float);
void SetStepRadTarget(char *, float);
void SetStepRadTargetDir(char *, QW);
void SetXfKind(char *, void *, int);
int func_0012DE58(char *, void *, int, QW, QW, float);
void func_0012E460(char *);
void func_00140C88(char *, void *);
QW func_0019F3F8(char *, char *, float);
void func_00204F78(char *, int, int);
extern char B_003DD490[];
extern float D_FLT_002BF780[];
extern float D_FLT_002BF798[];
extern float D_FLT_002BF7A0;
extern QW g_2a2db0;
extern QW g_2a2dc0;
extern QW g_2a2dd0;
extern float g_2dded0;
extern char *g_2e1e40;

void SetJmpBodyState(char *jmp, int jmpbs, void *param)
{
    VU_SCALE temp;
    QW normals[3];
    VU_SCALE scale;
    VU_SCALE origin;
    VU_SCALE target;
    VU_SCALE dir;
    VU_SCALE gravity;
    VU_SCALE velocity;
    VU_SCALE landing;

    if (jmpbs == F(jmp, int, 0x1C))
        return;

    switch (F(jmp, int, 0x1C)) {
    case 17:
        func_00204F78(F(jmp, char *, 0), F(F(jmp, char *, 0xC8), int, 4), 0);
        F(jmp, void *, 0xC8) = 0;
        break;
    case 7: {
        void *object = F(jmp, void *, 0xC);
        F(jmp, void *, 0xC) = 0;
        RecalcSwOxfFilterForObject(B_003DD490, object);
        break;
    }
    case 6: {
        char *object = F(jmp, char *, 0xC);
        F(jmp, void *, 0xC) = 0;
        if (F(F(jmp, char *, 0), int, 0x4C8) != 1) {
            RecalcSwOxfFilterForObject(B_003DD490, object);
            if (F(object, int, 0x17C) == 1)
                SetHbskHbsks(object, 0);
        }
        char *lo = F(jmp, char *, 0);
        SetXfKind(lo, F(lo, void *, 0x58), 2);
        F(F(jmp, char *, 0), QW, 0x190) = g_2a2dd0;
        break;
    }
    case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 18: {
        char *lo = F(jmp, char *, 0);
        SetXfKind(lo, F(lo, void *, 0x58), 2);
        F(F(jmp, char *, 0), QW, 0x190) = g_2a2dd0;
        int state = F(jmp, int, 0x1C);
        if (state < 16) {
            if (state >= 14) {
                char *carrier = F(jmp, char *, 0);
                if (carrier != g_2e1e40)
                    Carry_SetState(carrier + 0x900, -1);
                else
                    SetJtJtcs(carrier, -1);
            }
        }
        break;
    }
    case 19: case 20:
        if (jmpbs < 21) {
            if (jmpbs >= 19)
                break;
        }
        {
            void *sma = F(F(jmp, char *, 0), void *, 0x1D28);
            if (sma != 0)
                SetSmaGoal__FP3SMA3OID(sma, 0x5F8);
            func_00140C88(F(jmp, char *, 0), 0);
        }
        break;
    case 21: {
        func_0012E460(jmp + 0x1F0);
        char *lo = F(jmp, char *, 0);
        SetXfKind(lo, F(lo, void *, 0x58), 2);
        SetSoNoXpsAll(F(jmp, char *, 0), 0);
        break;
    }
    }

    char *asegbl = F(F(jmp, char *, 0), char *, 0x1030);
    void *aseg = 0;
    F(jmp, int, 0x1C) = jmpbs;
    F(jmp, void *, 0xC) = param;
    int flags = 1;
    float tLocal = 0.0f;
    float rBlend = 1.0f;
    F(jmp, float, 0x20) = g_2dded0;

    switch (jmpbs) {
    case 17: {
        flags = 9;
        F(jmp, JT *, 0)->Slot91();
        func_00204F78(F(jmp, char *, 0), F(F(jmp, char *, 0xC8), int, 4), 1);
        temp.q = ConvertXfPos(F(F(jmp, char *, 0xC8), void *, 0), 0, F(jmp, QW, 0xD0));
        scale.q = VectorFromFloat(-1.0f);
        normals[0] = VectorScaleX(F(jmp, QW, 0xE0), scale.q);
        GetNormalVectors__FP6VECTORN30(normals[0], g_2a2dc0, g_2a2db0, &normals[1]);
        temp.q = VectorSub(temp.q, TransformVector(F(jmp, QW, 0xF0), normals[0], normals[1], normals[2]));
        QW pos = temp.q;
        char *body = F(jmp, char *, 0);
        F(body, QW, 0x1010) = VectorSub(pos, PosLoWorld(body));
        ClearVelocity(F(jmp, char *, 0));
        F(jmp, int, 0x28) = 0;
        aseg = F(jmp, void *, 0x154);
        if (F(jmp, int, 0x174) != 0) {
            SetStepGravityRatio__FP4STEPf(F(jmp, char *, 0), F(jmp, float, 0x168));
            func_00140C88(F(jmp, char *, 0), 0);
            F(jmp, int, 0x174) = 0;
        }
        break;
    }
    case 0: case 1: case 4: case 5: case 7:
        switch (F(jmp, int, 4)) {
        case 13:
            aseg = F(jmp, void *, 0x148);
            break;
        case 14:
            aseg = F(jmp, void *, 0x158);
            break;
        case 16:
            aseg = F(F(jmp, char *, 0), void *, 0x1514);
            break;
        case 15:
            aseg = F(F(jmp, char *, 0), void *, 0x1518);
            break;
        }
        if (aseg == 0) {
            aseg = ((JMP_ASEGS *)jmp)->apasegLand[((JMP_ASEGS *)jmp)->iaseg];
            if (aseg == 0)
                aseg = F(jmp, void *, 0x120);
        }
        break;
    case 2: case 3:
        if (F(jmp, int, 4) == 14)
            aseg = F(jmp, void *, 0x15C);
        if (aseg == 0) {
            aseg = ((JMP_ASEGS *)jmp)->apasegFall[((JMP_ASEGS *)jmp)->iaseg];
            if (aseg == 0) {
                aseg = F(jmp, void *, 0x134);
                if (aseg == 0)
                    aseg = F(jmp, void *, 0x120);
            }
        }
        F(jmp, int, 0x28) = 0;
        break;
    case 6: {
        char *lo = F(jmp, char *, 0);
        SetXfKind(lo, F(lo, void *, 0x58), 0x11);
        RecalcSwOxfFilterForObject(B_003DD490, param);
        SetHbskHbsks(param, 1);
        ClearVelocity(F(jmp, char *, 0));
        aseg = F(F(F(jmp, char *, 0), char *, 0x1030), void *, 0x14);
        break;
    }
    case 8: {
        char *lo = F(jmp, char *, 0);
        SetXfKind(lo, F(lo, void *, 0x58), 0x11);
        ClearVelocity(F(jmp, char *, 0));
        aseg = F(asegbl, void *, 0x14);
        break;
    }
    case 11: case 12: case 13: case 14: case 15: {
        char *lo = F(jmp, char *, 0);
        SetXfKind(lo, F(lo, void *, 0x58), 0x11);
        ClearVelocity(F(jmp, char *, 0));
        F(jmp, int, 0x28) = 0;
        F(jmp, int, 8) = 0;
        aseg = F(jmp, void *, 0x120);
        int state = F(jmp, int, 0x1C);
        if (state < 16) {
          if (state >= 14) {
            char *carrier = F(jmp, char *, 0);
            if (carrier == g_2e1e40) {
                F(carrier, void *, 0x1854) = F(jmp, void *, 0xC);
                SetJtJtcs(carrier, 0);
            } else {
                rBlend = 0.0f;
                F(carrier, void *, 0x984) = F(jmp, void *, 0xC);
                Carry_SetState(F(jmp, char *, 0) + 0x900, 0);
                aseg = F(F(jmp, char *, 0), void *, 0x930);
                tLocal = F(aseg, float, 0x74) * 0.5f;
            }
          }
        }
        break;
    }
    case 9: case 10: case 16: case 18: {
        char *lo = F(jmp, char *, 0);
        SetXfKind(lo, F(lo, void *, 0x58), 0x11);
        ClearVelocity(F(jmp, char *, 0));
        F(jmp, int, 0x28) = 0;
        F(jmp, JT *, 0)->Slot35(GetJmpLaunchVelocity(jmp, 4));
        F(jmp, int, 8) = 0;
        if (F(jmp, int, 0x1C) == 16)
            aseg = F(jmp, void *, 0x14C);
        else
            aseg = F(jmp, void *, 0x148);
        asegbl = 0;
        break;
    }
    case -1:
        if (F(jmp, int, 0x174) != 0) {
            SetStepGravityRatio__FP4STEPf(F(jmp, char *, 0), F(jmp, float, 0x168));
            func_00140C88(F(jmp, char *, 0), 0);
            F(jmp, int, 0x174) = 0;
        }
        F(jmp, int, 0xBC) = 0;
        F(jmp, int, 4) = -1;
        break;
    case 19: {
        char *lo = F(jmp, char *, 0);
        SetStepRadTarget(lo, F(lo, float, 0x1A8) - D_FLT_002BF780[F(jmp, int, 8)]);
        F(jmp, int, 0x28) = 0;
        aseg = F(jmp, void *, 0x178);
        func_00140C88(F(jmp, char *, 0), F(jmp, void *, 0x1BC));
        F(F(F(jmp, char *, 0x1BC), char *, 0x114), float, 4) = D_FLT_002BF798[0] * 0.5f + D_FLT_002BF798[1] * 0.5f;
        void *sma = F(F(jmp, char *, 0), void *, 0x1D28);
        if (sma != 0)
            SetSmaGoal__FP3SMA3OID(sma, 0x5F7);
        break;
    }
    case 20:
        flags = 9;
        F(jmp, int, 0x188) = 0;
        F(jmp, int, 0x194) = 0;
        F(jmp, int, 0x1A0) = 0;
        F(jmp, int, 0x1AC) = 0;
        F(jmp, float, 0x17C) = 1.0f;
        ReblendAsegbl(F(jmp, void *, 0x1B8));
        aseg = F(jmp, void *, 0x1B8);
        break;
    case 21: {
        float t = -1000.0f;
        float dt = -1.0f;
        origin.q = F(F(F(jmp, char *, 0), char *, 0x58), QW, 0x70);
        void *target_so = F(jmp, void *, 0x1D0);
        if (target_so != 0 && (FIsBasicDerivedFrom(target_so, 0x13) || FIsBasicDerivedFrom(F(jmp, void *, 0x1D0), 0xB))) {
            t = 0.0f;
            dt = 500.0f;
        }
        target.q = func_0019F3F8(F(jmp, char *, 0), jmp + 0x1D0, D_FLT_002BF7A0);
        dir.q = VectorSub(VectorFromQuad(target.q), origin.q);
        gravity.q = F(F(F(jmp, char *, 0), char *, 0xE8), QW, 0x80);
        float dtSolve = DtSolveJumpLaunch(dir.q, gravity.q, 1000.0f, t, 1.0f, dt);
        dt = dtSolve > D_FLT_002BF7A0 ? dtSolve : D_FLT_002BF7A0;
        JT *jt = F(jmp, JT *, 0);
        temp.q = VectorFromFloat(dt);
        QW dtq = temp.q;
        QW launch = ScaleByReciprocalX(dir.q, dtq);
        temp.q = VectorFromFloat(dt * -0.5f);
        velocity.q = ScaleAddX(launch, gravity.q, temp.q);
        jt->Slot35(velocity.q);
        landing.q = ScaleAddX(velocity.q, gravity.q, dtq);
        t = g_2dded0 + dt;
        temp.q = dtq;
        QW posLand = ConvertXfPos(0, F(F(F(jmp, char *, 0), char *, 0x58), void *, 0xA0), target.q);
        QW vecLand = ConvertXfVec(0, F(F(F(jmp, char *, 0), char *, 0x58), void *, 0xA0), landing.q);
        char *body = F(jmp, char *, 0);
        F(jmp, int, 0x1F0) = func_0012DE58(body, F(body, void *, 0x58), 5, posLand, vecLand, t);
        SetSoNoXpsAll(F(jmp, char *, 0), 1);
        ClearVelocity(F(jmp, char *, 0));
        SetStepRadTargetDir(F(jmp, char *, 0), dir.q);
        aseg = F(jmp, void *, 0x120);
        break;
    }
    case 22:
        aseg = F(jmp, void *, 0x1C8);
        flags = 9;
        break;
    }

    switch (F(jmp, int, 0x1C)) {
    case 0:
        F(jmp, int, 0x30) = 0;
        break;
    case 2:
        F(jmp, int, 0x30) = 0;
        break;
    case 18:
        RecalcSwOxfFilterForObject(B_003DD490, F(jmp, char *, 0));
        break;
    }

    if (F(jmp, int, 0x1C) != -1) {
        if (asegbl == 0 || F(asegbl, void *, 0x14) != aseg) {
            RetractSmaRef(F(jmp, char *, 0) + 0x1034);
            char *lo = F(jmp, char *, 0);
            ApplyAsegToHandle(aseg, lo, flags, lo + 0x1030, tLocal, rBlend);
        }
        F(jmp, JT *, 0)->Slot90();
    }
}
}
