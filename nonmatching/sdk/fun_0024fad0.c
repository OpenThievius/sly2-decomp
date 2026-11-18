#include "types.h"

/* source: retail's 0x184 (mode) and 0x188 (flag) fields, read from the asm */
struct CurveState {
    char pad0[0x184];
    s32 mode;
    s32 flag;
};

static inline s32 HalfRoundUp(s32 value)
{
    return (value > 0 ? value + 1 : value) >> 1;
}

static inline s32 ThirdRoundUp(s32 value)
{
    return (value * 3 + (value > 0 ? 1 : 0)) >> 1;
}

void func_0024FAD0(struct CurveState *state, s32 *out, s32 *src, s32 firstValue, s32 secondValue)
{
    if (state->mode == 3) {
        if (state->flag != 0) {
            out[0] = HalfRoundUp(firstValue) + src[0];
            out[1] = HalfRoundUp(secondValue) + src[1] - 1;
            out[2] = ThirdRoundUp(firstValue) + src[0];
            out[3] = ThirdRoundUp(secondValue) + src[1] + 1;
        } else {
            out[0] = ThirdRoundUp(firstValue) + src[0];
            out[1] = ThirdRoundUp(secondValue) + src[1] - 1;
            out[2] = HalfRoundUp(firstValue) + src[0];
            out[3] = HalfRoundUp(secondValue) + src[1] + 1;
        }
    } else {
        out[0] = HalfRoundUp(firstValue) + src[0];
        if (state->mode == 1)
            out[1] = HalfRoundUp(secondValue) + src[1] - 1;
        else
            out[1] = HalfRoundUp(secondValue) + src[1] + 1;
    }
}
