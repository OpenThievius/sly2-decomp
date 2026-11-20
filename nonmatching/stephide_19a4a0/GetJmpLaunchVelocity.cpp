// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "jt.h"
#include "ps2inline.h"
#include "vu0inline.h"

union VU_SCALE { QW q; VECTOR v; };

extern "C" QW PosLoWorld(void *);
extern "C" int CSolveQuadratic__FfffPf(float, float, float, float *);

extern float RO_002BF738;
extern float RO_002BF73C;
extern float RO_002BF8B0[3];
extern float RO_002BF8C0[2];
extern float RO_002BF8C8;
extern float RO_002BF8CC;
extern float RO_002BF8D0;
extern float RO_002BF8D4;
extern float RO_002BF8D8;
extern float RO_002BF8DC;

static inline float SqrtfAsm(float value)
{
    float result;
    asm volatile("sqrt.s %0, %1" : "=&f"(result) : "f"(value));
    return result;
}

struct JMP_19A750 {
    JT *pjt;
};

extern "C" QW GetJmpLaunchVelocity(JMP_19A750 *pjmp, int state)
{
    VU_SCALE position;
    VU_SCALE velocity;
    float roots[4];
    position.q = PosLoWorld(pjmp->pjt);
    velocity.q = pjmp->pjt->GetVelocityVec();
    float gravity = *(float *)(*(char **)((char *)pjmp->pjt + 0xE8) + 0x88);
    float candidate;
    switch (state) {
    case 2:
        candidate = RO_002BF8C8;
        break;
    case 18:
        candidate = RO_002BF8CC;
        break;
    case 3:
        candidate = RO_002BF8D0;
        break;
    case 1:
    case 7:
    case 9:
    case 13:
    case 14:
    case 15: {
        float margin;
        switch (state) {
        case 9:
            margin = RO_002BF8D4;
            break;
        case 14:
            margin = RO_002BF8D8;
            break;
        case 13:
            margin = RO_002BF8DC;
            break;
        default:
            margin = RO_002BF738;
            break;
        }
        JT *pjt = pjmp->pjt;
        float height = *(float *)(*(char **)((char *)pjt + 0x218) + 8) - pjt->field_0x238 - margin;
        candidate = SqrtfAsm(0.0f < (gravity + gravity) * height ? (gravity + gravity) * height : 0.0f);
        break;
    }
    case 4: {
        float polynomial = RO_002BF8B0[0] + velocity.v.z * (RO_002BF8B0[1] + velocity.v.z * RO_002BF8B0[2]);
        if (polynomial < RO_002BF8C0[0])
            candidate = RO_002BF8C0[0];
        else if (RO_002BF8C0[1] < polynomial)
            candidate = RO_002BF8C0[1];
        else
            candidate = polynomial;
        break;
    }
    case 6: {
        float fallDrop = RO_002BF738 * -2.0f;
        float fall = SqrtfAsm(gravity * fallDrop);
        float negated = -fall;
        float fallTime = negated / gravity;
        QW current = pjmp->pjt->GetVelocityVec();
        float limited = LaneZInGeneralRegister(current);
        limited = limited < fall ? limited : fall;
        float riseTime = (limited - fall) / gravity;
        float halfRise = riseTime * 0.5f;
        float apex = riseTime * (fall + gravity * halfRise);
        float launchDrop = (RO_002BF73C - RO_002BF738) * -2.0f;
        CSolveQuadratic__FfffPf(gravity * 0.5f, SqrtfAsm(gravity * launchDrop), RO_002BF738, roots);
        float later = roots[1] - fallTime;
        if (0.0f < limited) {
            float apexDrop = (RO_002BF73C - apex) * -2.0f;
            candidate = SqrtfAsm(gravity * apexDrop);
        } else {
            if (limited < negated)
                apex = 0.0f;
            float divisor = (fallTime + fallTime + later) - riseTime;
            float halfDivisor = divisor * 0.5f;
            candidate = -apex / divisor - gravity * halfDivisor;
        }
        break;
    }
    default:
        candidate = velocity.v.z;
        break;
    }
    velocity.v.z = velocity.v.z > candidate ? velocity.v.z : candidate;
    return velocity.q;
}
