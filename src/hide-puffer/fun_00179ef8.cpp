#include "sly2.h"
#include "goal.h"
struct GUARDLIMITS_179EF8 { u8 unknown_0x0[0x2D4]; float limit; float limit2; };
struct GOAL_179EF8 : GOAL { u8 unknown_0x30[4]; float timer; };
extern "C" {
float GRandInRange(float, float);
extern float g_2dded0;
extern const float RO_002A5598;
void func_00179EF8(GOAL_179EF8 *self) {
    if (self->timer < RO_002A5598) {
    } else {
        float limit = ((GUARDLIMITS_179EF8 *)self->pstep)->limit;
        if (limit == RO_002A5598) {
            self->timer = RO_002A5598;
        } else {
            float base = g_2dded0;
            self->timer = base + GRandInRange(limit, ((GUARDLIMITS_179EF8 *)self->pstep)->limit2);
        }
    }
}
}
