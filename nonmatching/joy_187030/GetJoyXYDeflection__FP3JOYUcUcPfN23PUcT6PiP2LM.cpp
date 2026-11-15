// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"

struct JOY { char pad0[0x1018]; float hold; };
struct LM { float lo; float hi; };

extern float D_FLT_002BE950[8];

static inline float Sqrt(float x) { float r; asm volatile("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }

extern "C" void GetJoyXYDeflection__FP3JOYUcUcPfN23PUcT6PiP2LM(JOY *pjoy, u8 x, u8 y, float *pdx, float *pdy, float *pmagnitude, u8 *plastX, u8 *plastY, s32 *pactive, LM *plm)
{
    float fx, fy;
    s32 active = *pactive;
    if (active == 0) {
        if (pjoy->hold != 0.0f) {
            if (x != *plastX || y != *plastY || x < 0x60 || x > 0xA0 || y < 0x60 || y > 0xA0)
                active = 1;
        }
        *pactive = active;
    }
    if (active != 0) {
        fx = (float)x * 2.0f * 0.0039215689f + -1.0f;
        fy = 1.0f - (float)y * 2.0f * 0.0039215689f;
    } else {
        fy = 0.0f;
        fx = fy;
    }
    {
        float best = 0.0f;
        for (u32 index = 0; index < 4; index++) {
            float dot = fx * D_FLT_002BE950[index * 2] + fy * D_FLT_002BE950[index * 2 + 1];
            float limit;
            if (dot >= 0.0f) {
                if (plm[index].hi < dot)
                    plm[index].hi = dot;
                limit = plm[index].hi;
            } else {
                if (dot < plm[index].lo)
                    plm[index].lo = dot;
                limit = plm[index].lo;
            }
            float ratio = dot / limit;
            if (best < ratio)
                best = ratio;
        }
        float scaled = (best - 0.35f) * 2.0f;
        float clamped;
        if (scaled < 0.0f)
            clamped = 0.0f;
        else if (scaled > 1.0f)
            clamped = 1.0f;
        else
            clamped = scaled;
        *pmagnitude = clamped;
        float length = Sqrt(fx * fx + fy * fy);
        if (length > 0.0001f) {
            *pdx = clamped * fx / length;
            *pdy = clamped * fy / length;
        } else {
            *pdy = 0.0f;
            *pdx = 0.0f;
        }
        *plastX = x;
        *plastY = y;
        return;
    }
}
