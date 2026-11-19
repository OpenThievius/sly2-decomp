// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "sw.h"
#include "ps2inline.h"
#include "vu0inline.h"

union VU_VECTOR { QW q; VECTOR v; };
struct LSG {
    VU_VECTOR apos[2];
    VU_VECTOR anormal[2];
    float as[2];
    int unk48;
    int aiface[2];
    void *pedge;
    char pad58[0x60 - 0x58];
};
struct SAFEPOINT { void *pbasic; int field4; int field8; int fieldC; QW pos; };
struct SAFEPOINTLIST { void *pjt; };
struct LOPOS { char pad[0x218]; QW *ppos; };
struct ALO;
extern "C" {
void CStackFrame_Construct(void *);
void CStackFrame_Destructor(void *, int);
void IntersectSwBoundingSphere(SW *, QW, int (*)(void *, ALO *), void *, int *, float, ALO ***);
void *PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG(int, QW, QW, int, ALO **, LSG *);
QW func_0019F3F8(void *, SAFEPOINT *, float);
int FFilterOxa(void *, ALO *);
extern SW B_003DD490;
extern float g_2bf944;
extern QW D_002BF950[8];
extern float g_2bf9d0[3];
extern float g_2bf9e0[2];
}

static inline float GMax(float a, float b) { return a >? b; }

static inline float GClamp(float g, float gMin, float gMax)
{
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}

extern "C" float ScoreSafePoint(SAFEPOINTLIST *plist, SAFEPOINT *ppoint, int cplo, LOPOS **aplo)
{
    char frame[0x10];
    VU_VECTOR start;
    VU_VECTOR end;
    LSG lsg;
    int calo;
    ALO **apalo;
    float score = 0.0f;
    QW pos;
    pos = func_0019F3F8(plist->pjt, ppoint, score);
    if (ppoint->field8 != 0) {
        CStackFrame_Construct(frame);
        IntersectSwBoundingSphere(&B_003DD490, pos, FFilterOxa, *(void **)((char *)plist->pjt + 0xEC), &calo, g_2bf944, &apalo);
        start.v = *(VECTOR *)&pos;
        end.v = *(VECTOR *)&pos;
        start.v.z += 125.0f;
        end.v.z -= 175.0f;
        if (PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG(0, start.q, end.q, calo, apalo, &lsg) == 0 || lsg.as[0] == 0.0f ||
            lsg.anormal[0].v.z < 0.7f) {
            score = GMax(2000.0f, score);
        } else {
            pos = lsg.apos[0].q;
        }
        end.v = *(VECTOR *)&pos;
        start.v = *(VECTOR *)&pos;
        start.v.z += 180.0f;
        end.v.z += 5.0f;
        if (PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG(0, start.q, end.q, calo, apalo, &lsg) != 0) {
            score = GMax(2000.0f, score);
        }
        for (unsigned int i = 0; i < 8; i++) {
            start.q = end.q = VectorAdd(pos, D_002BF950[i]);
            start.v.z += 50.0f;
            end.v.z -= 30.0f;
            if (PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG(0, start.q, end.q, calo, apalo, &lsg) == 0) {
                score = GMax(1500.0f, score);
                break;
            }
        }
        CStackFrame_Destructor(frame, 2);
    }
    for (int i = 0; i < cplo; i++) {
        if (aplo[i] != plist->pjt) {
            float distance = LaneX(GeneralFromVector(SqrtX(SquaredLength(VectorSub(*aplo[i]->ppos, pos)))));
            float value = g_2bf9d0[0] + distance * (g_2bf9d0[1] + distance * g_2bf9d0[2]);
            value = GClamp(value, g_2bf9e0[0], g_2bf9e0[1]);
            score = GMax(value, score);
        }
    }
    return score;
}
