#include "sly2.h"
#include "acr.h"
/* one key of an axis array, 12 bytes: the value and the two tangents the segment loader copies */
struct KEYAXIS { float value; float tanIn; float tanOut; };
struct STATE_12C140 {
    u8 unknown_0x0[0x80]; float t0; float t1; float *pcur; float *pnext; u8 unknown_0x90[0x9A - 0x90]; short flag;
    u8 unknown_0x9C[0xC0 - 0x9C]; float a[4]; float q0[4]; float b[4]; float q1[4];
};
extern "C" {
int func_0012C0E0(ACRAXIS *acr, float t);
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
extern "C" void bevy_anim_keys_axis_segment(ACRAXIS *acr, STATE_12C140 *state)
{
    int ikey;
    if (acr->ckey != 0) {
        ikey = func_0012C0E0(acr, *state->pcur);
        state->t0 = acr->atime[ikey - 1];
        state->t1 = acr->atime[ikey];
    } else {
        state->pcur = &state->t0;
        state->t1 = 1.0f;
        state->pnext = &state->t1;
        state->t0 = 0.0f;
    }
    for (unsigned int i = 0; i < 3; i++) {
        KEYAXIS *akey = (KEYAXIS *)acr->aaxis[i];
        if (akey) {
            KEYAXIS *prev = &akey[ikey - 1];
            KEYAXIS *key = &akey[ikey];
            state->a[i] = prev->value;
            state->q0[i] = prev->tanOut;
            state->b[i] = key->value;
            state->q1[i] = key->tanIn;
        } else {
            state->a[i] = acr->adefault[i];
            state->q0[i] = 0.0f;
            state->b[i] = acr->adefault[i];
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
