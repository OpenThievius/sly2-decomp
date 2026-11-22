/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "light.h"

void RebuildLight(struct LIGHT *light);
void func_001A5E80(struct LIGHT *light);

void func_001A3460(struct LIGHT *light) {
    s32 generation;

    func_001A5E80(light);
    generation = 0;
    if (light->pxf != 0) {
        generation = light->pxf->generation;
    }
    if (light->generation < generation) {
        light->generation = generation;
        RebuildLight(light);
    }
}
