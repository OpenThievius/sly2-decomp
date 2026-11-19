#include "sly2.h"
struct V3_12C140 { float x; float y; float z; };
struct Acr { int pad0; int ckey; float *at; float *apg[3]; float pad[2]; float def[4]; };
struct STATE_12C140 {
    char pad0[0x80]; float t0; float t1; float *pcur; float *pnext; char pad90[0x9A - 0x90]; short flag;
    char pad9c[0xC0 - 0x9C]; float a[4]; float q0[4]; float b[4]; float q1[4];
};
extern "C" {
int func_0012C0E0(Acr *acr, float t);
int FFloatsNear__Ffff(float, float, float);
}
extern QW g_2a2dd0;
#include "ps2inline.h"
static inline int Near(float a, float b) { return FFloatsNear__Ffff(a, b, 0.0001f); }
static inline int Near3(QW p, QW q)
{
    return Near(LaneX(p), LaneX(q)) && Near(LaneYInGeneralRegister(p), LaneYInGeneralRegister(q)) &&
           Near(LaneZInGeneralRegister(p), LaneZInGeneralRegister(q));
}
extern "C" void bevy_anim_keys_axis_segment(Acr *acr, STATE_12C140 *state)
{
    int ikey;
    if (acr->ckey != 0) {
        ikey = func_0012C0E0(acr, *state->pcur);
        state->t0 = acr->at[ikey - 1];
        state->t1 = acr->at[ikey];
    } else {
        state->pcur = &state->t0;
        state->t1 = 1.0f;
        state->pnext = &state->t1;
        state->t0 = 0.0f;
    }
    int o = ikey * 12;
    int o1 = o - 12;
    for (unsigned int i = 0; i < 3; i++) {
        float *apg = acr->apg[i];
        if (apg) {
            float *prev = (float *)((char *)apg + o1);
            float *key = (float *)((char *)apg + o);
            state->a[i] = prev[0];
            state->q0[i] = prev[2];
            state->b[i] = key[0];
            state->q1[i] = key[1];
        } else {
            state->a[i] = acr->def[i];
            state->q0[i] = 0.0f;
            state->b[i] = acr->def[i];
            state->q1[i] = 0.0f;
        }
    }
    int ok = 0;
    int same = Near3(*(QW *)state->a, *(QW *)state->b);
    if (same) {
        int second = Near3(g_2a2dd0, *(QW *)state->q0);
        if (second) {
            int third = Near3(g_2a2dd0, *(QW *)state->q1);
            ok = third;
        }
    }
    state->flag = ok ? 2 : 1;
}
