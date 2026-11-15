// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "jt.h"
#include "ps2inline.h"
#include "vu0inline.h"

struct CM;
struct JTX {
    char pad0[0x40];
    u32 grfFlags;
    char pad44[0x150 - 0x44];
    struct { char pad[0x1C]; float s; } *pjoy;
    char pad154[0x190 - 0x154];
    QW vecTarget;
    char pad1A0[0x1B0 - 0x1A0];
    char ab1B0[0x20C - 0x1B0];
    float tAttach;
    char pad210[0x230 - 0x210];
    QW posAttach;
    QW posPivot;
    char pad250[0x900 - 0x250];
    char carry[0x9BC - 0x900];
    int field_0x9BC;
    char pad9C0[0x1024 - 0x9C0];
    void *ptunnel;
    char pad1028[0x1030 - 0x1028];
    void *hAsega;
    void *hSma;
    int field_0x1038;
    char pad103C[0x1048 - 0x103C];
    float sOffset;
    char pad104C[0x1060 - 0x104C];
    QW posOffset;
    char pad1070[0x10C0 - 0x1070];
    void *pcplcy;
    char pad10C4[0x130C - 0x10C4];
    int field_0x130C;
    char pad1310[0x1318 - 0x1310];
    int sidDefault;
    char pad131C[0x18D8 - 0x131C];
    int field_0x18D8;
    char pad18DC[0x19A0 - 0x18DC];
    LO *ploA;
    LO *ploB;
    char pad19A8[0x1BCC - 0x19A8];
    int field_0x1BCC;
    char pad1BD0[0x1C30 - 0x1BD0];
    char runblend[4];
    void *asegRun;
    char pad1C38[0x2048 - 0x1C38];
    void *pamb;
};
struct TUNNEL {
    char pad0[0x10C];
    LO *plo;
    char pad110[0x114 - 0x110];
    float *pdir;
    char pad118[0x12C - 0x118];
    int fActive;
    char pad130[0x150 - 0x130];
    QW pos;
    float rad;
};
struct ATTACH {
    JTX *pjt;
    int pad4;
    int kind;
    int substate;
    float tSubstate;
    LO *plo;
    LO **pplo;
    float u;
    float s;
    int fForward;
    int field_0x28;
    int field_0x2C;
    int pad30;
    int field_0x34;
    char pad38[0x68 - 0x38];
    TUNNEL *ptunnel;
    char pad6C[0x170 - 0x6C];
    void *asegHang;
    void *asegPipe;
    void *asegLedge;
    void *asegLedgeUp;
    char runblendA[4];
    void *asegRunA;
    char pad188[0x230 - 0x188];
    void *asegRope;
    void *asegRopeHang;
    void *asegPole;
    char pad23C[0x240 - 0x23C];
    char runblendB[4];
    void *asegRunB;
    char pad248[0x314 - 0x248];
    void *asegSwing;
    float field_0x318;
    float field_0x31C;
    void *asegRail;
    void *asegVault;
    void *asegVaultEnd;
    void *asegZip;
    char pad330[0x430 - 0x330];
    void *asegDrop;
    char pad434[0x440 - 0x434];
    char carry[0x470 - 0x440];
    struct { char pad[0x74]; float dt; } *pcarryAnim;
    char pad474[0x4C4 - 0x474];
    LO *ploCarry;
    char pad4C8[0x4F0 - 0x4C8];
    void *asegLadderUp;
    void *asegLadderDown;
    void *asegSpecial;
    int field_0x4FC;
    int field_0x500;
    char pad504[0x50C - 0x504];
    void *asegPeek;
    void *asegHangIdle;
    void *asegPipeIdle;
};
union VU_SCALE { QW q; VECTOR v; };
struct MATROWS3 { QW row[3]; };
struct PLAYERX { char pad[0x1AF0]; void *asegOverride; };

extern "C" {
int FIsBasicDerivedFrom(LO *plo, int cid);
QW PosLoWorld(void *plo);
void FindCrvClosestPointAll(LO *pcrv, QW pos, int a, void *pposClosest, void *pnormal, float *pu, float *ps);
void SetHbskHbsks(LO *plo, int hbsk);
void SubscribeLoObject(LO *plo, JTX *pjt);
void UnsubscribeLoObject(LO *plo, JTX *pjt);
void func_00204F78(JTX *pjt, LO *plo, int fSubscribe);
void EvaluateCrvFromU(LO *pcrv, float u, QW *ppos, VECTOR *pdpos);
MATRIX4 *PmatLoWorld(void *plo);
void *NewEmitter(int cb);
void SetEmitterUnpositioned(void *pemitter, int f);
void VirtualRefPtr_Assign(void **pp, void *pv);
void func_002046F0(JTX *pjt, LO *plo);
void FixStepAngularVelocity__FP4STEP(JTX *pjt);
void SetStepRadTargetDir(JTX *pjt, QW dir);
void SetCmPolicy__FP2CM3CPPP5CPLCYP2SOPv(CM *pcm, int cpp, void *pcplcy, JTX *pso, void *pv);
void RevokeCmPolicy__FP2CMi3CPPP5CPLCYP2SOPv(CM *pcm, int grf, int cpp, void *pcplcy, void *pso, void *pv);
void Carry_SetState(void *pcarry, int state);
void Carry_Detach(void *pcarry);
void StopAmb(void *pamb, float dt);
void func_00140C88(JTX *pjt, void *ptunnel);
void ResetJtDynamicTunnel__FP2JT(ATTACH *pattach);
QW ConvertAloPos(int grf, void *palo, QW pos);
void ResetRunBlendFootsteps(void *prunblend);
void RetractAsegaHandle(void *phandle);
void RetractSmaRef(void *phandle);
void ApplyAsegToHandle(void *paseg, JTX *pjt, int grfapl, void *phandle, float t, float svt);
void func_001F1448(void *paseg, JTX *pjt, int a, int grfapl, void *phandle);
void SetJtLookats(JTX *pjt, int grf);
void SetJtJtcs(JTX *pjt, int jtcs);
extern float g_2dded0;
extern JTX *g_2e1e40;
extern const QW g_2a2da0;
extern const QW g_2a2dc0;
extern const QW g_2a2dd0;
extern float D_FLT_002BF63C;
extern float D_FLT_002BF640;
extern const QW D_002BF650;
extern CM B_002DDF40;
extern PLAYERX *g_2f7900;
}

static inline JT *Pjt(JTX *pjt)
{
    return (JT *)pjt;
}

static inline void SetGrfFlag(u32 *pgrf, u32 grf)
{
    u32 grfCur = *pgrf;
    if ((grfCur ^ 1) & 1)
        *(u32 *)grfCur |= grf;
    else
        *pgrf = grfCur | grf;
}

extern "C" void SetAttachSubstate(ATTACH *pattach, int substate)
{
    if (substate == pattach->substate)
        return;

    switch (pattach->substate) {
    case 1:
        pattach->pjt->field_0x1038 = -1;
        break;
    case -1: {
        if (pattach->plo != 0 && FIsBasicDerivedFrom(pattach->plo, 0xA) != 0) {
            LO *pcrv = pattach->plo;
            FindCrvClosestPointAll(pcrv, PosLoWorld(pattach->pjt), 0, 0, 0, &pattach->u, &pattach->s);
        }
        switch (pattach->kind) {
        case 1: {
            LO *plo = pattach->plo;
            *(JTX **)((char *)plo + 0x190) = pattach->pjt;
            SetHbskHbsks(plo, 2);
            if (pattach->pjt == g_2e1e40)
                pattach->pjt->ploA->Remove();
            break;
        }
        case 4: {
            LO *plo = pattach->plo;
            plo->HandleSpliceEvent(5, 0, 0, 0, 0);
            SubscribeLoObject(plo, pattach->pjt);
            func_00204F78(pattach->pjt, plo, 1);
            pattach->pjt->posAttach = PosLoWorld(plo);
            break;
        }
        case 3: {
            LO *plo = pattach->plo;
            plo->HandleSpliceEvent(5, 0, 0, 0, 0);
            SubscribeLoObject(plo, pattach->pjt);
            func_00204F78(pattach->pjt, plo, 1);
            pattach->field_0x28 = -1;
            VECTOR dpos;
            VECTOR posCrv;
            EvaluateCrvFromU(plo, pattach->u, &pattach->pjt->posAttach, &posCrv);
            dpos.z = 0.0f;
            QW root = SqrtX(SquaredLength(*(QW *)&dpos));
            QW dirNorm;
            if (LaneX(root) < 0.0001f)
                dirNorm = g_2a2da0;
            else
                dirNorm = ScaleByReciprocalX(*(QW *)&dpos, root);
            *(QW *)&dpos = dirNorm;
            QW dir = *(QW *)&dpos;
            MATRIX4 *pmat = PmatLoWorld(pattach->pjt);
            pattach->fForward = LaneX(DotProduct(dir, pmat->row[0])) < D_FLT_002BF63C;
            break;
        }
        case 2: {
            void *pemitter = NewEmitter(0x5C);
            SetEmitterUnpositioned(pemitter, 0);
            VirtualRefPtr_Assign(&g_2e1e40->pamb, pemitter);
            break;
        }
        case 0xB:
            if (pattach->plo != 0)
                SubscribeLoObject(pattach->plo, pattach->pjt);
            break;
        case 0xC:
            if (pattach->plo != 0)
                func_002046F0(pattach->pjt, pattach->plo);
            FixStepAngularVelocity__FP4STEP(pattach->pjt);
            break;
        }
        pattach->field_0x2C = -1;
        pattach->pjt->tAttach = g_2dded0;
        break;
    }
    case 7:
        switch (substate) {
        case 9:
        case 10: {
            LO *plo = pattach->plo;
            if (*(LO **)((char *)plo + 0x15C) != 0) {
                QW pos = PosLoWorld(*(LO **)((char *)plo + 0x15C));
                JTX *pjt = pattach->pjt;
                Pjt(pjt)->TranslateToPos(VectorSub(pos, pjt->posPivot));
                pjt = pattach->pjt;
                VU_SCALE scale;
                scale.q = VectorFromWord(*(u32 *)&pjt->sOffset);
                pjt->posOffset = ScaleAddX(pos, g_2a2dc0, scale.q);
                SetStepRadTargetDir(pattach->pjt, PmatLoWorld(*(LO **)((char *)plo + 0x15C))->row[0]);
                Pjt(pattach->pjt)->Slot30(pattach->pjt->ab1B0);
                Pjt(pattach->pjt)->Slot35(g_2a2dd0);
                Pjt(pattach->pjt)->Slot36(g_2a2dd0);
            }
            SetCmPolicy__FP2CM3CPPP5CPLCYP2SOPv(&B_002DDF40, 0xA, (char *)&B_002DDF40 + 0x4C0, pattach->pjt, pattach->pjt->pcplcy);
            break;
        }
        }
        break;
    case 9:
    case 10:
        switch (substate) {
        case 9:
        case 10:
            break;
        default:
            RevokeCmPolicy__FP2CMi3CPPP5CPLCYP2SOPv(&B_002DDF40, 2, 0xA, (char *)&B_002DDF40 + 0x4C0, 0, 0);
            break;
        }
        break;
    }

    void *paseg = 0;
    void *pasegSecondary = 0;
    int grfapl = 1;
    float t = 0.0f;
    float svt = 1.0f;
    int grfLookats = 0;
    switch (substate) {
    case -1: {
        pattach->field_0x500 = 0;
        switch (pattach->kind) {
        case 1:
            SetHbskHbsks(pattach->plo, 0);
            if (pattach->pjt == g_2e1e40)
                pattach->pjt->ploA->Add();
            break;
        case 3:
        case 4: {
            LO *plo = pattach->plo;
            plo->HandleSpliceEvent(6, 0, 0, 0, 0);
            UnsubscribeLoObject(plo, pattach->pjt);
            func_00204F78(pattach->pjt, plo, 0);
            break;
        }
        case 6:
            if (pattach->pjt->field_0x18D8 == 0)
                SetJtJtcs(pattach->pjt, -1);
            break;
        case 0xB:
            if (pattach->plo != 0)
                UnsubscribeLoObject(pattach->plo, pattach->pjt);
            pattach->pjt->field_0x130C = 0;
            pattach->pjt->field_0x9BC = -1;
            break;
        case 5:
        case 9:
            Carry_SetState(pattach->carry, -1);
            break;
        case 0xC:
            pattach->pjt->sidDefault = -1;
            Carry_Detach(pattach->pjt->carry);
            if (pattach->pjt == g_2e1e40)
                pattach->pjt->field_0x1BCC = 0;
            break;
        case 2:
            if (g_2e1e40->pamb != 0) {
                StopAmb(g_2e1e40->pamb, 0.0f);
                VirtualRefPtr_Assign(&g_2e1e40->pamb, 0);
            }
            break;
        }
        void *ptunnel = pattach->pjt->ptunnel;
        if (ptunnel != 0) {
            if (ptunnel == pattach->ptunnel)
                func_00140C88(pattach->pjt, 0);
            else if (ptunnel == *pattach->pplo)
                func_00140C88(pattach->pjt, 0);
        }
        pattach->pjt->field_0x1038 = -1;
        pattach->u = 0.0f;
        pattach->field_0x4FC = -1;
        pattach->kind = -1;
        pattach->substate = -1;
        pattach->plo = 0;
        pattach->pplo = 0;
        pattach->s = 0.0f;
        pattach->field_0x34 = 0;
        break;
    }
    case 0:
    case 5:
        switch (pattach->kind) {
        case 0xD:
            if (substate != 0)
                paseg = pattach->asegPipe;
            else
                paseg = pattach->asegHangIdle;
            grfapl = 9;
            break;
        case 0:
            paseg = pattach->asegPipe;
            grfapl = 9;
            break;
        case 2:
            paseg = pattach->asegPipeIdle;
            grfapl = 9;
            break;
        case 1:
            pasegSecondary = pattach->asegRope;
            grfapl = 1;
            break;
        case 4:
            paseg = pattach->asegRopeHang;
            grfapl = 9;
            grfLookats = 7;
            break;
        case 3:
            if (*(int *)((char *)pattach->plo + 0x1BC) != 0 && pattach->asegSwing != 0) {
                paseg = pattach->asegSwing;
                pattach->field_0x318 = 0.0f;
                pattach->field_0x31C = 0.0f;
            } else {
                paseg = pattach->asegPole;
            }
            grfapl = 9;
            grfLookats = 0x1F;
            break;
        case 6:
        case 7:
            paseg = pattach->asegRail;
            grfapl = 9;
            break;
        case 5:
        case 9:
            pattach->ploCarry = pattach->plo;
            svt = 0.0f;
            Carry_SetState(pattach->carry, 0);
            paseg = pattach->pcarryAnim;
            t = pattach->pcarryAnim->dt * 0.5f;
            break;
        case 0xA:
            if (D_FLT_002BF640 <= pattach->pjt->pjoy->s)
                paseg = pattach->asegLadderUp;
            else
                paseg = pattach->asegLadderDown;
            break;
        case 0xB:
            if (pattach->field_0x4FC != 0x15) {
                paseg = pattach->asegSpecial;
            } else {
                paseg = g_2f7900->asegOverride;
                if (paseg == 0)
                    paseg = pattach->asegSpecial;
            }
            break;
        case 0xC:
            paseg = pattach->asegPeek;
            break;
        }
        pattach->pjt->vecTarget = g_2a2dd0;
        break;
    case 1:
        if (pattach->kind == 0) {
            paseg = pattach->asegHang;
            if (pattach->pjt->ptunnel == 0) {
                if (FIsBasicDerivedFrom(pattach->plo, 0xC) != 0) {
                    LO *plo = pattach->plo;
                    void *ptunnel = *(void **)((char *)plo + 0x190);
                    if (ptunnel != 0) {
                        func_00140C88(pattach->pjt, ptunnel);
                    } else {
                        ResetJtDynamicTunnel__FP2JT(pattach);
                        pattach->ptunnel->plo = plo;
                        func_00140C88(pattach->pjt, pattach->ptunnel);
                    }
                } else if (FIsBasicDerivedFrom(pattach->plo, 0x22) != 0) {
                    LO *plo = pattach->plo;
                    void *ptunnel = *(void **)((char *)plo + 0xE0);
                    if (ptunnel != 0) {
                        func_00140C88(pattach->pjt, ptunnel);
                    } else {
                        ResetJtDynamicTunnel__FP2JT(pattach);
                        pattach->ptunnel->fActive = 1;
                        TUNNEL *ptun = pattach->ptunnel;
                        ptun->pos = ConvertAloPos(0, pattach->ptunnel, PosLoWorld(plo));
                        pattach->ptunnel->rad = *(float *)((char *)plo + 0x10C);
                        func_00140C88(pattach->pjt, pattach->ptunnel);
                    }
                } else if (FIsBasicDerivedFrom(pattach->plo, 0x26) != 0) {
                    LO *plo = pattach->plo;
                    void *ptunnel = *(void **)((char *)plo + 0xE0);
                    if (ptunnel != 0) {
                        func_00140C88(pattach->pjt, ptunnel);
                    } else {
                        ResetJtDynamicTunnel__FP2JT(pattach);
                        MATRIX4 *pmat = PmatLoWorld(plo);
                        QW dir = TransformVector(D_002BF650, pmat->row[0], pmat->row[1], pmat->row[2]);
                        pattach->ptunnel->pdir[4] = LaneX(dir);
                        pattach->ptunnel->pdir[8] = LaneYInGeneralRegister(dir);
                        pattach->ptunnel->pdir[12] = LaneZInGeneralRegister(dir);
                        func_00140C88(pattach->pjt, pattach->ptunnel);
                    }
                }
            }
            grfapl = 9;
        } else if (pattach->kind == 0xD) {
            paseg = pattach->asegHang;
            grfapl = 9;
        } else {
            grfapl = 9;
        }
        break;
    case 4:
        switch (pattach->kind) {
        case 3:
            paseg = pattach->asegRunB;
            ResetRunBlendFootsteps(pattach->runblendB);
            break;
        case 1:
            paseg = pattach->asegRunA;
            ResetRunBlendFootsteps(pattach->runblendA);
            break;
        case 2:
            paseg = pattach->pjt->asegRun;
            ResetRunBlendFootsteps(pattach->pjt->runblend);
            break;
        }
        grfapl = 9;
        break;
    case 3:
        paseg = pattach->asegLedge;
        pattach->pjt->vecTarget = g_2a2dd0;
        break;
    case 2:
        paseg = pattach->asegLedgeUp;
        pattach->pjt->vecTarget = g_2a2dd0;
        break;
    case 7: {
        LO *plo = pattach->plo;
        paseg = pattach->asegVault;
        if (*(LO **)((char *)plo + 0x15C) != 0) {
            MATROWS3 mat = *(MATROWS3 *)PmatLoWorld(*(LO **)((char *)plo + 0x15C));
            SetStepRadTargetDir(pattach->pjt, mat.row[0]);
        }
        pattach->pjt->vecTarget = g_2a2dd0;
        plo->HandleSpliceEvent(5, 0, 0, 0, 0);
        break;
    }
    case 8:
        paseg = pattach->asegVaultEnd;
        pattach->pjt->vecTarget = g_2a2dd0;
        pattach->plo->HandleSpliceEvent(6, 0, 0, 0, 0);
        break;
    case 9:
        pasegSecondary = pattach->asegZip;
        if (pattach->substate == 7) {
            SetGrfFlag(&pattach->pjt->grfFlags, 0x10);
            if (pattach->pjt == g_2e1e40) {
                SetGrfFlag((u32 *)((char *)pattach->pjt->ploA + 0x40), 0x10);
                SetGrfFlag((u32 *)((char *)g_2e1e40->ploB + 0x40), 0x10);
            }
        }
        pattach->pjt->vecTarget = g_2a2dd0;
        break;
    case 10:
        paseg = pattach->asegDrop;
        pattach->pjt->field_0x1038 = -1;
        grfapl = 9;
        pattach->pjt->vecTarget = g_2a2dd0;
        break;
    }
    pattach->substate = substate;
    pattach->tSubstate = g_2dded0;
    if (substate != -1) {
        RetractAsegaHandle(&pattach->pjt->hAsega);
        RetractSmaRef(&pattach->pjt->hSma);
        ApplyAsegToHandle(paseg, pattach->pjt, grfapl, &pattach->pjt->hAsega, t, svt);
        func_001F1448(pasegSecondary, pattach->pjt, -1, grfapl, &pattach->pjt->hSma);
        Pjt(pattach->pjt)->Slot90();
        if (FIsBasicDerivedFrom((LO *)pattach->pjt, 0x35) != 0)
            SetJtLookats(pattach->pjt, grfLookats);
    }
}
