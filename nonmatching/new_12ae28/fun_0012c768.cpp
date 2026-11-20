#include "sly2.h"
struct KEYS_12C768 { int pad0; int count; float *times; float *axes[3]; int pad18[2]; float defaults[3]; };
struct STATE_12C768 {
    char pad0[0x80];
    float prevTime;
    float nextTime;
    float *currentPtr;
    float *nextPtr;
    char pad90[0xA];
    short flag;
    char pad9c[0x24];
    float vecA[4];
    float vecB[4];
    float vecC[4];
    float vecD[4];
};
extern "C" {
int FFloatsNear__Ffff(float, float, float);
int func_0012C708(KEYS_12C768 *, float);
}
extern QW g_2a2dd0;
#include "ps2inline.h"
static inline int Near(float a, float b) { return FFloatsNear__Ffff(a, b, 0.0001f); }
static inline int Near3(QW p, QW q)
{
    return Near(LaneX(p), LaneX(q)) && Near(LaneYInGeneralRegister(p), LaneYInGeneralRegister(q)) &&
           Near(LaneZInGeneralRegister(p), LaneZInGeneralRegister(q));
}
extern "C" void func_0012C768(KEYS_12C768 *keys, STATE_12C768 *state) {
    int index;
    if (keys->count != 0) {
        index = func_0012C708(keys, *state->currentPtr);
        state->prevTime = keys->times[index - 1];
        state->nextTime = keys->times[index];
    } else {
        state->currentPtr = &state->prevTime;
        state->nextTime = 1.0f;
        state->nextPtr = &state->nextTime;
        state->prevTime = 0;
    }
    float *defaultPtr = keys->defaults;
    unsigned int step = 0;
    int offset = index * 8;
    float **axisPtr = keys->axes;
    int previousOffset = offset - 8;
    float *outD = state->vecD;
    float *outC = state->vecC;
    float *outB = state->vecB;
    float *outA = state->vecA;
    do {
        char *base = (char *)*axisPtr;
        if (base != 0) {
            char *previous = base + previousOffset;
            char *current = base + offset;
            *outA = *(float *)previous;
            *outB = *(float *)(previous + 4);
            *outC = *(float *)current;
            *outD = *(float *)(current + 4);
        } else {
            *outA = *defaultPtr;
            *(int *)outB = 0;
            *outC = *defaultPtr;
            *(int *)outD = 0;
        }
        step++;
        outD++;
        outC++;
        outB++;
        outA++;
        defaultPtr++;
        axisPtr++;
    } while (step < 3U);
    int ok = 0;
    if (Near3(*(QW *)state->vecA, *(QW *)state->vecC)) {
        if (Near3(g_2a2dd0, *(QW *)state->vecB)) {
            ok = Near3(g_2a2dd0, *(QW *)state->vecD);
        }
    }
    state->flag = ok ? 2 : 1;
}
