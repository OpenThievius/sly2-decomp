/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "light.h"

void RebuildLight(struct LIGHT *light);

void func_001A3610(struct LIGHT *light, f32 strength) {
    light->strength = strength;
    RebuildLight(light);
}
