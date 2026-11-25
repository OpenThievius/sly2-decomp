#include "sly2.h"
#include "goal.h"
struct GUARDLIMITS_179E80 { u8 unknown_0x0[0x2CC]; float limit; float limit2; };
struct GOAL_179E80 : GOAL { float timer; };
extern "C" {
float GRandInRange(float, float);
extern float g_2dded0;
extern const float RO_002A5594;
void func_00179E80(GOAL_179E80 *self) {
    if (self->timer < RO_002A5594) {
    } else {
        float limit = ((GUARDLIMITS_179E80 *)self->pstep)->limit;
        if (limit == RO_002A5594) {
            self->timer = RO_002A5594;
        } else {
            float base = g_2dded0;
            self->timer = base + GRandInRange(limit, ((GUARDLIMITS_179E80 *)self->pstep)->limit2);
        }
    }
}
}
