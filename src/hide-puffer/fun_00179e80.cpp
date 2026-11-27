// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "goal.h"
#include "stepguard.h"
struct GOAL_179E80 : GOAL { float timer; };
extern "C" {
float GRandInRange(float, float);
extern float g_2dded0;
extern const float RO_002A5594;
void func_00179E80(GOAL_179E80 *self) {
    if (self->timer < RO_002A5594) {
    } else {
        float limit = ((STEPGUARD *)self->pstep)->field_0x2CC.gMin;
        if (limit == RO_002A5594) {
            self->timer = RO_002A5594;
        } else {
            float base = g_2dded0;
            self->timer = base + GRandInRange(limit, ((STEPGUARD *)self->pstep)->field_0x2CC.gMax);
        }
    }
}
}
