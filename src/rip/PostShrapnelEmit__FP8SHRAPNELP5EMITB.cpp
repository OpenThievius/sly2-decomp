#include "vu0inline.h"
#include "sly2.h"
#include "ps2inline.h"
extern "C" {
void func_001CE9B8();
float GRandInRange(float, float);
extern float g_2c1f78[];
extern float g_2c1f80[];
extern float g_2bbb60[];
}
struct EMITB { u8 unknown_0x0[0xF0]; float vx, vy, vz; };
struct SHRAPNEL { u8 unknown_0x0[0x18]; float lifetime; u8 unknown_0x1C[0x74]; QW velocity; u8 unknown_0xA0[0x30]; float spin[3]; u8 unknown_0xDC[0x14]; float vx, vy, vz; };

void PostShrapnelEmit(SHRAPNEL *shrapnel, EMITB *emit)
{
    func_001CE9B8();
    shrapnel->lifetime = shrapnel->lifetime * GRandInRange(g_2c1f78[0], g_2c1f78[1]);
    float speed = LaneX(SqrtX(SquaredLength(shrapnel->velocity)));
    shrapnel->vx = emit->vx;
    shrapnel->vy = emit->vy;
    shrapnel->vz = emit->vz;
    float low = g_2bbb60[0];
    float high = g_2bbb60[1];
    float spread = g_2c1f80[0] + speed * (g_2c1f80[1] + speed * g_2c1f80[2]);
    if (spread < low)
        spread = low;
    else if (high < spread)
        spread = high;
    float range = spread * 10.0f;
    for (int index = 0; index < 3; index++)
        shrapnel->spin[index] = GRandInRange(-range, range);
}
