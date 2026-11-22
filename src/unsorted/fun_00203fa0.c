/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

void func_00203FA0(struct STEPVIEW *step, s32 value) {
    if (step->field_0x204 != value) {
        step->field_0x204 = value;
        if (value != 0) {
            step->psoSurface = 0;
        }
    }
}
