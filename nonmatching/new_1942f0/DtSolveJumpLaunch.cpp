// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "ps2inline.h"
#include "vu0inline.h"

extern "C" int CSolveQuadratic(float, float, float, float *);

static inline float Sqrt(float x) { float r; asm volatile("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }

float DtSolveJumpLaunch(QW velocity, QW gravity, float lowX, float highX, float lowY, float highY)
{
    float roots[4];
    float roots2[4];
    float half = LaneZInGeneralRegister(gravity) * 0.5f;
    float z = LaneZInGeneralRegister(velocity);
    float best = 0.0f;
    int count = CSolveQuadratic(-half, -lowX, z, roots);
    if (count > 0) {
        float root = roots[count - 1];
        best = best > root ? best : root;
    }
    count = CSolveQuadratic(half, -highX, z, roots2);
    if (count > 0) {
        float root = roots2[count - 1];
        best = best > root ? best : root;
    }
    float speed = LaneX(SqrtX(SquaredLengthXy(velocity)));
    float time = (lowY * speed - z) / -half;
    if (0.0f < time) {
        float root = Sqrt(time);
        best = best > root ? best : root;
    }
    time = (highY * speed - z) / half;
    if (0.0f < time) {
        float root = Sqrt(time);
        best = best > root ? best : root;
    }
    return best;
}
