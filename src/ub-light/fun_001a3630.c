/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "light.h"

void RebuildLight(struct LIGHT *light);

void func_001A3630(struct LIGHT *light, f32 cone) {
    light->cone = cone;
    RebuildLight(light);
}
