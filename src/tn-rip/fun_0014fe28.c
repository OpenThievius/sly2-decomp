/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

void SetCmFov(struct CM *, f32);
extern struct CM B_002DDF40;

void func_0014FE28(struct CPLOOK *look) {
    look->u = 0;
    look->du = 0;
    SetCmFov(&B_002DDF40, look->fovMin);
}
