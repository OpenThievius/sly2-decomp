// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "sly2.h"
#include "jt.h"
#include "vu0inline.h"

union VU_SCALE { QW q; VECTOR v; };
union VU_VECTOR { QW q; VECTOR v; };

struct CLOCK { float t; float dt; };
struct JOY { char pad0[0x1C]; float uStick; char pad20[0x30 - 0x20]; u32 grfbtn; };
struct XFL { char pad0[0xA0]; void *pxf; char padA4[4]; float tLand; char padAC[0xB8 - 0xAC]; float dz; };
struct ASEGA { char pad0[0x28]; u64 grfo; char pad30[0x17C - 0x30]; s32 kind; };
struct EDGEHOST { char pad0[0xEC]; void *poxa; };
struct EDGESO { void *pxf; EDGEHOST *phost; };
struct EDGEEND { EDGESO *pso; char pad4[0xC]; QW pos; char pad20[0x20]; };
struct EDGE { EDGEEND aend[2]; char pad80[0x9C - 0x80]; s32 field_0x9C; s32 field_0xA0; s32 field_0xA4; };
struct ACTVAL { char pad0[0x1C]; float tGoal; char pad20[0x10]; QW pos; };
struct LANDING { LO *plo; s32 field_0x4; s32 field_0x8; };

struct Jmp;

struct JMP {
    JT *pjt;
    s32 kind;
    s32 field_0x8;
    ASEGA *pasega;
    char pad10[0xC];
    s32 state;
    float tState;
    s32 field_0x24;
    s32 field_0x28;
    char pad2c[4];
    s32 fStarted;
    char pad34[0xC];
    s32 field_0x40;
    char pad44[0xC8 - 0x44];
    EDGESO *psoEdge;
    char padcc[4];
    QW posEdge;
    QW dirEdge;
    char padf0[0x10];
    s32 field_0x100;
    s32 field_0x104;
    char pad108[0x134 - 0x108];
    void *paseg;
    char pad138[0x1D0 - 0x138];
    LANDING landing;
    char pad1dc[0x1F0 - 0x1DC];
    ACTVAL *pactval;
};

#define JT_FIELD(pjt, type, offset) (*(type *)((char *)(pjt) + (offset)))

extern "C" {
extern CLOCK g_2dded0;
extern float D_002BF818;
extern float D_002BF81C;
extern float D_002BF82C;
extern float D_002BF830;
extern unsigned int D_002BF820[3];
extern QW g_2a2dd0;
extern JT *g_2e1e40;
extern char *g_2f7900;
QW PosLoWorld(void *);
void bevy_player_19c828(JMP *);
int GrfbtnVjoyPressedWithin(JOY *, int, float);
int FButtonPressedWithin(JOY *, int, float);
int FJtLandsWithin(JT *, float);
void ClearVjoyPresses(JOY *, int);
void SetJmpState(JMP *, int, int, int);
void JtbsChooseJtLanding(JMP *, LO *);
int FGadgetAcquired(int);
void SpendJtGadgetPower(JT *, int);
void SetJmpBodyState(JMP *, int, ASEGA *);
void StartJmpDirectionAseg(struct Jmp *);
void bevy_player_p14_jts8_enter(JMP *);
float TFindAsegLabel__FP4ASEG3OID(void *, int);
void CarryThrow_SetState(void *, int);
void StartAttach(void *, int, int, int);
EDGE *PxpFindJtBestEdge__FP2JTPiP6VECTOR(JMP *, int *, VECTOR *);
QW ConvertXfPos(void *, void *, QW);
int FJtStuck(JT *, void *, float);
void WarpJtToSafePoint(JT *, int);
QW PosSmooth(QW, QW, void *, int, float);
int FCheckJtEdgeGrab__FP2JTP2SOP6VECTOR3XPKPvT2(JMP *, EDGESO *, QW, int, int, QW *);
void SetStepRadTargetDir(JT *, QW);
void StartBinoc(void *, int, int, int);
int PmqFirstOxaContact(void *);
u32 GrfbtnJtGadget(JT *, int);
int FAsegaGone(void *);
int FIsBasicDerivedFrom(void *, int);
void ApplyAsegToHandle(void *, JT *, int, void *, float, float);
QW GetJmpLaunchVelocity(JMP *, int);
QW func_0019F3F8(JT *, LANDING *, float);
void SetActvalGoal(ACTVAL *, QW, QW);
int GetJtPower(JT *);
}

extern "C" void UpdateJmpBodyState(JMP *pjmp)
{
    VU_VECTOR posWorld;
    VU_VECTOR vel;
    VU_VECTOR posEdge;
    VU_SCALE scale;
    int iEdge;
    int fGrab = 0;
    int stateOld;
    s32 saved;

    posWorld.q = PosLoWorld(pjmp->pjt);
    vel.q = pjmp->pjt->GetVelocityVec();
    JOY *pjoy = JT_FIELD(pjmp->pjt, JOY *, 0x150);
    if (JT_FIELD(pjmp->pjt, char *, 0x208) && *(float *)(JT_FIELD(pjmp->pjt, char *, 0x208) + 0x88) > 0.7f) {
        fGrab = 1;
    }

    for (;;) {
        stateOld = pjmp->state;
        if (pjmp->pasega && ((int)(pjmp->pasega->grfo >> 60) & 1) == 0) {
            bevy_player_19c828(pjmp);
        }
        switch (pjmp->state) {
        case 9 ... 22:
            break;
        default:
            if (pjmp->field_0x28 && GrfbtnVjoyPressedWithin(pjoy, 0x40, 0.0f) && !FJtLandsWithin(pjmp->pjt, 0.075f)) {
                ClearVjoyPresses(pjoy, 0x40);
                SetJmpState(pjmp, 6, pjmp->field_0x8, 0);
            }
            if (GrfbtnVjoyPressedWithin(pjoy, 0x20, 0.0f)) {
                int state = pjmp->state;
                JtbsChooseJtLanding(pjmp, 0);
                if (pjmp->state != state) {
                    ClearVjoyPresses(pjoy, 0x20);
                }
            }
            if (GrfbtnVjoyPressedWithin(pjoy, 8, 0.0f) && pjmp->pjt == g_2e1e40 && FGadgetAcquired(0x1B) &&
                !FJtLandsWithin(pjmp->pjt, 0.3f)) {
                SpendJtGadgetPower(pjmp->pjt, 0x1B);
                ClearVjoyPresses(pjoy, 8);
                g_2e1e40->UseGadget(0x1B);
            }
            break;
        }

        switch (pjmp->state) {
        case 0:
            if (D_002BF818 < g_2dded0.t - pjmp->tState) {
                if (!(pjoy->grfbtn & 0x40) && pjmp->field_0x40 != 3) {
                    pjmp->field_0x24 = 1;
                }
                SetJmpBodyState(pjmp, 1, pjmp->pasega);
            } else if (!pjmp->fStarted && pjoy->uStick > 0.5f) {
                StartJmpDirectionAseg((Jmp *)pjmp);
            }
            break;
        case 2:
            if (D_002BF81C < g_2dded0.t - pjmp->tState) {
                SetJmpBodyState(pjmp, 3, pjmp->pasega);
            } else if (!pjmp->fStarted && pjoy->uStick > 0.5f) {
                StartJmpDirectionAseg((Jmp *)pjmp);
            }
            break;
        case 1:
        case 7:
            if (vel.v.z < 0.0f) {
                SetJmpBodyState(pjmp, 4, pjmp->pasega);
            }
            break;
        case 6:
            if (pjmp->pasega->kind == 3) {
                SetJmpBodyState(pjmp, 4, 0);
            } else if (JT_FIELD(pjmp->pjt, XFL *, 0x58)->tLand < g_2dded0.t) {
                bevy_player_p14_jts8_enter(pjmp);
            }
            break;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            if (JT_FIELD(pjmp->pjt, XFL *, 0x58)->tLand < g_2dded0.t) {
                bevy_player_p14_jts8_enter(pjmp);
            }
            break;
        case 18:
            if (JT_FIELD(pjmp->pjt, XFL *, 0x58)->tLand -
                        TFindAsegLabel__FP4ASEG3OID(*(void **)(g_2f7900 + 0x1974), 0x1C7) <=
                    g_2dded0.t &&
                *(s32 *)(g_2f7900 + 0x1914) != 3) {
                CarryThrow_SetState(g_2f7900 + 0x1910, 3);
            } else if (JT_FIELD(pjmp->pjt, XFL *, 0x58)->tLand < g_2dded0.t) {
                bevy_player_p14_jts8_enter(pjmp);
            }
            break;
        case 8:
            if (JT_FIELD(pjmp->pjt, XFL *, 0x58)->tLand < g_2dded0.t) {
                SetJmpBodyState(pjmp, 4, pjmp->pasega);
            }
            break;
        case 5:
            if (g_2dded0.t - pjmp->tState > 0.25f && fGrab) {
                pjmp->pjt->SetMode(0);
            } else if (FJtStuck(pjmp->pjt, (char *)pjmp->pjt + 0x131C, pjmp->tState)) {
                WarpJtToSafePoint(pjmp->pjt, 0);
            }
            break;
        case 3:
        case 4:
            if (fGrab) {
                if (pjmp->kind == 0xE) {
                    StartAttach((char *)pjmp->pjt + 0x4C0, 0xA, 0, 0);
                } else {
                    pjmp->pjt->SetMode(0);
                }
            } else {
                EDGE *pedge = PxpFindJtBestEdge__FP2JTPiP6VECTOR(pjmp, &iEdge, &posEdge.v);
                if (pedge) {
                    EDGEEND *pend = &pedge->aend[1 - iEdge];
                    EDGESO *pso = pend->pso;
                    pjmp->psoEdge = pso;
                    pjmp->posEdge = ConvertXfPos(0, pso->pxf, pend->pos);
                    pjmp->field_0x100 = pedge->field_0x9C;
                    pjmp->field_0x104 = iEdge == 0 ? pedge->field_0xA4 : pedge->field_0xA0;
                    pjmp->dirEdge = posEdge.q;
                    SetJmpBodyState(pjmp, 0x11, 0);
                } else if (FJtStuck(pjmp->pjt, (char *)pjmp->pjt + 0x131C, pjmp->tState)) {
                    WarpJtToSafePoint(pjmp->pjt, 0);
                }
            }
            break;
        case 17:
            if (g_2dded0.t - pjmp->tState > 0.25f && FButtonPressedWithin(pjoy, 0x40, 0.25f)) {
                SetJmpState(pjmp, 3, 0, 0);
            } else if (!pjmp->psoEdge->phost->poxa) {
                SetJmpBodyState(pjmp, 4, 0);
            } else {
                JT *pjtSmooth = pjmp->pjt;
                JT_FIELD(pjtSmooth, QW, 0x1010) =
                    PosSmooth(JT_FIELD(pjtSmooth, QW, 0x1010), g_2a2dd0, D_002BF820, 0, g_2dded0.dt);
                posEdge.q = ConvertXfPos(pjmp->psoEdge->pxf, 0, pjmp->posEdge);
                if (g_2dded0.t - pjmp->tState > 0.03f &&
                    !FCheckJtEdgeGrab__FP2JTP2SOP6VECTOR3XPKPvT2(pjmp, pjmp->psoEdge, posEdge.q, pjmp->field_0x100,
                                                                 pjmp->field_0x104, &pjmp->dirEdge)) {
                    SetJmpBodyState(pjmp, 4, 0);
                } else {
                    scale.q = VectorFromFloat(-1.0f);
                    SetStepRadTargetDir(pjmp->pjt, VectorScaleX(pjmp->dirEdge, scale.q));
                    if (GrfbtnVjoyPressedWithin(pjoy, 0x400, 0.15f) && pjmp->pjt->FCanUseGadget(3)) {
                        ClearVjoyPresses(pjoy, 0x400);
                        StartBinoc((char *)pjmp->pjt + 0xF00, 0, 0, 0);
                    }
                }
            }
            break;
        case 19:
        case 20:
            if (PmqFirstOxaContact(pjmp->pjt->poxa)) {
                SetJmpBodyState(pjmp, 4, 0);
            } else if (!(pjoy->grfbtn & (GrfbtnJtGadget(pjmp->pjt, 0x1B) | 8))) {
                SetJmpBodyState(pjmp, 4, 0);
            } else if (pjmp->state == 0x13) {
                void *pasega = JT_FIELD(pjmp->pjt, void *, 0x1030);
                if (!pasega || FAsegaGone(pasega)) {
                    SetJmpBodyState(pjmp, 0x14, 0);
                }
            }
            break;
        case 21: {
            float tGoal = pjmp->pactval->tGoal;
            if (tGoal < g_2dded0.t) {
                JT *pjtSly = 0;
                if (FIsBasicDerivedFrom(pjmp->pjt, 0x35)) {
                    pjtSly = pjmp->pjt;
                    saved = JT_FIELD(pjtSly, s32, 0x18F0);
                }
                posEdge.q = pjmp->pjt->GetVelocityVec();
                posEdge.v.x = posEdge.v.y = 0.0f;
                pjmp->pjt->Slot35(posEdge.q);
                SetJmpState(pjmp, 0xB, 0, 0);
                if (pjtSly) {
                    JT_FIELD(pjtSly, s32, 0x18F0) = saved;
                }
            } else if (pjmp->landing.field_0x4 && tGoal < g_2dded0.t + 0.25f &&
                       (FIsBasicDerivedFrom(pjmp->landing.plo, 0x13) || FIsBasicDerivedFrom(pjmp->landing.plo, 0xB) ||
                        FIsBasicDerivedFrom(pjmp->landing.plo, 0xD) || FIsBasicDerivedFrom(pjmp->landing.plo, 0x27) ||
                        FIsBasicDerivedFrom(pjmp->landing.plo, 0xC) || FIsBasicDerivedFrom(pjmp->landing.plo, 0x22) ||
                        FIsBasicDerivedFrom(pjmp->landing.plo, 0x26))) {
                SetJmpState(pjmp, 0xB, 0, 0);
                JtbsChooseJtLanding(pjmp, pjmp->landing.plo);
            } else if (pjmp->field_0x28 && JT_FIELD(pjmp->pjt, XFL *, 0x58)->dz < 0.0f) {
                ApplyAsegToHandle(pjmp->paseg, pjmp->pjt, 1, (char *)pjmp->pjt + 0x1030, 0.0f, 1.0f);
                pjmp->field_0x28 = 0;
                pjmp->pjt->Slot35(GetJmpLaunchVelocity(pjmp, 6));
            } else if (pjmp->landing.field_0x4 || pjmp->landing.field_0x8) {
                float dt = pjmp->pactval->tGoal - g_2dded0.t;
                QW pos = func_0019F3F8(pjmp->pjt, &pjmp->landing, dt < 0.7f ? dt : 0.7f);
                pos = ConvertXfPos(0, JT_FIELD(pjmp->pjt, XFL *, 0x58)->pxf, pos);
                SetActvalGoal(pjmp->pactval, pos, pjmp->pactval->pos);
            }
            break;
        }
        case 22:
            if (GetJtPower(pjmp->pjt) <= 0) {
                SetJmpBodyState(pjmp, 4, 0);
            } else if (D_002BF82C < g_2dded0.t - pjmp->tState && fGrab) {
                pjmp->pjt->SetMode(0);
            } else if (D_002BF82C < g_2dded0.t - pjmp->tState &&
                       !(pjoy->grfbtn & GrfbtnJtGadget(pjmp->pjt, 0xC))) {
                SetJmpBodyState(pjmp, 4, 0);
            } else if (D_002BF830 < g_2dded0.t - pjmp->tState) {
                SetJmpBodyState(pjmp, 4, 0);
            }
            break;
        }
        if (pjmp->state == stateOld || pjmp->state == -1) {
            break;
        }
    }
}
