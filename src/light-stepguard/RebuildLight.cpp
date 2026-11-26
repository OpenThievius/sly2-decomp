// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "light.h"

extern "C" {
void ConvertAngleStrength__FffffPfT4(float, float, float, float, float *, float *);
void ConvertUserHsvToUserRgb__FP6VECTORT0(VECTOR *, VECTOR *);
void GreyColor_1ed2d8(VECTOR *);
QW PosLoWorld(void *);
void FitLinearFunction__FffffPfT4(float, float, float, float, float *, float *);
void func_001A3B38(void *);

void RebuildLight(LIGHT *light)
{
    VECTOR rgb;
    float strengthFirst = light->strength;
    float limit = light->hsv.z < strengthFirst ? strengthFirst : light->hsv.z;
    float cone = light->cone > 30.0f ? light->cone : 30.0f;
    ConvertAngleStrength__FffffPfT4(cone, 0.0f, 0.0f, limit, &light->angleA, &light->angleB);
    ConvertUserHsvToUserRgb__FP6VECTORT0(&light->hsv, &rgb);
    GreyColor_1ed2d8(&rgb);
    float red = rgb.x;
    float green = rgb.y;
    float blue = rgb.z;
    light->color[0] = red;
    light->color[1] = green;
    light->color[2] = blue;
    light->alpha = light->strength;
    if (limit > 0.0f) {
        red = red / limit;
        green = green / limit;
        blue = blue / limit;
        light->alpha = light->alpha / limit;
        light->color[0] = red;
        light->color[1] = green;
        light->color[2] = blue;
    }
    light->angleB = -light->angleB;
    light->modeCopy = light->mode;
    switch (light->mode) {
    case 0: {
        VECTOR *pos = &light->pos;
        pos->z = 0.0f;
        pos->y = 0.0f;
        light->scaleA = 1.0f;
        light->pos.x = 0.0f;
        light->scaleB = 0.0f;
        light->posCopy = *(BYTES12 *)light->PmatWorld();
        break;
    }
    case 1:
        *(QW *)&light->pos = PosLoWorld(light);
        light->posCopy = *(BYTES12 *)&light->pos;
        FitLinearFunction__FffffPfT4(light->rangeA, 1.0f, light->rangeB, 0.0f, &light->fitA, &light->fitB);
        light->scaleA = light->fitA;
        light->scaleB = light->fitB;
        break;
    }
    float hsvLast = light->hsv.z;
    limit = light->strength < hsvLast ? hsvLast : light->strength;
    light->scaleA = light->scaleA * limit;
    light->scaleB = light->scaleB * limit;
    func_001A3B38(light);
}
}
