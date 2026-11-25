#include "types.h"
struct GOAL_177E80 { u8 unknown_0x0[0x34]; float f34; u8 unknown_0x38[0x10]; float f48; int f4C; u8 unknown_0x50[0x08]; int f58; u8 unknown_0x5C[0x08]; float f64; float f68; float f6C; u8 unknown_0x70[0x30]; int fA0; };
extern "C" void func_001EEF68();
extern float D_FLT_002BE624, D_FLT_002BE628, D_FLT_002BE62C;
extern "C" void GoalFollowCrv_Init(GOAL_177E80 *goal)
{
    func_001EEF68();
    goal->f34 = goal->f48 = -1.0f;
    goal->f58 = 0;
    goal->f64 = D_FLT_002BE62C;
    goal->f68 = D_FLT_002BE624;
    goal->f6C = D_FLT_002BE628;
    goal->f4C = -1;
    goal->fA0 = 1;
}
