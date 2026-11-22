/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jt.h"
extern "C" {
float GRandInRange(float, float);
extern float g_2dded0;
}
extern "C" void ScheduleJtGlance(JT *pjt)
{
    float t;
    if (pjt->fGlance) {
        t = g_2dded0;
        t += GRandInRange(pjt->field_0x1138, pjt->field_0x113C);
    } else {
        t = g_2dded0;
        t += GRandInRange(pjt->field_0x1140, pjt->field_0x1144);
    }
    pjt->tGlance = t;
}
